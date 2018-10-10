/**
 * Game Manager Source File
 *
 * This file implements managing the game flow
 *
 */
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

/**
 * this function initiates the game variables and structures for the commands
 *
 */
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
/**
 * this function initiates a new gameboard so that gameboard is empty and so does gamemoves list (notice there is another function called "startGame" that handles moves)
 *
 */
void startNewGame() {
    gameMode = INIT_MODE;
    if (gameBoard != NULL) {
        deleteBoard(gameBoard);
        gameBoard = NULL;
    } else {
        deleteArray(gameMoves);
        gameMoves = NULL;
    }
    free(commandArray);
    free(filePath);
    initiateGame();
}

/**
 * This function checks if the Sudoku board is solvable
 *
 * @return 1 if board is solvable
 */

int validate() {
    check = 0;
    tempBoard = copyGameBoard(gameBoard);
    check = solveSudoko(gameBoard, tempBoard);
    deleteBoard(tempBoard);
    tempBoard = NULL;
    return check;


}

/**
 * This function is called when mode is SOLVE, it prints the opened sudoku board and initiats the list of moves
 *
 *
 * @param path of board to solve

 */

void solve(char *path) {
    gameMode = SOLVE_MODE;
    if (tempBoard != NULL) {
        deleteBoard(tempBoard);
        tempBoard = NULL;
    }
    tempBoard = openGameBoardFromFile(path, gameMode);
    if (tempBoard != NULL) {
        if (gameBoard != NULL) {
            deleteBoard(gameBoard);
            gameBoard = NULL;
        }
        if (gameMoves != NULL) {
            deleteArray(gameMoves);
            gameMoves = NULL;
        }
        gameBoard = tempBoard;
        updateBoardErrors(gameBoard);
        isMark = 1;
        gameMoves = createNewLinkedLists();
        printGameBoard(gameBoard, isMark);

    } else {
        gameMode = INIT_MODE;
    }
}

/**
 * This function is called when mode is EDIT
 *
 * @param path of board to solve

 */

void edit(char *path) {
    gameMode = EDIT_MODE;
    if (!strcmp(path, "")) {
        if (gameBoard != NULL) {
            deleteBoard(gameBoard);
            gameBoard = NULL;
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
                gameBoard = NULL;
            }
            gameBoard = tempBoard;
            tempBoard = NULL;

        }
        if (gameMoves != NULL) {
            deleteArray(gameMoves);
            gameMoves = NULL;
        }
    }
    gameMoves = createNewLinkedLists();
    isMark = 1;
    printGameBoard(gameBoard, isMark);
}

/**
 * This function validates the isMark parameter (checks that it's 1 or 0)
 *
 * @param mark - isMark parameter , changed in the function
 */
void markError(int mark) {
    if (mark != 0 && mark != 1) {
        printErrorValidation();
    } else {
        isMark = mark;
    }
}

/**
 * This function generates a gameBoard or thorws an Error that generator failed
 *
 * @param X- number of cells to randomly fill , Y- number of cells to keep full after generation
 */

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

/**
 * This function is called by startGame when command is SET
 * It validates parameters and cell condition (fixed or not) and sets new value into specified cell
 *
 * @param column,row - ints between 0-N, decreased by 1 (since array starts in 0 and not 1)
 *        value - an int between 0-N
 */

void set(int column, int row, int value) {
    column -= 1;
    row -= 1;
    oldValue = getCellValue(gameBoard, column, row);
    columnsLst[0] = column;
    rowsLst[0] = row;
    valueLst[0] = oldValue;
    if (value > getNumberOfRows(gameBoard)||value <0||oldValue == ERROR) {
        printValueOutOfRange(getNumberOfRows(gameBoard));
    }
    else if (!validateCellFixed(gameBoard, column, row)){
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

/**
 * This function is called by startGame when command is EXIT
 * It deletes gameBoard, list of moves, frees all allocated memory and exits the game
 *
 */

void exitGame() {
    if (gameBoard != NULL) {
        deleteBoard(gameBoard);
        gameBoard = NULL;
    }
    if (gameMoves != NULL) {
        deleteArray(gameMoves);
        gameMoves = NULL;
    }
    free(filePath);
    free(commandArray);
    printExit();
    exit(1);
}

/**
 * This function Undos a move.
 * It calls the relevant function from LinkedList class
 *
 * @param isReset - 1 if was called from RESET
 * @return 1 if undo succeeded and 0 if no moves to undo
 */

int doUndo(int isReset) {
    return undoMoves(gameBoard, gameMoves, isReset, isMark);
}

/**
 * This function redos a move.
 * It calls the relevant function from LinkedList class
 *
 */

void doRedo() {
    redoMoves(gameBoard, gameMoves, isMark, 0);
}

/**
 * This function uses validates and calls saving function for gameboard into a file
 *
 * @param path -  destination path for saving
 */

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
        if (saveFile(path, gameBoard)) {
            printSaveTo(path);
        }
    } else if (gameMode == SOLVE_MODE) {
        if (saveFile(path, gameBoard)) {
            printSaveTo(path);
        }
    }


}

/**
 * This function autofills obvious values
 * in case of a full board - it prints that board is full and in case board or solution is erroneous - is prints so.
 *
 */

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

/**
 * This function prints the number of possible solutions for this ganeboard
 *
 */

void numSolutions() {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else {
        int numberOfSols = numberOfSolves(gameBoard);
        printNumberOfsolutions(numberOfSols);
        if (numberOfSols == 1) {
            printGoodBoard();
        } else if (numberOfSols != 0){
            printBadPuzzle();
        }
    }

}
/**
 * This function Resets the board to its initial state by Undo'ing all of the moves .
 */

void resetBoard() {
    int value;
    do {
        value = doUndo(1);
    } while (value);
    printGameBoard(gameBoard, 0);
    printBoardReset();

}

/**
 * This function fills requested cell with solutions value, or if not possible - prints a relevant error
 *
 * @param column, row - of the requested cell for hint
 */

void hint(int column, int row) {
    if (checkBoardErrors(gameBoard)) {
        printBoardContainsError();
    } else if (column > getNumberOfColumns(gameBoard) || row > getNumberOfColumns(gameBoard)) {
        printValueNotInRange2(getNumberOfColumns(gameBoard));
    } else if (isCellFixed(gameBoard, column - 1, row - 1, 1)) {
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
        tempBoard = NULL;
    }
}

/**
 * This function manages game flow by referring commands to their relevant functions .
 *
 */

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









