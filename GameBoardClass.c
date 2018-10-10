/**
 * Game Board Class Source File
 *
 * This file implements gameBoard structures and get functions
 *
 */

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
#include "LinkedList.h"

/**
 * this enum is used for gameboard structure
 */

enum VALIDATION_ERROR {
    BLOCK = -1,
    COLUMN = -2,
    ROW = -3
};

int rowIndex, columnIndex, rowBlock, columnBlock, size, randValue, columnRandom, rowRandom, generateCounter, updateRow, updateColumn, counter;
char *gameInput;
Node *tempNode;

/**
 * this function updates the board to print errors where needed
 * @param gameBoard
 */

void updateBoardErrors(GameBoard * gameBoard){
    for (updateRow = 0; updateRow < gameBoard->numberOfRows ; updateRow++){
        for (updateColumn = 0; updateColumn < gameBoard->numberOfColumns; updateColumn++){
            if (isCellFixed(gameBoard, updateColumn,updateRow,1)){
                continue;
            } else if (validateSet(gameBoard,updateRow, updateColumn, getCellValue(gameBoard,updateColumn,updateRow)) == 1){
                markCellUnError(gameBoard,updateColumn,updateRow);
            } else {
                markCellError(gameBoard,updateColumn,updateRow);
            }
        }
    }
}

/**
 * this function checks if value is legal in his row,column and block
 * @param gameBoard
 * @param row - of the checked cell
 * @param column - of the checked cell
 * @param value -checked value
 * @return  1 if legal
 */


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
    rowBlock = (row / gameBoard->numberOfColumnBlock) * gameBoard->numberOfColumnBlock;
    columnBlock = (column / gameBoard->numberOfRowsBlock) * gameBoard->numberOfRowsBlock;
    for (rowIndex = 0; rowIndex < gameBoard->numberOfColumnBlock; ++rowIndex) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfRowsBlock; ++columnIndex) {
            if ((gameBoard->cellList + (rowIndex + rowBlock) * gameBoard->numberOfColumns +
                 (columnIndex + columnBlock))->value == value && (rowIndex + rowBlock) != row &&
                (columnBlock + columnIndex) != column) {
                return BLOCK;
            }
        }
    }
    return 1;
}

/**
 * this function updates the cells' parameter "isError"
 * @param gameBoard
 * @param row , column , value of about-to-be-marked cell
 * @param isError - this parameter defines the mark of the cell
 */
void markCellsIsError(GameBoard *gameBoard, int row, int column, int value, int isError) {
    if (value == 0) return;

    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; ++rowIndex) {
        if (rowIndex != row && (gameBoard->cellList + rowIndex * gameBoard->numberOfRows + column)->value == value) {
            if (isCellFixed(gameBoard, column, rowIndex, 1) == 0) {
                if (isError) {
                    markCellError(gameBoard, column, rowIndex);
                } else {
                    markCellUnError(gameBoard, column, rowIndex);
                }
            }
        }
    }
    for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; ++columnIndex) {
        if (columnIndex != column &&
            (gameBoard->cellList + row * gameBoard->numberOfColumns + columnIndex)->value == value) {
            if (isCellFixed(gameBoard, columnIndex, row, 1) == 0) {
                if (isError) {
                    markCellError(gameBoard, columnIndex, row);
                } else {
                    markCellUnError(gameBoard, columnIndex, row);
                }

            }
        }
    };
    rowBlock = (row / gameBoard->numberOfRowsBlock) * gameBoard->numberOfRowsBlock;
    columnBlock = (column / gameBoard->numberOfColumnBlock) * gameBoard->numberOfColumnBlock;
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRowsBlock; ++rowIndex) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumnBlock; ++columnIndex) {
            if ((gameBoard->cellList + (rowIndex + rowBlock) * gameBoard->numberOfColumns +
                 (columnIndex + columnBlock))->value == value && (rowIndex + rowBlock) != row &&
                (columnBlock + columnIndex) != column) {
                if (isCellFixed(gameBoard, columnIndex + columnBlock, rowIndex + rowBlock, 1) == 0) {
                    if (isError) {
                        markCellError(gameBoard, columnIndex + columnBlock, rowIndex + rowBlock);
                    } else {
                        markCellUnError(gameBoard, columnIndex + columnBlock, rowIndex + rowBlock);
                    };

                }
            }
        }
    }
}


