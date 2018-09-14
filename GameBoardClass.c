
#ifndef GAMEBOARD_C
#define GAMEBOARD_C



struct GameCell {
    int value;
    int isFixed;
    int isError;
};

struct GameBoards {
    int size;
    int numberOfColumnBlock;
    int numberOfRowsBlock;
    int numberOfRows;
    int numberOfColumns;
    struct GameCell *cellList;
};

#endif

#include <stdlib.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "GameBoardClass.h"
#include "utils.h"


enum VALIDATION_ERROR {
    BLOCK = -1,
    COLUMN = -2,
    ROW = -3
};

int rowIndex, columnIndex, rowBlock, columnBlock, size, randValue, columnRandom, rowRandom, generateCounter;
char *gameInput;


int validateSet(const GameBoard *gameBoard, int row, int column, int value) {
    if (value == 0) {
        return 1;
    }
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; ++rowIndex) {
        if (rowIndex != row && (gameBoard->cellList + rowIndex * gameBoard->numberOfRows + column)->value == value) {
            return COLUMN;
        }
    }
    for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; ++columnIndex) {
        if (columnIndex != column &&
            (gameBoard->cellList + row * gameBoard->numberOfColumns + columnIndex)->value == value) {
            return ROW;
        }
    };
    rowBlock = (row / gameBoard->numberOfRowsBlock) * gameBoard->numberOfRowsBlock;
    columnBlock = (column / gameBoard->numberOfColumnBlock) * gameBoard->numberOfColumnBlock;
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRowsBlock; ++rowIndex) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumnBlock; ++columnIndex) {
            if ((gameBoard->cellList + (rowIndex + rowBlock) * gameBoard->numberOfColumns +
                 (columnIndex + columnBlock))->value == value && (rowIndex + rowBlock) != row &&
                (columnBlock + columnIndex) != column) {
                return BLOCK;
            }
        }
    }
    return 1;
}


int getCellIsFixed(Cell *cell) {
    return cell->isFixed;
}


GameBoard *createEmptyBoard(int rows, int columns) {
    GameBoard *newBoard = (GameBoard *) malloc(sizeof(GameBoard));
    assert(newBoard);
    size = (rows * columns) * (rows * columns);
    newBoard->size = size;
    newBoard->numberOfRows = rows * columns;
    newBoard->numberOfColumnBlock = columns;
    newBoard->numberOfColumns = rows * columns;
    newBoard->numberOfRowsBlock = rows;
    newBoard->cellList = (Cell *) malloc(sizeof(Cell) * size);
    assert(newBoard->cellList);
    for (rowIndex = 0; rowIndex < newBoard->numberOfRows; ++rowIndex) {
        for (columnIndex = 0; columnIndex < newBoard->numberOfColumns; ++columnIndex) {
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->value = 0;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->isFixed = 0;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->isError = 0;
        }
    }
    return newBoard;
}

GameBoard *copyGameBoard(GameBoard *oldGameBoard) {
    GameBoard *newBoard = (GameBoard *) malloc(sizeof(GameBoard));
    assert(newBoard);
    newBoard->size = oldGameBoard->size;
    newBoard->numberOfRows = oldGameBoard->numberOfRows;
    newBoard->numberOfColumns = oldGameBoard->numberOfColumns;
    newBoard->numberOfRowsBlock = oldGameBoard->numberOfRowsBlock;
    newBoard->numberOfColumnBlock = oldGameBoard->numberOfColumnBlock;
    newBoard->cellList = (Cell *) malloc(sizeof(Cell) * oldGameBoard->size);
    assert(newBoard->cellList);
    for (rowIndex = 0; rowIndex < newBoard->numberOfRows; ++rowIndex) {
        for (columnIndex = 0; columnIndex < newBoard->numberOfColumns; ++columnIndex) {
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->value = (
                    oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns +
                    columnIndex)->value;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns +
             columnIndex)->isFixed = (oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns +
                                      columnIndex)->isFixed;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns +
             columnIndex)->isError = (oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns +
                                      columnIndex)->isError;
        }
    }
    return newBoard;
}

