//
// Created by Shai Leibovich on 19/08/2018.
//
#define ERROR -1

#include <stdlib.h>
#include <assert.h>
#include <printf.h>

typedef struct GameCell {
    int value;
    int isFixed;
    int isError;
} Cell;


typedef struct GameBoards {
    int size;
    int numberOfColumnBlock;
    int numberOfRowsBlock;
    int numberOfRows;
    int numberOfColumns;
    Cell *cellList;
} GameBoard;

//
//int isZeroOrOne(int value) {
//    return value == 0 || value == 1 ? 1 : 0;
//}


int getCellIsFixed(Cell *cell) {
    return cell->isFixed;
}

//int getCellIsError(Cell *cell) {
//    return cell->isError;
//}
//
//void setCellIsFixed(Cell *cell, int isFixed) {
//    if (isZeroOrOne(isFixed)) {
//        cell->isFixed = isFixed;
//    } else {
//        printf("Error -> cell can be set only 0 or 1");
//    }
//}
//
//void setCellIsError(Cell *cell, int isError) {
//    if (isZeroOrOne(isError)) {
//        cell->isError = isError;
//    } else {
//        printf("Error -> cell can be set only 0 or 1");
//    }
//}
//
//void setCellValue(Cell *cell, int value) {
//    cell->value = value;
//}
//
//int getCellValue(Cell *cell) {
//    return cell->value;
//}

GameBoard *createEmptyBoard(int rows, int columns) {
    GameBoard *gameBoard = (GameBoard *) malloc(sizeof(GameBoard));
    assert(gameBoard);
    int size = (rows * columns) ^2;
    gameBoard->size = size;
    gameBoard->numberOfRows = rows * columns;
    gameBoard->numberOfColumnBlock = columns;
    gameBoard->numberOfColumns = rows * columns;
    gameBoard->numberOfRowsBlock = rows;
    gameBoard->cellList = (Cell *) malloc(sizeof(Cell) * size);
    assert(gameBoard->cellList);
    for (int rowIndex = 0; rowIndex < gameBoard->numberOfRows; ++rowIndex) {
        for (int columnIndex = 0; columnIndex < gameBoard->numberOfColumns; ++columnIndex) {
            (gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + gameBoard->numberOfRows)->value = 0;
            (gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isFixed = 0;
            (gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isError = 0;
        }
    }
    return gameBoard;
}

GameBoard *copyGameBoard(GameBoard *oldGameBoard) {
    GameBoard *newGameBoard = (GameBoard *) malloc(sizeof(GameBoard));
    assert(oldGameBoard);
    newGameBoard->size = oldGameBoard->size;
    newGameBoard->numberOfRows = oldGameBoard->numberOfRows;
    newGameBoard->numberOfColumns = oldGameBoard->numberOfColumns;
    newGameBoard->numberOfRowsBlock = oldGameBoard->numberOfRowsBlock;
    newGameBoard->numberOfColumnBlock = oldGameBoard->numberOfColumnBlock;
    newGameBoard->cellList = (Cell *) malloc(sizeof(Cell) * oldGameBoard->size);
    assert(newGameBoard->cellList);
    for (int rowIndex = 0; rowIndex < newGameBoard->numberOfRows; ++rowIndex) {
        for (int columnIndex = 0; columnIndex < newGameBoard->numberOfColumns; ++columnIndex) {
            (newGameBoard->cellList + rowIndex * newGameBoard->numberOfColumns + newGameBoard->numberOfRows)->value = (
                    oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns +
                    oldGameBoard->numberOfRows)->value;
            (newGameBoard->cellList + rowIndex * newGameBoard->numberOfColumns +
             newGameBoard->numberOfRows)->isFixed = (oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns +
                                                     oldGameBoard->numberOfRows)->isFixed;
            (newGameBoard->cellList + rowIndex * newGameBoard->numberOfColumns +
             newGameBoard->numberOfRows)->isError = (oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns +
                                                     oldGameBoard->numberOfRows)->isError;
        }
    }
    return newGameBoard;
}

int validateCellValue(GameBoard *gameBoard, int column, int row, int value) {
    if (value > gameBoard->size) {
        printf("Error: value not in range 0-%d\n", gameBoard->size);
        return 0;
    }
    return 1;
}

int validateCellIndex(GameBoard *gameBoard, int column, int row) {
    if (column > gameBoard->numberOfColumns || row > gameBoard->numberOfRows) {
        printf("Error, invalid index");
        return ERROR;
    }
    return 1;
}

int validateCellFixed(GameBoard *gameBoard, int column, int row) {
    if ((getCellIsFixed((gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)))) {
        printf("Error: cell is fixed\n");
        return ERROR;
    }
    return 1;
}

int setCellValue(GameBoard *gameBoard, int column, int row, int value) {
    if (!validateCellValue(gameBoard, column, row, value)) {

    } else if (!validateCellFixed(gameBoard, column, row)) {

    } else if (!validateCellIndex(gameBoard, column, row)) {

    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->value = value;
        return 1;
    }
}

int setCellFixed(GameBoard *gameBoard, int column, int row, int isFixed) {
    if (!validateCellFixed(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isFixed = isFixed;
        return 1;
    }
}

int isCellFixed(GameBoard *gameBoard, int column, int row) {
    if (!validateCellFixed(gameBoard, column, row)) {
        return ERROR;
    } else {
        return (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isFixed;
    }
}

int getCellValue(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        return (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->value;
    }
}

int getCellError(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        return (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->value;
    }
}

int makrCellError(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isError = 1;
        return 1;
    }
}

int markCellUnError(GameBoard *gameBoard, int column, int row) {
    if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isError = 0;
        return 1;
    }
}

int checkBoardErrors(GameBoard *gameBoard) {
    for (int rowIndex = 0; rowIndex < gameBoard->numberOfRowsBlock; rowIndex++) {
        for (int columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + gameBoard->numberOfRows)->isError) {
                return 1;
            }
        }
    }
    return 0;
}

void printGameBoard(GameBoard *gameBoard, int withStars) {
    for (int rowIndex = 0; rowIndex < gameBoard->numberOfColumns; ++rowIndex) {
        if (rowIndex % gameBoard->numberOfColumnBlock == 0) {
            printf("----------------------------------\n");
        }
        for (int columnIndex = 0; columnIndex < gameBoard->numberOfRows; ++columnIndex) {
            if (columnIndex % gameBoard->numberOfRowsBlock == 0) {
                printf("| ");
            }
            if (isCellFixed(gameBoard, columnIndex, rowIndex)) {
                printf(".");
            } else if (withStars && getCellError(gameBoard, columnIndex, rowIndex)) {
                printf("*");
            } else {
                printf(" ");
            }
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->value == 0) {
                printf(" ");
            } else {
                printf("%d ", abs((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->value));
            }
        }
        printf("|");
        printf("\n");
    }
    printf("----------------------------------\n");
}

int setValueToCell(GameBoard *gameBoard, int column, int row, int value) {
    if (!validateCellIndex(gameBoard, column, row) || !validateCellFixed(gameBoard, column, row) ||
        !validateCellValue(gameBoard, column, row, value)) {
        return ERROR;
    } else {

    }
    return 1;
}

void deleteBoard(GameBoard *gameBoard) {
    free(gameBoard->cellList);
    free(gameBoard);
};


