
#include "GameBoardClass.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *fileString, *inputString;
FILE * fp;
int rows, column, value, columnIndex , rowIndex;
GameBoard * newBoard;

void makeFileString(char *fileString, GameBoard *gameBoard, int gameMode) {
    getNumberOfBlocksString(fileString, gameBoard);
    strcat(fileString, " ");
    getNumberOfRowsString(fileString, gameBoard);
    strcat(fileString, "\n");
    for (rowIndex = 0; rowIndex < getNumberOfRows(gameBoard); rowIndex++) {
        getRowValuesString(fileString, gameBoard, rowIndex, gameMode);
        if (rowIndex != getNumberOfRows(gameBoard) - 1) {
            strcat(fileString, "\n");
        }
    }

}

int saveFile(char *filePath, GameBoard *gameBoard, int gameMode) {
    fileString = (char *) malloc(sizeof(char) * 1024);
    assert(fileString);
    makeFileString(fileString, gameBoard, gameMode);
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
    for (rowIndex = 0; rowIndex < getNumberOfRows(newBoard); rowIndex++) {
        for (columnIndex = 0; columnIndex < getNumberOfColumns(newBoard); columnIndex++) {
            fscanf(fp, "%s", inputString);
            sscanf(inputString, "%d", &value);
            setValueToCell(newBoard, columnIndex, rowIndex, value);
            if (strchr(inputString, '.') != NULL) {
                setCellFixed(newBoard, columnIndex, rowIndex, 1);
            } else {
                setCellFixed(newBoard, columnIndex, rowIndex, 0);
            }

        }
    }
    checkBoardErrors(newBoard);
    fclose(fp);
    free(inputString);
    return newBoard;
}
