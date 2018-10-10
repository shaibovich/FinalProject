/**
 * Exhaustive algorithm source File
 *
 * This file contains implementations of all functions that use the exhaustive algorithm
 *
 */

#include "GameBoardClass.h"
#include "Stack.h"
#include "LinkedList.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int rowAlgoIndex, columnAlgoIndex, value, counter, check, chosenValue;
GameBoard *tempBoard;
Stack *stack;
StackCell *currentCell;
Cell *emptyCell;
int *sit_mat, *innerCounterLst;
List * movesList;

/**
 * This function returns the next cell that is empty
 *
 *
 * @param- GameBoard- the Board user is currently solving
 *         currentRow - row parameter of current cell
 *         currentColumn- like row
 * @returns- returns value of the next empty cell
 */
Cell *getNextEmptyCell(GameBoard *gameBoard, int *currentRow, int *currentColumn) {
    while (*currentRow < getNumberOfRows(gameBoard)) {
        if (!getCellValue(gameBoard, *currentColumn, *currentRow)) {
            return getCell(gameBoard, *currentColumn, *currentRow);
        }
        if (*currentColumn == getNumberOfColumns(gameBoard) - 1) {
            *currentColumn = 0;
            *currentRow += 1;
        } else {
            *currentColumn += 1;
        }

    }
    return NULL;
}

/**
 * This function ends the exhaustive algorithm, deletes resources and frees allocations*
 */

void finishAlg() {
    if (currentCell != NULL){
        deleteStackCell(currentCell);
    }
    DeleteStack(stack);
    free(currentCell);
}

/**
 * This function counts number of solutions using the exhastive algorithm and returns it as an int
 *
 * @param gameBoard
 * @returns int - number of possible solutions

 */
int numberOfSolves(GameBoard *gameBoard) {
    counter = 0, rowAlgoIndex = 0, columnAlgoIndex = 0,check =0;
    currentCell = NULL;
    stack = createNewStack();
    emptyCell = getNextEmptyCell(gameBoard, &rowAlgoIndex, &columnAlgoIndex);
    if (emptyCell == NULL){
        return 0;
    }
    push(stack, rowAlgoIndex, columnAlgoIndex);
    while (1) {
        if (rowAlgoIndex > getNumberOfColumns(gameBoard)){
            check = 1;
        }
        else if (getCellValue(gameBoard, columnAlgoIndex, rowAlgoIndex) != getNumberOfColumns(gameBoard)){
            setCellValue(gameBoard, columnAlgoIndex, rowAlgoIndex, getCellValue(gameBoard, columnAlgoIndex, rowAlgoIndex)+1);
        } else {
            check = 1;
        }
        if (validateSet(gameBoard, rowAlgoIndex, columnAlgoIndex, getCellValue(gameBoard, columnAlgoIndex, rowAlgoIndex)) == 1 && !check){
            if (getNextEmptyCell(gameBoard, &rowAlgoIndex, &columnAlgoIndex) == NULL){
                check = 1;
            }
            push(stack, rowAlgoIndex, columnAlgoIndex);
            if (!checkBoardErrors(gameBoard) && isBoardFull(gameBoard)){
                counter++;
                check = 1;
            } else {
                check = 0;
            }
        } else if (check) {
            setCellValue(gameBoard, columnAlgoIndex, rowAlgoIndex, 0);
            currentCell = pop(stack);
            if (currentCell == NULL) {
                break;
            }
            columnAlgoIndex = getColumn(currentCell);
            rowAlgoIndex = getRow(currentCell);
            check = 0;
        }
    }
    finishAlg();
    return counter;
}

/**
 * This function fills the gamBoard for Autofill command according to exhaustive algorithm
 *
 * @param gameboard and the linkedlist of moves
 */

void fillGameBoard(GameBoard *gameBoard, ListofLists *listArray) {
    movesList = createLinkedList();
    chosenValue = 0;
    tempBoard = copyGameBoard(gameBoard);
    for (rowAlgoIndex = 0; rowAlgoIndex < getNumberOfRows(gameBoard); rowAlgoIndex++) {
        for (columnAlgoIndex = 0; columnAlgoIndex < getNumberOfColumns(gameBoard); columnAlgoIndex++) {
            if (!getCellValue(tempBoard, columnAlgoIndex, rowAlgoIndex)) {
                counter = 0;
                for (value = 1; value < getNumberOfColumns(gameBoard)+1; value++) {
                    if (validateSet(tempBoard, rowAlgoIndex, columnAlgoIndex, value) == 1) {
                        counter += 1;
                        chosenValue = value;
                    }
                    if (counter > 1) {
                        chosenValue = 0;
                        break;
                    }
                }
                if (counter == 1) {
                    setCellValue(gameBoard, columnAlgoIndex, rowAlgoIndex, chosenValue);
                    printSetCell(columnAlgoIndex+1, rowAlgoIndex+1, chosenValue);
                    addMove(gameBoard, movesList, rowAlgoIndex, columnAlgoIndex, 0);
                }
            }
        }
    }
    addMovesFromList(listArray, movesList);
    deleteBoard(tempBoard);
}
