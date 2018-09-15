#define FALSE 0
#define TRUE 1

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "LinkedList.h"
#include "InputController.h"
#include "GameManager.h"
#include "FileController.h"
#include "exhaustive.h"
//#include "sudokuSolver.h"

int gameMode, counter, check;
GameBoard *gameBoard, *tempBoard;
int *commandArray, columnsLst[1], rowsLst[1], valueLst[1];
int isMark, oldValue, isFinish, withStar;
List * generateLst;
char *filePath;
Node *node;
ListofLists *gameMoves;

void startNewGame() {
    gameMode = INIT_MODE;
}

void initiateGame() {
    gameMode = INIT_MODE;
    isMark = FALSE;
    isFinish = 0;
    commandArray = (int *) malloc(sizeof(int) * 4);
    assert(commandArray);
    filePath = (char *) malloc(sizeof(char) * 1024);
    assert(filePath);
    gameMoves = createNewLinkedLists();
}

void solve(char *path) {
    gameBoard = openGameBoardFromFile(path, SOLVE_MODE);
    if (gameBoard != NULL) {
        if (isBoardFull(gameBoard)) {
            startNewGame();
        } else {
            gameMode = SOLVE_MODE;
            printGameBoard(gameBoard, isMark);
        }
    }
}

void edit(char *path) {
    if (!strcmp(path, "")) {
        gameBoard = createEmptyBoard(3, 3);
    } else {
        gameBoard = openGameBoardFromFile(path, EDIT_MODE);
        if (gameBoard != NULL && isBoardFull(gameBoard)) {
            gameMode = INIT_MODE;
            return;

        }
    }
    gameMode = EDIT_MODE;
    printGameBoard(gameBoard, EDIT_MODE);
}

void markError(int mark) {
    if (mark != 0 && mark != 1) {
        printErrorValidation();
    } else {
        isMark = mark;
    }
}

int validate() {
    check = 0;

    tempBoard = copyGameBoard(gameBoard);
//    check = solveSudoko(gameBoard, tempBoard);
    deleteBoard(tempBoard);
    return check;
}

void generate(int x, int y) {
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
                clearRandom(gameBoard, y, generateLst);
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
    withStar = 0;
    column -= 1;
    row -= 1;
    oldValue = getCellValue(gameBoard, column, row);

    columnsLst[0] = column;
    rowsLst[0] = row;
    valueLst[0] = value;
    if (setValueToCell(gameBoard, column, row, value) != ERROR) {
        addMoves(gameBoard, gameMoves, rowsLst, columnsLst, valueLst, 1);
        if (isMark == 1 || gameMode == EDIT_MODE) {
            withStar = 1;
        }
        printGameBoard(gameBoard, withStar);
        if (checkBoardErrors(gameBoard) && gameMode == SOLVE_MODE) {
            printSolutionErroneous();
        } else {
            if (isBoardFull(gameBoard)) {
                printPuzzleSolved();
                startNewGame();
            }
        }
    }
}

void exitGame() {
    deleteBoard(gameBoard);
    deleteArray(gameMoves);
    free(filePath);
    free(commandArray);
    printExit();
    exit(1);
}

int doUndo(int isReset) {
    return undoMoves(gameBoard, gameMoves, isReset, withStar);
}

void doRedo() {
    redoMoves(gameBoard, gameMoves, withStar);
//    printGameBoard(gameBoard, (isMark || gameMode == EDIT_MODE));

}

void save(char *path) {
    if (gameMode == EDIT_MODE) {
        if (checkBoardErrors(gameBoard)) {
            printBoardContainsError();
            return;
        } else {
            if (checkBoardErrors(gameBoard)) {
                printFilNotOpened(1);
                return;
            }
        }
        setAllFilledFixed(gameBoard);
    }
    if (saveFile(filePath, gameBoard, gameMode)) {
        printSaveTo(path);
    }

}

void autoFill() {
    fillGameBoard(gameBoard, gameMoves);
    printGameBoard(gameBoard, isMark);
}

void numSolutions() {
    int numberOfSols = numberOfSolves(gameBoard);
    printNumberOfsolutions(numberOfSols);
    if (numberOfSols == 1) {
        printGoodBoard();
    } else {
        printBadPuzzle();
    }
}

void resetBoard() {
    int value;
    do {
        value = doUndo(1);
    } while (value);
    printGameBoard(gameBoard,0);
    printBoardReset();

}

void hint(int column, int row) {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else if (isCellFixed(gameBoard, column-1, row-1, 0)) {
        printCellIsFixed();
    } else if (getCellValue(gameBoard, column-1, row-1)) {
        printCellAlreadyContains();
    } else {
        tempBoard = copyGameBoard(gameBoard);
//        if (solveSudoko(gameBoard, tempBoard)) {
//            printGameBoard(tempBoard, 0);
//            hintCell(getCellValue(tempBoard, column-1, row-1));
//        } else {
//            printBoardUnsolvedable();
//        }
        deleteBoard(tempBoard);
    }
}


void startGame() {
    printStartGame();
    initiateGame();
    while (1) {
        getTurnCommand(isFinish, gameMode, commandArray, filePath);
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
                printGameBoard(gameBoard, commandArray[1]);
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
                printGameBoard(tempBoard, isMark);
                if (validate()) {
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









