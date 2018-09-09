
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "utils.h"

#define NUMBER_OF_CHARS_INPUT 1024
#define SET_OPTION "set"
#define HINT_OPTION "hint"
#define VALIDATE_OPTION "validate"
#define EXIT_OPTION "exit"
#define EDIT_OPTION "edit"
#define MARK_ERROR_OPTION "mark_errors"
#define PRINT_BOARD_OPTION "print_board"
#define GENERATE_OPTION "generate"
#define UNDO_OPTION "undo"
#define REDO_OPTION "redo"
#define SAVE_OPTION "save"
#define NUM_SOLUTIONS_OPTION "num_solutions"
#define AUTOFILL_OPTION "autofill"
#define SOLVE_OPTION "solve"
#define RESET_OPTION "reset"
#define REGEX " \n\r\t"

#include "InputController.h"
#include "GameManager.h"


int isValidCommand;

char *tempInput, *command, *inputString;
int cnt = 0;


int isSolveMode(int gameMode) {
    return gameMode == SOLVE_MODE;
}

int isSolveOrEditMode(int gameMode) {
    return gameMode == SOLVE_MODE || gameMode == EDIT_MODE;
}

int isEditMode(int gameMode) {
    return gameMode == EDIT_MODE;
}

void validateCommand(int isFinish, int gameMode, int *commandArray) {
    if (!strcmp(command, SET_OPTION) && !isFinish && cnt >= 4 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = SET;
    } else if (!strcmp(command, HINT_OPTION) && !isFinish && cnt >= 3 && isSolveMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = HINT;
    } else if (!strcmp(command, VALIDATE_OPTION) && !isFinish && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = VALIDATE;
    } else if (!strcmp(command, RESET_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = RESET;
    } else if (!strcmp(command, EXIT_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = EXIT;
    } else if (!strcmp(command, SOLVE_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = SOLVE;
    } else if (!strcmp(command, EDIT_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = EDIT;
    } else if (!strcmp(command, MARK_ERROR_OPTION) && cnt >= 2 && isSolveMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = MARK_ERROR;
    } else if (!strcmp(command, PRINT_BOARD_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = PRINT_BOARD;
    } else if (!strcmp(command, GENERATE_OPTION) && cnt >= 3 && isEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = GENERATE;
    } else if (!strcmp(command, UNDO_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = UNDO;
    } else if (!strcmp(command, REDO_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = REDO;
    } else if (!strcmp(command, SAVE_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = SAVE;
    } else if (!strcmp(command, NUM_SOLUTIONS_OPTION) && cnt >= 2 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = NUM_SOLUTIONS;
    } else if (!strcmp(command, AUTOFILL_OPTION) && cnt >= 1 && isSolveMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = AUTO_FILL;
    } else {
        printInvalidCommand();
    }
}

void getTurnCommand(int isFinish, int gameMode, int *commandArray, char *pathString) {
//    printf("isSolved: %d, GameMode %d, CommandArray0 %d, CommandArray1 %d, CommandArray2 %d, FilePath %s", isFinish, gameMode, commandArray[0], commandArray[1], commandArray[2], pathString);
    command = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    tempInput = (char*) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    inputString = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    assert(command);
    assert(inputString);
    assert(tempInput);
    if (command == NULL || inputString == NULL || tempInput == NULL) {
        exit(1);
    }
    isValidCommand = 0;
    printEnterCommand();
    while (!isValidCommand) {
        if (feof(stdin)) {
            return;
        }
        cnt = 0;
//        printf("here");
        fgets(inputString, NUMBER_OF_CHARS_INPUT, stdin);
        printf("InputString: %s", inputString);
        if (tempInput != NULL){
            printf("%s", tempInput);
        }
        tempInput = strtok(inputString, REGEX);
//        printf("TempInput: %s", tempInput);
        if (tempInput == NULL) {
            continue;
        } else {
            while (tempInput != NULL) {
                switch (cnt) {
                    case 0:
//                        printf("TempInput in switch: %s", tempInput);
                        strcpy(command, tempInput);
                        break;
                    case 1:
                        if (!strcmp(command, SAVE_OPTION) || !strcmp(command, EDIT_OPTION) ||
                            !strcmp(command, SOLVE_OPTION)) {
                            strcpy(pathString, tempInput);
                        } else {
                            commandArray[1] = (int) *tempInput - '0';
                        }
                        break;
                    case 2:
                        commandArray[2] = (int) *tempInput - '0';
                        break;
                    case 3:
                        commandArray[3] = (int) *tempInput - '0';
                    default:
                        break;
                }
                tempInput = strtok(NULL, REGEX);
                ++cnt;
            }

            validateCommand(isFinish, gameMode, commandArray);
        }
    }
    free(command);
    free(inputString);
    free(tempInput);
}

