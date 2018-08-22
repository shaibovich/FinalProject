#define NUMBER_OF_CHARS_INPUT 1024
#define SET_OPTION "set"
#define HINT_OPTION "hint"
#define VALIDATE_OPTION "validate"
#define RESET_OPTION "restart"
#define EXIT_OPTION "exit"
#define REGEX " \n\r\t"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../HomeWork1/MainAux.h"
#include "../HomeWork1/Game.h"

int numberOfCells = -1, isValidCommand;

char *tempInput, *command, *inputString;
int cnt = 0;

enum commandsEnum {
    SET = 1,
    HINT = 2,
    VALIDATE = 3,
    RESET = 4,
    EXIT = 5
};


int validateCellsNumber(int num) {
    return num >= 0 && num <= 80;
}


int getNumberOfCells() {
    numberOfCells = -1;
    do {
        printNumberOfCellsInput();
        if (scanf("%d", &numberOfCells) != 1) {
            printErrorScanf();
            exit(1);
        } else {
            if (!validateCellsNumber(numberOfCells)) {
                printUnvalidCell();
            }
        }

    } while (!validateCellsNumber(numberOfCells));
    return numberOfCells;
}

void validateCommand(int isFinish, int *commandArray) {
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
    } else {
        printInvalidCommand();
    }
}

void getTurnCommand(int isFinish, int *commandArray) {
    command = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    inputString = (char *) malloc(NUMBER_OF_CHARS_INPUT * sizeof(char));
    if (command == NULL || inputString == NULL) {
        printMallocError();
    }
    isValidCommand = 0;
    while (!isValidCommand) {
        if (feof(stdin)) {
            exitGame();
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
            validateCommand(isFinish, commandArray);
        }
    }
    free(command);
    free(inputString);
}



