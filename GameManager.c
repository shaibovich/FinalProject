//
// Created by Shai Leibovich on 20/08/2018.
//

#define TRUE 1
#define FALSE 0

#include <assert.h>
#include <stdlib.h>
#include "GameBoard.h"
#include "utils.h"
#include "LinkedList.h"
#include "InputController.h"
#include "GameManager.h"



int markErros;
int gameMode;
GameBoard *gameBoard;
//List gameList;
int *commandArray;

void initiliateGame() {
    gameMode = INIT_MODE;
    markErros = FALSE;
    commandArray = (int *) malloc(sizeof(int) * 4);
    assert(commandArray);

}


void solve(int x){
    gameMode = SOLVE_MODE;

}

void edit(int x){

}

void markError(int x){

}




void startGame() {
    printStartGame();
    initiliateGame();
    while (1) {
        getTurnCommand(0, gameMode, commandArray);
        switch (commandArray[0]) {
            case SET:
                break;
            case HINT:
                break;
            case RESET:
                break;
            case SOLVE:
                solve(commandArray[1]);
                break;
            case EDIT:
                edit(commandArray[1]);
                break;
            case MARK_ERROR:
                markError(commandArray[1]);
                break;
            case PRINT_BOARD:

                break;
            case GENERATE:
                break;
            case UNDO:
                break;
            case REDO:
                break;
            case SAVE:
                break;
            case NUM_SOLUTIONS:
                break;
            case AUTO_FILL:
                break;
            default:
                break;
        }
        return;
    }
}









