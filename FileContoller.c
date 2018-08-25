//
// Created by Shai Leibovich on 25/08/2018.
//

#include "GameBoard.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void makeFileString(char *fileString, GameBoard *gameBoard) {
    getNumberOfBlocksString(fileString, gameBoard);
    strcat(fileString, " ");
    getNumberOfRowsString(fileString, gameBoard);
    strcat(fileString, "\n");
    for (int rowIndex = 0; rowIndex < getNumberOfRows(gameBoard); rowIndex++) {
        getRowValuesString(fileString, gameBoard,rowIndex);
        if (rowIndex != getNumberOfRows(gameBoard)-1){
            strcat(fileString, "\n");
        }
    }

}

int saveFile(char *filePath, GameBoard *gameBoard) {
    FILE *fp;
    char *fileString = (char*)malloc(sizeof(char) * 1024);
    makeFileString(fileString, gameBoard);
    printf(fileString);
    fp = fopen(filePath, "w");
    if (fputs(fileString, fp) == 0){
        return 0;
    }
    return 1;

}

int openGameBoardFromFile(char *filePath) {
    return 0;
}