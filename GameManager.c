#define FALSE 0
#define TRUE 1

#include <assert.h>
#include <stdlib.h>

#include <string.h>
#include "utils.h"
#include "LinkedList.h"
#include "InputController.h"
#include "GameManager.h"
#include "FileController.h"
#include "GameBoardClass.h"
#include "exhaustive.h"
#include "sudokuSolver.h"

int gameMode, counter, check;
GameBoard *gameBoard, *tempBoard;
int *commandArray, columnsLst[1], rowsLst[1], valueLst[1];
int isMark, oldValue;
List *generateLst;
char *filePath;
Node *node;
ListofLists *gameMoves;

void initiateGame() {
    gameMode = INIT_MODE;
    isMark = TRUE;
    commandArray = (int *) malloc(sizeof(int) * 4);
    assert(commandArray);
    filePath = (char *) malloc(sizeof(char) * 1024);
    assert(filePath);
    gameMoves = NULL;
    gameBoard = NULL;
    tempBoard = NULL;
}

void startNewGame() {
    gameMode = INIT_MODE;
    if (gameBoard != NULL) {
        deleteBoard(gameBoard);
    } else {
        deleteArray(gameMoves);
    }
    free(commandArray);
    free(filePath);
    initiateGame();
}

int validate() {
    check = 0;
    tempBoard = copyGameBoard(gameBoard);
    check = solveSudoko(gameBoard, tempBoard);
    deleteBoard(tempBoard);
    tempBoard = NULL;
    return check;


}


void solve(char *path) {
    gameMode = SOLVE_MODE;
    if (tempBoard != NULL) {
        deleteBoard(tempBoard);
    }
    tempBoard = openGameBoardFromFile(path, gameMode);
    if (tempBoard != NULL) {
        if (gameBoard != NULL) {
            deleteBoard(gameBoard);
        }
        if (gameMoves != NULL) {
            deleteArray(gameMoves);
        }
        gameBoard = tempBoard;
        updateBoardErrors(gameBoard);
        isMark = 1;
        gameMoves = createNewLinkedLists();
        printGameBoard(gameBoard, isMark);

    } else {
        gameMode = INIT_MODE;
    }
    tempBoard = NULL;
}

void edit(char *path) {
    gameMode = EDIT_MODE;
    if (!strcmp(path, "")) {
        if (gameBoard != NULL) {
            deleteBoard(gameBoard);
        }
        gameBoard = createEmptyBoard(3, 3);
    } else {
        tempBoard = openGameBoardFromFile(path, gameMode);
        if (tempBoard == NULL) {
            gameMode = INIT_MODE;
            return;
        } else {
            if (gameBoard != NULL) {
                deleteBoard(gameBoard);
            }
            gameBoard = tempBoard;
            tempBoard = NULL;

        }
        if (gameMoves != NULL) {
            deleteArray(gameMoves);
        }
    }
    gameMoves = createNewLinkedLists();

    isMark = 1;
    printGameBoard(gameBoard, isMark);
}

void markError(int mark) {
    if (mark != 0 && mark != 1) {
        printErrorValidation();
    } else {
        isMark = mark;
    }
}


void generate(int x, int y) {
    if (x > getNumberOfRows(gameBoard) || y > getNumberOfRows(gameBoard)) {
        printValueOutOfRange(getNumberOfEmptyCells(gameBoard));
        return;
    }
    counter = 0;
    generateLst = createLinkedList();
    if (!isBoardEmpty(gameBoard)) {
        printBoardNotEmpty();
    } else if (x < y) {
        printGeneratorFailed();
    } else if (x == y) {
        return;
    } else {
        for (counter = 0; counter < 1000; counter++) {
            if (!fillRandom(gameBoard, x, generateLst)) {
                makeBoardEmpty(gameBoard);
                emptyLst(generateLst);
            } else if (validate()) {
                clearRandom(gameBoard, x - y, generateLst);
                addMovesFromList(gameMoves, generateLst);
                return;
            } else {
                makeBoardEmpty(gameBoard);
            }
        }
        printGeneratorFailed();
    }
    deleteLinkedList(generateLst);
}


