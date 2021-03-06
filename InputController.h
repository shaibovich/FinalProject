
void getTurnCommand(int gameMode, int *commandArray, char *pathString);

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
    AUTO_FILL = 15
};