int validateCellValue(GameBoard *gameBoard, int value) {
    if (value > gameBoard->numberOfRows) {
        return 0;
    }
    return 1;
}

int validateCellIndex(GameBoard *gameBoard, int column, int row) {
    if (column >= gameBoard->numberOfColumns || column < 0|| row<0|| row >= gameBoard->numberOfRows) {
        return 0;
    }
    return 1;
}

int validateCellFixed(GameBoard *gameBoard, int column, int row) {
    if ((getCellIsFixed((gameBoard->cellList + row * gameBoard->numberOfColumns + column)))) {
        return 0;
    }
    return 1;
}

int setCellValue(GameBoard *gameBoard, int column, int row, int value) {
    if (!validateCellValue(gameBoard, value)) {
        printValueOutOfRange(gameBoard->numberOfRows);
        return ERROR;
    } else if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->value = value;
        return 1;
    }
}

int setCellFixed(GameBoard *gameBoard, int column, int row, int isFixed) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->isFixed = isFixed;
        return 1;
    }
}

int isCellFixed(GameBoard *gameBoard, int column, int row, int isSave) {
    if (!validateCellFixed(gameBoard, column, row)) {
        if (!isSave) {
            printCellIsFixed();
        }
        return ERROR;
    } else {
        return (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->isFixed;
    }
}

int getCellValue(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        return (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->value;
    }
}

int getCellError(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        return (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->isError;
    }
}

int markCellError(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->isError = 1;
        return 1;
    }
}

int markCellUnError(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->isError = 0;
        return 1;
    }
}


int checkBoardErrors(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRowsBlock; rowIndex++) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->isError) {
                return 1;
            }
        }
    }
    return 0;
}

void printGameBoard(GameBoard *gameBoard, int withStars) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfColumns; ++rowIndex) {
        if (rowIndex % gameBoard->numberOfColumnBlock == 0) {
            printf("----------------------------------\n");
        }
        for (columnIndex = 0; columnIndex < gameBoard->numberOfRows; ++columnIndex) {
            if (columnIndex % gameBoard->numberOfRowsBlock == 0) {
                printf("| ");
            }
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->value == 0) {
                printf(" ");
            } else {
                printf("%d", abs((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->value));
            }
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->isFixed) {
                printf(". ");
            } else if (withStars && getCellError(gameBoard, columnIndex, rowIndex)) {
                printf("* ");
            } else {
                printf("  ");
            }

        }
        printf("|");
        printf("\n");
    }
    printf("----------------------------------\n");
}

int isInvalidValue(GameBoard *gameBoard, int column, int row, int value) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++) {
        if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + column)->value == value) {
            return 0;
        }
    }

    for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
        if ((gameBoard->cellList + row * gameBoard->numberOfColumns + columnIndex)->value == value) {
            return 0;
        }
    }


    return 1;
}

int setValueToCell(GameBoard *gameBoard, int column, int row, int value) {
    if (!validateCellFixed(gameBoard, column, row)) {
        printCellIsFixed();
        return ERROR;
    }
    else if (!validateCellIndex(gameBoard, column, row)|| !validateCellValue(gameBoard,value)) {
        printValueOutOfRange(gameBoard->numberOfRows);
        return ERROR;
    }
    else {
        int res = validateSet(gameBoard, row, column, value);
        switch (res) {
            case 1:
                setCellValue(gameBoard, column, row, value);
                markCellUnError(gameBoard, column, row);
                break;
            case COLUMN:
            case ROW:
            case BLOCK:
                setCellValue(gameBoard, column, row, value);
                markCellError(gameBoard, column, row);
            default:
                break;
        }
    }
    return 1;
}

