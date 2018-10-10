/**
 * Input Controller Source File
 *
 * This file implements managing the fetching of commands entered by the user, as well validating and converting the input to the
 * relevant command structs.
 *
 */


#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
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
#define REGEX " \t\r\n"

#include "InputController.h"
#include "GameManager.h"


int isValidCommand;

char *tempInput, *command, *inputString;
int cnt = 0, isLastInput;


/**
 * This function returns a boolean which indicate if the game mode is solve
 *
 * @param gameMode - int, indicate which gameMode
 * @return 1 if gameMode == SOLVE_MODE
 */
int isSolveMode(int gameMode) {
    return gameMode == SOLVE_MODE;
}

/**
 * This function returns a boolean which indicate if the game mode is solve or edit
 *
 * @param gameMode - int, indicate which gameMode
 * @return 1 if gameMode is SOLVE_MODE or EDIT_MODE
 */
int isSolveOrEditMode(int gameMode) {
    return gameMode == SOLVE_MODE || gameMode == EDIT_MODE;
}

/**
 * This function returns a boolean which indicate if the game mode is edit
 *
 * @param gameMode - int, indicate which gameMode
 * @return 1 if gameMode == EDIT_MODE
 */
int isEditMode(int gameMode) {
    return gameMode == EDIT_MODE;
}


/**
 * This function empty the string buffer if the input is bigger than 256
 *
 */
void emptyBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/**
 * This function validate the input and filling the commandArray with the command and inputs specified by the user
 *
 * @param gameMode - int, indicate which gameMode
 * @param commandArray - int array - describing the command and the relevant input
 */
void validateCommand(int gameMode, int *commandArray) {
    if (!strcmp(command, SET_OPTION) && cnt >= 4 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = SET;
    } else if (!strcmp(command, HINT_OPTION) && cnt >= 3 && isSolveMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = HINT;
    } else if (!strcmp(command, VALIDATE_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = VALIDATE;
    } else if (!strcmp(command, RESET_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = RESET;
    } else if (!strcmp(command, EXIT_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = EXIT;
    } else if (!strcmp(command, SOLVE_OPTION) && cnt >= 2) {
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
    } else if (!strcmp(command, NUM_SOLUTIONS_OPTION) && cnt >= 1 && isSolveOrEditMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = NUM_SOLUTIONS;
    } else if (!strcmp(command, AUTOFILL_OPTION) && cnt >= 1 && isSolveMode(gameMode)) {
        isValidCommand = 1;
        commandArray[0] = AUTO_FILL;
    } else {
        printInvalidCommand();
    }
}

/**
 * This function fetch an input from the user, validate and filling the commandArray if the input is correct.
 *
 * @param gameMode - int, indicate which gameMode
 * @param commandArray - int array, describing the command and the relevant input
 * @param pathString - String, for commands save, edit and solve - the pathString indicate for the file location.
 */
void getTurnCommand(int gameMode, int *commandArray, char *pathString) {
    strcpy(pathString, "");
    command = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    inputString = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    assert(command);
    assert(inputString);
    isValidCommand = 0;

    while (!isValidCommand) {
        if (feof(stdin)) {
            free(command);
            free(inputString);
            exitGame();
        }
        printEnterCommand();
        cnt = 0;
        fgets(inputString, 270, stdin);
        while (strlen(inputString) > 256) {
            emptyBuffer();
        }
        tempInput = strtok(inputString, REGEX);
        if (tempInput == NULL) {
            continue;
        } else {
            while (tempInput != NULL) {
                switch (cnt) {
                    case 0:
                        strcpy(command, tempInput);
                        break;
                    case 1:
                        if (!strcmp(command, SAVE_OPTION) || !strcmp(command, EDIT_OPTION) ||
                            !strcmp(command, SOLVE_OPTION)) {
                            strcpy(pathString, tempInput);
                        } else {
                            sscanf(tempInput, "%d", &commandArray[1]);
                        }
                        break;
                    case 2:
                        sscanf(tempInput, "%d", &commandArray[2]);
                        break;
                    case 3:
                        sscanf(tempInput, "%d", &commandArray[3]);
                    default:
                        break;
                }
                tempInput = strtok(NULL, REGEX);
                ++cnt;
            }
            validateCommand(gameMode, commandArray);
        }
    }
    free(command);
    free(inputString);
}

