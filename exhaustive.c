

#include "GameBoardClass.h"
#include "Stack.h"
#include <stdlib.h>

int rowIndex, columnIndex, value, counter;
GameBoard *tempBoard;
Stack *stack;
StackCell *currentCell;
Cell *emptyCell;


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

void finishAlg() {
    DeleteStack(stack);
    free(emptyCell);
    free(currentCell);
}


int numberOfSolves(GameBoard *gameBoard) {
    counter = 0, rowIndex = 0, columnIndex = 0;
    stack = createNewStack();
    emptyCell = getNextEmptyCell(gameBoard, &rowIndex, &columnIndex);
    push(stack, rowIndex, columnIndex);
    while (!isEmpty(stack)) {
        setCellValue(gameBoard, columnIndex, rowIndex, getCellValue(gameBoard, columnIndex, rowIndex) + 1);
        if (checkBoardErrors(gameBoard)) {
            emptyCell = getNextEmptyCell(gameBoard, &columnIndex, &rowIndex);
            push(stack, rowIndex, columnIndex);
        } else if (getCellValue(gameBoard, columnIndex, rowIndex) > getNumberOfColumns(gameBoard)) {
            setCellValue(gameBoard, columnIndex, rowIndex, 0);
            currentCell = pop(stack);
            if (currentCell==NULL){
                break;
            }
            emptyCell = getCell(gameBoard, getColumn(currentCell), getRow(currentCell));
        }
    }
    finishAlg();
    return counter;
}

void fillGameBoard(GameBoard *gameBoard) {
    tempBoard = copyGameBoard(gameBoard);
    for (rowIndex = 0; rowIndex < getNumberOfRows(gameBoard); rowIndex++) {
        for (columnIndex = 0; columnIndex < getNumberOfColumns(gameBoard); columnIndex++) {
            if (!getCellValue(tempBoard, columnIndex, rowIndex)) {
                counter = 0;
                for (value = 1; value < getNumberOfColumns(gameBoard); value++) {
                    setCellValue(tempBoard, columnIndex, rowIndex, value);
                    if (!checkBoardErrors(tempBoard)) {
                        counter += 1;
                    }
                    if (counter > 1) {
                        break;
                    }
                }
                if (counter == 1) {
                    setCellValue(gameBoard, columnIndex, rowIndex, value);
                }
                setCellValue(tempBoard, columnIndex, rowIndex, 0);
            }
        }
    }
    deleteBoard(gameBoard);
}