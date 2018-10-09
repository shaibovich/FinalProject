#include <stdio.h>

void printEnterCommand() {
    printf("Enter your command:\n");
}

void printCellIsFixed() {
    printf("Error: cell is fixed\n");
}

void printStartGame() {
    printf("Sudoku\n------\n");
}

void printInvalidCommand() {
    printf("ERROR: invalid command\n");
}

void printFilNotOpened(int isSolved) {
    if (isSolved) {
        printf("Error: File doesn’t exist or cannot be opened\n");
    } else {
        printf("Error: File cannot be opened\n");
    }

}

void printErrorValidation() {
    printf("Error: the value should be 0 or 1\n");
}

void printValueOutOfRange(int n) {
    printf("Error: value not in range 0-%d\n", n);
}

void printSolutionErroneous() {
    printf("Puzzle solution erroneous\n");
}

void printPuzzleSolved() {
    printf("Puzzle solved successfully\n");
}

void printBoardContainsError() {
    printf("Error: board contains erroneous values\n");
}

void printValidationPassed() {
    printf("Validation passed: board is solvable\n");
}

void printValidationFailed() {
    printf("Validation failed: board is unsolvable\n");
}

void printBoardNotEmpty() {
    printf("Error: board is not empty\n");
}

void printGeneratorFailed() {
    printf("Error: puzzle generator failed\n");
}

void printBoardUnsolvedable(){
    printf("Error: board is unsolvable\n");
}

void printNoMovesToUndo() {
    printf("Error: no moves to undo\n");
}

void printBoardValidationFailed(){
    printf("Error: board validation failed\n");
}

void printUndoValue(int x, int y, int oldValue, int newValue) {
    if (oldValue == 0 && newValue == 0) {
        printf("Undo %d,%d: from _ to _\n", x, y);
    } else if (oldValue == 0) {
        printf("Undo %d,%d: from _ to %d\n", x, y, newValue);
    } else if (newValue == 0) {
        printf("Undo %d,%d: from %d to _\n", x, y, oldValue);
    } else {
        printf("Undo %d,%d: from %d to %d\n", x, y, oldValue, newValue);
    }

}

void printNoMovesToRedo() {
    printf("Error: no moves to redo\n");
}

void printRedoValue(int x, int y, int oldValue, int newValue) {
    if (oldValue == 0 && newValue == 0) {
        printf("Redo %d,%d: from _ to _\n", x, y);
    } else if (oldValue == 0) {
        printf("Redo %d,%d: from _ to %d\n", x, y, newValue);
    } else if (newValue == 0) {
        printf("Redo %d,%d: from %d to _\n", x, y, oldValue);
    } else {
        printf("Redo %d,%d: from %d to %d\n", x, y, oldValue, newValue);
    }

}

void printFileCannotBeCreated() {
    printf("Error: File cannot be created or modified\n");
}

void printSaveTo(char *filePath) {
    printf("Saved to: %s\n", filePath);
}

void printCellAlreadyContains() {
    printf("Error: cell already contains a value\n");
}

void hintCell(int value) {
    printf("Hint: set cell to %d\n", value);
}

void printNumberOfsolutions(int num) {
    printf("Number of solutions: %d\n", num);
}

void printValueNotInRange2(int num){
    printf("Error: value not in range 1-%d\n", num);
}

void printGoodBoard() {
    printf("This is a good board!\n");
}

void printBadPuzzle() {
    printf("The puzzle has more than 1 solution, try to edit it further\n");
}

void printSetCell(int x, int y, int value) {
    printf("Cell <%d,%d> set to %d\n", x, y, value);
}

void printBoardReset() {
    printf("Board reset\n");
}

void printExit() {
    printf("Exiting...\n");
}


