#include <stdlib.h>
#include <stdio.h>
#include "Parser.h"
#include "Solver.h"
#include "MainAux.h"


#define NUMBER_OF_ROWS 9
#define NUMBER_OF_COLUMNS 9
#define RANDOM "random"
int gameFull = 0, check;
int *gameBoard, *commandInput, *solutionBoard, *validationBoard;
int fixedCells, rowIndex, columnIndex, isSolved;

enum commands {
    SET = 1,
    HINT = 2,
    VALIDATE = 3,
    RESET = 4,
    EXIT = 5
};

void createSolutionBoard(){
    solutionBoard = (int *) malloc(NUMBER_OF_COLUMNS * NUMBER_OF_ROWS * sizeof(int));
    assert(solutionBoard);
    if (solutionBoard == NULL) {
        printMallocError();
    }
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
            *(solutionBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) = 0;
        }
    }
}

void createGameBoard() {
    gameBoard = (int *) malloc(NUMBER_OF_COLUMNS * NUMBER_OF_ROWS * sizeof(int));
    if (gameBoard == NULL) {
        printMallocError();
    }
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
            *(gameBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) = *(solutionBoard + rowIndex * NUMBER_OF_COLUMNS +
                                                                          columnIndex);
        }
    }
}


int set(int column, int row, int value) {
    check = 1;
    --row, --column;
    if (*(gameBoard + row * NUMBER_OF_COLUMNS + column) < 0) {
        cellFixed();
        check = 0;
    } else if (!value) {
        *(gameBoard + row * NUMBER_OF_COLUMNS + column) = value;
    } else {
        if (validateSet(gameBoard, row, column, value)) {
            *(gameBoard + row * NUMBER_OF_COLUMNS + column) = value;
        } else {
            invalidValue();
            check = 0;
        }
    }
    return check;
}

void generatePuzzle(int numberOfFixed) {
    rowIndex = 0, columnIndex = 0;
    while (numberOfFixed > 0) {
        columnIndex = rand() % NUMBER_OF_ROWS;
        rowIndex = rand() % NUMBER_OF_COLUMNS;
        if (*(solutionBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) > 0) {
            *(solutionBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) *= -1;
            *(gameBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) *= -1;
            --numberOfFixed;
        }
    }
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
            if (*(solutionBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) > 0) {
                *(gameBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) = 0;
            }
        }
    }
}

void freeSpace() {
    free(gameBoard);
    free(solutionBoard);
}

void exitGame() {
    freeSpace();
    free(commandInput);
    printExit();
    exit(1);
}

void hint(int column, int row) {
    --row, --column;
    printf("Hint: set cell to %d\n", abs(*(solutionBoard + row * NUMBER_OF_COLUMNS + column)));
}


void validationToSoulution() {
    free(solutionBoard);
    createSolutionBoard();
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
            *(solutionBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) = abs(
                    *(validationBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex));
        }
    }
}

void createValidationBoard() {
    validationBoard = (int *) malloc(NUMBER_OF_COLUMNS * NUMBER_OF_ROWS * sizeof(int));
    if (validationBoard == NULL) {
        printMallocError();
    }
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
            *(validationBoard + rowIndex * NUMBER_OF_COLUMNS + columnIndex) = *(gameBoard +
                                                                                rowIndex * NUMBER_OF_COLUMNS +
                                                                                columnIndex);
        }
    }
}


void validateBoard() {
    createValidationBoard();
    isSolved = solver(validationBoard, "");
    if (!isSolved) {
        puzzleUnvalid();
    } else {
        validationToSoulution();
        puzzleValid();
    }
    free(validationBoard);

}




void initialization() {
    createSolutionBoard();
    solver(solutionBoard, RANDOM);
    createGameBoard();
    fixedCells = getNumberOfCells();
    generatePuzzle(fixedCells);
}


void resetBoard() {
    freeSpace();
    initialization();
    gameFull = 0;
}


void startGame() {
    commandInput = (int *) malloc(4 * sizeof(int));
    if (commandInput == NULL) {
        printMallocError();
    }
    initialization();
    printBoard(gameBoard);
    while (1) {
        getTurnCommand(gameFull, commandInput);
        if (commandInput == NULL) {
            return;
        }
        switch (commandInput[0]) {
            case SET:
                if (set(commandInput[1], commandInput[2], commandInput[3])){
                    printBoard(gameBoard);
                    if (isFinish(gameBoard)) {
                        puzzleSolved();
                        gameFull = 1;
                    }
                }
                break;
            case HINT:
                hint(commandInput[1], commandInput[2]);
                break;
            case VALIDATE:
                validateBoard();
                break;
            case RESET:
                resetBoard();
                printBoard(gameBoard);
                break;
            case EXIT:
                exitGame();
                break;
            default:
                break;

        }
    }
}

