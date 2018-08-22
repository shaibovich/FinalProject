//
// Created by Shai Leibovich on 22/08/2018.
//

#include <string.h>
#include <stdlib.h>
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
#define REGEX " \n\r\t"


enum commandsEnum {
    SET = 1,
    HINT = 2,
    VALIDATE = 3,
    RESET = 4,
    EXIT = 5,
    SOLVE = 6,
    EDIT = 7,
    MARK_ERROR = 8,
    PRINT_BOARD = 9,
    GENERATE = 10,
    UNDO = 11,
    REDO = 12,
    SAVE = 13,
    NUM_SOLUTIONS = 14,
    AUTI_FULL = 15
};

int numberOfCells = -1, isValidCommand;

char *tempInput, *command, *inputString;
int cnt = 0;

void validateCommand(int isFinish, int gameBoard, int *commandArray) {
    if (!strcmp(command, SET_OPTION) && !isFinish && cnt >= 4) {
        isValidCommand = 1;
        commandArray[0] = SET;
    } else if (!strcmp(command, HINT_OPTION) && !isFinish && cnt >= 3) {
        isValidCommand = 1;
        commandArray[0] = HINT;
    } else if (!strcmp(command, VALIDATE_OPTION) && !isFinish && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = VALIDATE;
    } else if (!strcmp(command, RESET_OPTION) && cnt >= 1) {
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
    } else if (!strcmp(command, MARK_ERROR_OPTION) && cnt >= 2) {
        isValidCommand = 1;
        commandArray[0] = MARK_ERROR;
    } else if (!strcmp(command, PRINT_BOARD_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = EDIT;
    } else if (!strcmp(command, GENERATE_OPTION) && cnt >= 3) {
        isValidCommand = 1;
        commandArray[0] = GENERATE;
    } else if (!strcmp(command, UNDO_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = UNDO;
    } else if (!strcmp(command, REDO_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = REDO;
    } else if (!strcmp(command, SAVE_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = SAVE;
    } else if (!strcmp(command, NUM_SOLUTIONS_OPTION) && cnt >= 2) {
        isValidCommand = 1;
        commandArray[0] = NUM_SOLUTIONS;
    } else if (!strcmp(command, AUTOFILL_OPTION) && cnt >= 1) {
        isValidCommand = 1;
        commandArray[0] = AUTI_FULL;
    } else {
        printInvalidCommand();
    }
}

void getTurnCommand(int isFinish, int gameMode, int *commandArray) {
    command = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    inputString = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    if (command == NULL || inputString == NULL) {
        // TODO: errorHandler on malloc
    }
    isValidCommand = 0;
    while (!isValidCommand) {
        if (feof(stdin)) {
            // TODO: Exit game
        }
        cnt = 0;
        fgets(inputString, NUMBER_OF_CHARS_INPUT, stdin);
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
                        commandArray[1] = (int) *tempInput - '0';
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
}