int getCellIsFixed(Cell *cell) {
    return cell->isFixed;
}

/**
 * this function creates a new and Empty gameBoard
 * @param rows - how many rows in the new gameboard
 * @param columns - how many columns
 * @return - a new gameboard (empty)
 */

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
    for (rowIndex = 0; rowIndex < newBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 0; columnIndex < newBoard->numberOfColumns; columnIndex++) {
            assert(newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex);
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->value = 0;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->isFixed = 0;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->isError = 0;
        }
    }
    return newBoard;
}

/**
 * this function counts the number of blank cells in the board for other functions' use
 * @param gameBoard
 * @return int of blank cells
 */

int getNumberOfEmptyCells(GameBoard * gameBoard){
    counter =0 ;
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++){
        for (columnIndex =0 ; columnIndex< gameBoard->numberOfColumns; columnIndex++){
            if (getCellValue(gameBoard,columnIndex, rowIndex) == 0){
                counter ++;
            }

        }
    }
    return counter;
}

/**
 * this function copies an existing gameboard into a new one so changes can be made on the copy
 * @param oldGameBoard
 * @return copy of the gameboard
 */
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
    for (rowIndex = 0; rowIndex < newBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 0; columnIndex < newBoard->numberOfColumns; columnIndex++) {
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->value = (oldGameBoard->cellList +
                                                                                                rowIndex *
                                                                                                oldGameBoard->numberOfColumns +
                                                                                                columnIndex)->value;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->isFixed = (
                    oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns + columnIndex)->isFixed;
            (newBoard->cellList + rowIndex * newBoard->numberOfColumns + columnIndex)->isError = (
                    oldGameBoard->cellList + rowIndex * oldGameBoard->numberOfColumns + columnIndex)->isError;
        }
    }
    return newBoard;
}

/**
 * this function validates the cell value (between 0 and legal range)
 * @param gameBoard
 * @param value
 * @return 1 if value is legal
 */

int validateCellValue(GameBoard *gameBoard, int value) {
    if (value > gameBoard->numberOfRows || value <0) {
        return 0;
    }
    return 1;
}

/**
 * this function validates the index of the cell (between range)
 * @param gameBoard
 * @param column , row of checked cell
 * @return 1 if index is legal
 */
int validateCellIndex(GameBoard *gameBoard, int column, int row) {
    if (column >= gameBoard->numberOfColumns || column < 0 || row < 0 || row >= gameBoard->numberOfRows) {
        return 0;
    }
    return 1;
}

/**
 * this function checks if the given cell is fixed
 * @return 1 if cell is not fixed
 */
int validateCellFixed(GameBoard *gameBoard, int column, int row) {
    if ((getCellIsFixed((gameBoard->cellList + row * gameBoard->numberOfColumns + column)))) {
        return 0;
    }
    return 1;
}

/**
 * this function 
 * @param gameBoard
 * @param column
 * @param row
 * @param value
 * @return
 */
int setCellValue(GameBoard *gameBoard, int column, int row, int value) {
    if (!validateCellValue(gameBoard, value)) {
        printValueOutOfRange(gameBoard->numberOfRows);
        return ERROR;
    } else if (!validateCellIndex(gameBoard, column, row)) {
        return ERROR;
    } else {
        (gameBoard->cellList + row * gameBoard->numberOfColumns + column)->value = value;
        updateBoardErrors(gameBoard);
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
    for (rowIndex = 0; rowIndex < gameBoard->numberOfRows; rowIndex++) {
        for (columnIndex = 0; columnIndex < gameBoard->numberOfColumns; columnIndex++) {
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->isError == 1) {
                return 1;
            }
        }
    }
    return 0;
}

