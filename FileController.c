/**
 * File Controller Source File
 *
 * This file implements managing the file commands. The controller implement for writing and reading from files.
 * relevant command structs.
 *
 */

#include "GameBoardClass.h"
#include "utils.h"
#include "GameManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *fileString, *inputString;
FILE *fp;
int rows, column, value, rowIndexFile, columnIndexFile;
GameBoard *newBoard;

/**
 * This function make the stirng that will be writen to file.
 * @param fileString - String, the string that will be written to file.
 * @param gameBoard - GameBoard pointer struct, Using the board the fileString will written accoring to the right format.
 */
void makeFileString(char *fileString, GameBoard *gameBoard) {
    getNumberOfBlocksString(fileString, gameBoard);
    strcat(fileString, " ");
    getNumberOfRowsString(fileString, gameBoard);
    strcat(fileString, "\n");
    for (rowIndexFile = 0; rowIndexFile < getNumberOfRows(gameBoard); rowIndexFile++) {
        getRowValuesString(fileString, gameBoard, rowIndexFile, 1);
        if (rowIndexFile != getNumberOfRows(gameBoard) - 1) {
            strcat(fileString, "\n");
        }
    }

}

/**
 * This function save the GameBoard to file according the format. The function open the file according the filePath and saving the gameBoard to file
 * @param filePath - String, point to the file path
 * @param gameBoard
 * @return
 */
int saveFile(char *filePath, GameBoard *gameBoard) {
    fileString = (char *) malloc(1024);
    assert(fileString);
    strcpy(fileString, "");
    makeFileString(fileString, gameBoard);
    fp = fopen(filePath, "w");
    if (fp == NULL) {
        printFileCannotBeCreated();
        return 0;
    }
    if (fputs(fileString, fp) == 0) {
        return 0;
    }
    fclose(fp);
    free(fileString);
    fileString = NULL;
    return 1;
}

GameBoard *openGameBoardFromFile(char *filePath, int isSolve) {
    fp = fopen(filePath, "r");
    if (fp == NULL) {
        printFilNotOpened(isSolve);
        return NULL;
    }
    fscanf(fp, "%d", &column);
    fscanf(fp, "%d", &rows);
    inputString = (char *) malloc(sizeof(char) * (column * rows));
    assert(inputString);
    newBoard = createEmptyBoard(rows, column);
    newBoard = createEmptyBoard(rows, column);
    for (rowIndexFile = 0; rowIndexFile < getNumberOfRows(newBoard); rowIndexFile++) {
        for (columnIndexFile = 0; columnIndexFile < getNumberOfColumns(newBoard); columnIndexFile++) {
            fscanf(fp, "%s", inputString);
            sscanf(inputString, "%d", &value);
            setValueToCell(newBoard, columnIndexFile, rowIndexFile, value);
            if (strchr(inputString, '.') != NULL && isSolve == SOLVE_MODE) {
                setCellFixed(newBoard, columnIndexFile, rowIndexFile, 1);
            } else {
                setCellFixed(newBoard, columnIndexFile, rowIndexFile, 0);
            }
        }
    }
    checkBoardErrors(newBoard);
    fclose(fp);
    free(inputString);
    inputString = NULL;
    return newBoard;
}