void set(int column, int row, int value) {
    if (value > getNumberOfRows(gameBoard)) {
        printValueOutOfRange(getNumberOfRows(gameBoard));
    }
    column -= 1;
    row -= 1;
    oldValue = getCellValue(gameBoard, column, row);
    columnsLst[0] = column;
    rowsLst[0] = row;
    valueLst[0] = oldValue;
    if (!validateCellFixed(gameBoard, column, row)){
        printCellIsFixed();
    } else if (getCellValue(gameBoard, column, row) == value) {
        printGameBoard(gameBoard, isMark);
    } else if (setValueToCell(gameBoard, column, row, value) != ERROR) {
        addMoves(gameBoard, gameMoves, rowsLst, columnsLst, valueLst, 1);
        printGameBoard(gameBoard, isMark);

        if (isBoardFull(gameBoard)) {
            if (validate()) {
                printPuzzleSolved();
                startNewGame();
            } else {
                printSolutionErroneous();
            }
        }

    }
}

void exitGame() {
    if (gameBoard != NULL) {
        deleteBoard(gameBoard);
    }
    if (gameMoves != NULL) {
        deleteArray(gameMoves);
    }
    free(filePath);
    free(commandArray);
    printExit();
    exit(1);
}

int doUndo(int isReset) {
    return undoMoves(gameBoard, gameMoves, isReset, isMark);
}

void doRedo() {
    redoMoves(gameBoard, gameMoves, isMark, 0);
}

void save(char *path) {
    if (gameMode == EDIT_MODE) {
        if (checkBoardErrors(gameBoard)) {
            printBoardContainsError();
            return;
        } else if (!validate()) {
            printBoardValidationFailed();
            return;
        }
        setAllFilledFixed(gameBoard);
        if (saveFile(filePath, gameBoard)) {
            printSaveTo(path);
        }
    } else if (gameMode == SOLVE_MODE) {
        if (saveFile(filePath, gameBoard)) {
            printSaveTo(path);
        }
    }


}

void autoFill() {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else {
        fillGameBoard(gameBoard, gameMoves);
        if (isBoardFull(gameBoard)) {
            if (validate()) {
                printPuzzleSolved();
                startNewGame();
            } else {
                printSolutionErroneous();
            }
        } else {
            printGameBoard(gameBoard, isMark);
        }
    }

}

void numSolutions() {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else {
        int numberOfSols = numberOfSolves(gameBoard);
        printNumberOfsolutions(numberOfSols);
        if (numberOfSols == 1) {
            printGoodBoard();
        } else {
            printBadPuzzle();
        }
    }

}

void resetBoard() {
    int value;
    do {
        value = doUndo(1);
    } while (value);
    printGameBoard(gameBoard, 0);
    printBoardReset();

}

void hint(int column, int row) {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else if (column > getNumberOfColumns(gameBoard) || row > getNumberOfColumns(gameBoard)) {
        printValueNotInRange2(getNumberOfColumns(gameBoard));
    } else if (isCellFixed(gameBoard, column - 1, row - 1, 0)) {
        printCellIsFixed();
    } else if (getCellValue(gameBoard, column - 1, row - 1)) {
        printCellAlreadyContains();
    } else {
        tempBoard = copyGameBoard(gameBoard);
        if (solveSudoko(gameBoard, tempBoard)) {
            hintCell(getCellValue(tempBoard, column - 1, row - 1));
        } else {
            printBoardUnsolvedable();
        }
        deleteBoard(tempBoard);
    }
}


void startGame() {
    printStartGame();
    initiateGame();
    while (1) {
        getTurnCommand(gameMode, commandArray, filePath);
        switch (commandArray[0]) {
            case SET:
                set(commandArray[1], commandArray[2], commandArray[3]);
                break;
            case HINT:
                hint(commandArray[1], commandArray[2]);
                break;
            case RESET:
                resetBoard();
                break;
            case SOLVE:
                solve(filePath);
                break;
            case EDIT:
                edit(filePath);
                break;
            case MARK_ERROR:
                markError(commandArray[1]);
                break;
            case PRINT_BOARD:
                printGameBoard(gameBoard, isMark);
                break;
            case GENERATE:
                generate(commandArray[1], commandArray[2]);
                break;
            case UNDO:
                doUndo(0);
                break;
            case REDO:
                doRedo();
                break;
            case SAVE:
                save(filePath);
                break;
            case NUM_SOLUTIONS:
                numSolutions();
                break;
            case AUTO_FILL:
                autoFill();
                break;
            case VALIDATE:
                if (checkBoardErrors(gameBoard)) {
                    printBoardContainsError();
                } else if (validate()) {
                    printValidationPassed();
                } else {
                    printValidationFailed();
                }
                break;
            case EXIT:
                exitGame();
                break;
            default:
                break;
        }

    }
}









