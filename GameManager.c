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
#include "sudokuSolver.h"

int gameMode, counter, check;
GameBoard *gameBoard, *tempBoard;
int *commandArray;
int isMark, oldValue;
char *filePath;
Node *node;
List *gameMoves;

void initiliateGame() {
    gameMode = INIT_MODE;
    isMark = FALSE;
    commandArray = (int *) malloc(sizeof(int) * 4);
    assert(commandArray);
    filePath = (char *) malloc(sizeof(char) * 1024);
    assert(filePath);
    gameMoves = createLinkedList();
}

void solve(char *path) {
    gameBoard = openGameBoardFromFile(path, SOLVE_MODE);
    if (gameBoard != NULL) {
        gameMode = SOLVE_MODE;
        printGameBoard(gameBoard, isMark);
    }

}

void edit(char *path) {
    if (!strcmp(path, "")) {
        gameBoard = createEmptyBoard(3, 3);
    } else {
        gameBoard = openGameBoardFromFile(path, EDIT_MODE);
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
    check = solveSudoko(gameBoard, tempBoard);
    deleteBoard(tempBoard);
    return check;
}

void generate(int x, int y) {
    counter = 0;
    if (!isBoardEmpty(gameBoard)) {
        printBoardNotEmpty();
    } else {
        for (counter = 0; counter < 1000; counter++) {
            if (!fillRandom(gameBoard, x)) {
                makeBoardEmpty(gameBoard);
            } else if (validate()) {
                clearRandom(gameBoard, y);
                return;
            } else {
                makeBoardEmpty(gameBoard);
            }
        }
        printGeneratorFailed();
    }
}

void startNewGame() {
    gameMode = INIT_MODE;
}

void set(int column, int row, int value) {
    column -= 1;
    row -= 1;
    oldValue = getCellValue(gameBoard, column, row);
    if (setValueToCell(gameBoard, column, row, value)!=ERROR) {
        addMove(gameBoard, gameMoves, row, column, oldValue);
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
    deleteLinkedList(gameMoves);
    free(filePath);
    free(commandArray);
    printExit();
    exit(1);
}

int doUndo(int isReset) {
    node = undoMove(gameMoves, isReset);
    if (node == NULL) {
        return 0;
    } else {
        setValueToCell(gameBoard, getNodeY(node), getNodeX(node), getNodePrevValue(node));
        return 1;
    }
}

void doRedo() {
    node = redoMove(gameMoves);
    if (node != NULL) {
        setValueToCell(gameBoard, getNodeY(node), getNodeX(node), getNodeValue(node));
    }

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
    fillGameBoard(gameBoard);
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
    printBoardReset();
}

void hint(int column, int row) {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else if (isCellFixed(gameBoard, column, row, 0)) {
        printCellIsFixed();
    } else if (getCellValue(gameBoard, column, row)) {
        printCellAlreadyContains();
    } else {
        tempBoard = copyGameBoard(gameBoard);
        if (solveSudoko(gameBoard, tempBoard)) {
            hintCell(getCellValue(tempBoard, column, row));
        } else {
            printBoardUnsolvedable();
        }
        deleteBoard(tempBoard);
    }
}


void startGame() {
    printStartGame();
    initiliateGame();
    while (1) {
        getTurnCommand(0, gameMode, commandArray, filePath);
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
                if (validate()){
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