void printGameBoard(GameBoard *gameBoard, int withStars) {
    for (rowIndex = 0; rowIndex < gameBoard->numberOfColumns; ++rowIndex) {
        if (rowIndex % gameBoard->numberOfColumnBlock == 0) {
            for (columnIndex = 0;
                 columnIndex < (gameBoard->numberOfColumns * 4 + gameBoard->numberOfColumnBlock + 1); columnIndex++) {
                printf("-");
            }
            printf("\n");
        }
        for (columnIndex = 0; columnIndex < gameBoard->numberOfRows; ++columnIndex) {
            if (columnIndex % gameBoard->numberOfRowsBlock == 0) {
                printf("|");
            }
            printf(" ");
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->value == 0) {
                printf("  ");
            } else {
                printf("%2d",
                       abs((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->value));
            }
            if ((gameBoard->cellList + rowIndex * gameBoard->numberOfColumns + columnIndex)->isFixed) {
                printf(".");
            } else if (withStars && getCellError(gameBoard, columnIndex, rowIndex)) {
                printf("*");
            } else {
                printf(" ");
            }

        }
        printf("|");
        printf("\n");
    }
    for (columnIndex = 0;
         columnIndex < (gameBoard->numberOfColumns * 4 + gameBoard->numberOfColumnBlock + 1); columnIndex++) {
        printf("-");
    }
    printf("\n");
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
    if (!validateCellIndex(gameBoard, column, row) || !validateCellValue(gameBoard, value)) {
        printValueOutOfRange(gameBoard->numberOfRows);
        return ERROR;
    } else if (!validateCellFixed(gameBoard, column, row)) {
        printCellIsFixed();
        return ERROR;
    } else {
        int res = validateSet(gameBoard, row, column, value);
        switch (res) {
            case 1:
                setCellValue(gameBoard, column, row, value);
                markCellUnError(gameBoard, column, row);
                updateBoardErrors(gameBoard);
                break;
            case COLUMN:
            case ROW:
            case BLOCK:
                setCellValue(gameBoard, column, row, value);
                markCellError(gameBoard, column, row);
                updateBoardErrors(gameBoard);
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
    gameInput = NULL;
}

void getNumberOfBlocksString(char *string, GameBoard *gameBoard) {
    gameInput = (char *) malloc(sizeof(char) * gameBoard->numberOfColumns);
    sprintf(gameInput, "%d", gameBoard->numberOfColumnBlock);
    strcat(string, gameInput);
    free(gameInput);
    gameInput = NULL;
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
    gameInput = NULL;
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
    return (gameBoard->cellList + row * gameBoard->numberOfRows + column);
}

int fillRandom(GameBoard *gameBoard, int x, List *fillLst) {
    generateCounter = 0, rowRandom = 0, columnRandom = 0, randValue = 0;
    while (x > 0 && generateCounter < 1000) {
        rowRandom = (rand() % (gameBoard->numberOfRows));
        columnRandom = (rand() % (gameBoard->numberOfColumns));
        randValue = (rand() % (gameBoard->numberOfColumns));
        if (randValue != 0) {
            if (validateSet(gameBoard, rowRandom, columnRandom, randValue) == 1 &&
                getCellValue(gameBoard, columnRandom, rowRandom) == 0) {
                if (setCellValue(gameBoard, columnRandom, rowRandom, randValue) != ERROR) {
                    addMove(gameBoard, fillLst, rowRandom, columnRandom, 0);
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


void clearRandom(GameBoard *gameBoard, int y, List *lst) {
    while (y > 0) {
        rowRandom = (rand() % (gameBoard->numberOfRows));
        columnRandom = (rand() % (gameBoard->numberOfColumns));
        if (getCellValue(gameBoard, columnRandom, rowRandom) == 0) {
            continue;
        } else if (setCellValue(gameBoard, columnRandom, rowRandom, 0) != ERROR) {
            tempNode = deleteCellFromList(lst, columnRandom, rowRandom);
            if (tempNode == NULL) {
                printf(" column %d row %d\n", columnRandom + 1, rowRandom + 1);
            } else {
                deleteNode(tempNode);
            }
            y--;
        }
    }
}