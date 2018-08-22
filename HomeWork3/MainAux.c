#include <stdio.h>
#include <stdlib.h>


#define NUMBER_OF_COLUMNS 9
#define NUMBER_OF_ROWS 9
#define BLOCK_CELL_ROW 3
#define BLOCK_CELL_COLUMN 3


int rowIndex, columnIndex, rowBlock, columnBlock;


int validateSet(const int *board, int row, int column, int value) {
    rowBlock = 0;
    columnBlock = 0;
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        if (rowIndex != row && abs(*(board + rowIndex * NUMBER_OF_COLUMNS + column)) == value) {
            return 0;
        }
    }
    for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
        if (columnIndex != column && abs(*(board + row * NUMBER_OF_COLUMNS + columnIndex)) == value) {
            return 0;
        }
    };
    rowBlock= (row / BLOCK_CELL_ROW) * BLOCK_CELL_ROW;
    columnBlock = (column / BLOCK_CELL_COLUMN) * BLOCK_CELL_COLUMN;
    for (rowIndex = 0; rowIndex < BLOCK_CELL_ROW; ++rowIndex) {
        for (columnIndex = 0; columnIndex< BLOCK_CELL_COLUMN; ++columnIndex) {
            if (abs(*(board + (rowIndex + rowBlock) * NUMBER_OF_COLUMNS + (columnIndex + columnBlock))) == value && (rowIndex+rowBlock) != row && (columnBlock+columnIndex) != column) {
                return 0;
            }
        }
    }
    return 1;
}

void printBoard(const int *arr) {
    for (rowIndex = 0; rowIndex < NUMBER_OF_COLUMNS; ++rowIndex) {
        if (rowIndex % BLOCK_CELL_COLUMN == 0) {
            printf("----------------------------------\n");
        }
        for (columnIndex = 0; columnIndex < NUMBER_OF_ROWS; ++columnIndex) {
            if (columnIndex % BLOCK_CELL_ROW == 0) {
                printf("| ");
            }
            if (*(arr + rowIndex * NUMBER_OF_COLUMNS + columnIndex) < 0) {
                printf(".");
            } else {
                printf(" ");
            }
            if (*(arr + rowIndex * NUMBER_OF_COLUMNS + columnIndex) == 0) {
                printf("  ");
            } else {
                printf("%d ", abs(*(arr + rowIndex * NUMBER_OF_COLUMNS + columnIndex)));
            }
        }
        printf("|");
        printf("\n");
    }
    printf("----------------------------------\n");
}

int isFinish(int *arr) {
    for (rowIndex = 0; rowIndex < NUMBER_OF_ROWS; ++rowIndex) {
        for (columnIndex = 0; columnIndex < NUMBER_OF_COLUMNS; ++columnIndex) {
            if (*(arr + rowIndex * NUMBER_OF_COLUMNS + columnIndex) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void printNumberOfCellsInput() {
    printf("Please enter the number of cells to fill [0-80]:\n");
}

void printErrorScanf() {
    printf("Error: scanf has failed\n");
}

void printUnvalidCell() {
    printf("Error: Invalid number of cells to fill (should be between 0 and 80)\n");
}

void printMallocError() {
    printf("Error: malloc has failed\n");
    exit(1);
}

void puzzleValid() {
    printf("Validation passed: board is solvable\n");
}

void puzzleUnvalid() {
    printf("Validation failed: board is unsolvable\n");
}

void printExit() {
    printf("Exiting...\n");
}

void cellFixed() {
    printf("Error: cell is fixed\n");
}

void puzzleSolved() {
    printf("Puzzle solved successfully\n");
}

void invalidValue() {
    printf("Error: value is invalid\n");
}


void printInvalidCommand() {
    printf("Error: invalid command\n");
}