void deleteBoard(GameBoard *gameBoard) {
    free(gameBoard->cellList);
    free(gameBoard);
}

void getNumberOfRowsString(char *string, GameBoard *gameBoard) {
    gameInput = (char *) malloc(sizeof(char) * gameBoard->numberOfRows);
    sprintf(gameInput, "%d", gameBoard->numberOfRowsBlock);
    strcat(string, gameInput);
    free(gameInput);
}

void getNumberOfBlocksString(char *string, GameBoard *gameBoard) {
    gameInput = (char *) malloc(sizeof(char) * gameBoard->numberOfColumns);
    sprintf(gameInput, "%d", gameBoard->numberOfColumnBlock);
    strcat(string, gameInput);
    free(gameInput);
}

void getRowValuesString(char *string, GameBoard *gameBoard, int row, int isSave) {
    gameInput = (char *) malloc(sizeof(char) * gameBoard->size);
    assert(gameInput);
    for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
        sprintf(gameInput, "%d", (gameBoard->cellList + row * gameBoard->numberOfColumns + columnIndex)->value);
        strcat(string, gameInput);
        if (isCellFixed(gameBoard, columnIndex, row, isSave)) {
            strcat(string, ".");
        }
        if (columnIndex != gameBoard->numberOfColumns - 1) {
            strcat(string, " ");
        }
    }
    free(gameInput);
}

int getNumberOfColumns(GameBoard *gameBoard) {
    return gameBoard->numberOfColumns;
}

int getNumberOfRows(GameBoard *gameBoard) {
    return gameBoard->numberOfRows;
}

int getNumberOfBlockColumn(GameBoard *gameBoard) {
    return gameBoard->numberOfColumnBlock;
}

int getNumberOfRowsBlock(GameBoard *gameBoard) {
    return gameBoard->numberOfRowsBlock;
}

int isBoardFull(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 2; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            if (!getCellValue(gameBoard, columnIndex, rowIndex)) {
                return 0;
            }
        }
    }
    return 1;
}

int isBoardEmpty(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            if (getCellValue(gameBoard, columnIndex, rowIndex) != 0) {
                return 0;
            }
        }
    }
    return 1;
}

void setAllFilledFixed(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            if (getCellValue(gameBoard, columnIndex, rowIndex) != 0) {
                setCellFixed(gameBoard, columnIndex, rowIndex, 1);
            }
        }
    }
}

int getGameBoardSize(GameBoard *gameBoard) {
    return gameBoard->size;
}

void makeBoardEmpty(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            setCellValue(gameBoard, columnIndex, rowIndex, 0);
        }
    }
}

Cell *getCell(GameBoard *gameBoard, int column, int row) {
    return (gameBoard->cellList + column * gameBoard->numberOfRows + row);
}

int fillRandom(GameBoard *gameBoard, int x) {
    generateCounter = 0, rowRandom = 0, columnRandom = 0, randValue = 0;
    while (x > 0 && generateCounter < 1000) {
        rowRandom = (rand() % (gameBoard->numberOfRows));
        columnRandom = (rand() % (gameBoard->numberOfColumns));
        randValue = (rand() % (gameBoard->numberOfColumns));
        if (randValue != 0) {
            if (validateSet(gameBoard, rowRandom, columnRandom, randValue) == 1 &&
                getCellValue(gameBoard, columnRandom, rowRandom) == 0) {
                if (setCellValue(gameBoard, columnRandom, rowRandom, randValue) != ERROR) {
                    x--;
                }
            }
        }
        generateCounter++;
    }
    if (x == 0) {
        return 1;
    }
    return 0;
}


void clearRandom(GameBoard *gameBoard, int y) {
    while (y > 0) {
        rowIndex = (rand() % (gameBoard->numberOfRows));
        columnIndex = (rand() % (gameBoard->numberOfColumns));
        if (setCellValue(gameBoard, columnIndex, rowIndex, 0) != ERROR) {
            y--;
        }
    }
}