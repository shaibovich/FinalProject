#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../HomeWork1/MainAux.h"

#define NUMBER_OF_ROWS 9
#define NUMBER_OF_COLUMNS 9
#define RANDOM "random"
int FIRST_CELL_I;
int FIRST_CELL_J;
int UNFIXED;
int r, i, j, counter, inner_counter, one, randomNum;
int cell[2];
int solved;
int initi;
int *sit_mat, *innerCounterLst;


void first_unfixed_cell(int *arr) {
    FIRST_CELL_I = 0;
    FIRST_CELL_J = 0;
    UNFIXED = 0;
    i = 0;
    j = 0;
    initi = 0;
    for (i = 0; i < NUMBER_OF_ROWS; i++) {
        for (j = 0; j < NUMBER_OF_COLUMNS; j++) {
            if (*(arr + i * NUMBER_OF_COLUMNS + j) == 0 && initi == 0) {
                FIRST_CELL_I = i;
                FIRST_CELL_J = j;
                initi = 1;
            }
            if (*(arr + i * NUMBER_OF_COLUMNS + j) < 0) {
                UNFIXED += 1;
            }
        }
    }
    UNFIXED = NUMBER_OF_ROWS * NUMBER_OF_COLUMNS - UNFIXED;
}

void next_unfixed_cell(int *arr, int i, int j) {
    if (j == (NUMBER_OF_COLUMNS - 1)) {
        j = 0;
        i = i + 1;
    } else {
        j += 1;
    }
    while (*(arr + i * NUMBER_OF_COLUMNS + j) != 0) {
        if (j == (NUMBER_OF_COLUMNS - 1)) {
            j = 0;
            i = i + 1;
        } else {
            j += 1;
        }
    }
    cell[0] = i;
    cell[1] = j;
}

int condition_check(int *arr, int i, int j, char *R) {
    if (!strcmp(RANDOM, R)) {
        if (*(arr + i * NUMBER_OF_COLUMNS + j) != 0) {
            if (*(innerCounterLst + counter) == 1){
                one = 1;
            }
            return 1;
        }
        inner_counter = 0;
        for (r = 1; r <= 9; r++) {
            *(arr + i * NUMBER_OF_COLUMNS + j) = r;
            if (validateSet(arr, i, j, *(arr + i * NUMBER_OF_COLUMNS + j))) {
                *(sit_mat + 9 * counter + inner_counter) = r;
                inner_counter++;
            }
            *(arr + i * NUMBER_OF_COLUMNS + j) = 0;
        }
        *(innerCounterLst + counter) = inner_counter;   
        if (inner_counter > 0) {
            if (inner_counter == 1) {
                one = 1;
            } else {
                one = 0;
            }
            return 1;
        }
        return 0;
    } else {
        if (abs(*(arr + i * NUMBER_OF_COLUMNS + j)) != 9) {
            return 1;
        }
    }
    return 0;
}


int solver_rec(int *arr, int i, int j, char *R) {
    while (condition_check(arr, i, j, R)) {
        if (!strcmp(RANDOM, R)) {
            if (one == 1) {
                *(arr + i * NUMBER_OF_COLUMNS + j) = *(sit_mat + 9 * counter);
                *(sit_mat + 9 * counter) = 0;
                *(innerCounterLst + counter) = 0;
                one = 0;
            } else {
                if (*(innerCounterLst + counter) <= 0) {
                    break;
                }
                randomNum = (rand() % (*(innerCounterLst + counter)));
                *(arr + i * NUMBER_OF_COLUMNS + j) = *(sit_mat + 9 * counter + randomNum);
                for (r  = randomNum ; r < *(innerCounterLst+ counter)-1 ; ++r){
                    *(sit_mat + 9 * counter + r) = *(sit_mat + 9 * counter + r+ 1);
                }
                *(sit_mat+ 9 * counter+ *(innerCounterLst+ counter)) = 0;
                *(innerCounterLst + counter) -= 1;
                randomNum = 0;
            }
        } else {
            *(arr + i * NUMBER_OF_COLUMNS + j) += 1;
        }
        if (validateSet(arr, i, j, *(arr + i * NUMBER_OF_COLUMNS + j))) {
            if (isFinish(arr)) {
                return 1;
            } else {
                next_unfixed_cell(arr, i, j);
                counter += 1;
                if (solver_rec(arr, cell[0], cell[1], R)) {
                    return 1;
                }
                counter -= 1;
            }
        }
    }
    *(arr + i * NUMBER_OF_COLUMNS + j) = 0;
    return 0;
}


int solver(int *arr, char *R) {
    counter = 0;
    first_unfixed_cell(arr);
    sit_mat = (int *) malloc(UNFIXED * 9  * sizeof(int));
    innerCounterLst = (int *) malloc(UNFIXED * sizeof(int));
    if (sit_mat == NULL || innerCounterLst == NULL){
        printMallocError();
    }
    solved = solver_rec(arr, FIRST_CELL_I, FIRST_CELL_J, R);
    free(sit_mat);
    free(innerCounterLst);
    return solved;
}
