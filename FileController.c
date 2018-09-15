
#include "GameBoardClass.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *fileString, *inputString;
FILE *fp;
int rows, column, value, rowIndexFile, columnIndexFile;
GameBoard *newBoard;

void makeFileString(char *fileString, GameBoard *gameBoard, int gameMode) {
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

int saveFile(char *filePath, GameBoard *gameBoard, int gameMode) {
    fileString = (char *) malloc(1024);
    assert(fileString);
    strcpy(fileString, "");
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
    for (rowIndexFile = 0; rowIndexFile < getNumberOfRows(newBoard); rowIndexFile++) {
        for (columnIndexFile = 0; columnIndexFile < getNumberOfColumns(newBoard); columnIndexFile++) {
            fscanf(fp, "%s", inputString);
            sscanf(inputString, "%d", &value);
            setValueToCell(newBoard, columnIndexFile, rowIndexFile, value);
            if (strchr(inputString, '.') != NULL) {
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
