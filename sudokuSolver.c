


#include "sudokuSolver.h"
#include "gurobi1_c.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int zero, error, optimstatus, DIM, SUBDIM, rowIndex, columnIndex, value, ig, jg, count, gameColumnBlock , gameRowsBlock;
int *ind;
char *cursor, *namestorage, *names, *vtype;
double *val, *lb, objval;
GRBmodel *model;
GRBenv *env;

void init() {
    printf("Starting Init");
    ind = (int *) malloc(sizeof(int) * DIM);
    assert(ind);
    val = (double *) malloc(sizeof(double) * DIM);
    assert(val);
    lb = (double *) malloc(sizeof(double) * DIM * DIM * DIM);
    assert(lb);
    vtype = (char *) malloc(sizeof(char) * DIM * DIM * DIM);
    assert(vtype);
    names = (char *) malloc(sizeof(char) * DIM * DIM * DIM);
    assert(names);
    namestorage = (char *) malloc(sizeof(char) * DIM * DIM * DIM * 10);
    assert(namestorage);
    printf("Finished Init");
}

void finish(){
    free(ind);
    free(val);
    free(lb);
    free(vtype);
    free(names);
    free(namestorage);
}

int solveSudoko(GameBoard *gameBoard) {
    SUBDIM = 3;
    env = NULL;
    model = NULL;
    DIM = getNumberOfRows(gameBoard);
    gameColumnBlock = getNumberOfBlockColumn(gameBoard);
    gameRowsBlock = getNumberOfRowsBlock(gameBoard);
    init();

    zero = 0;
    error = 0;

    /* Create an empty model */
    printf("created empty board");
    cursor = namestorage;
    for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (value = 0; value < DIM; value++) {
                if (getCellValue(gameBoard, columnIndex, rowIndex) == value)
                    *(lb + rowIndex * DIM * DIM + columnIndex *DIM +value ) = 1;
                else
                    *(lb + rowIndex * DIM * DIM + columnIndex *DIM +value ) = 0;
                *(vtype + rowIndex * DIM * DIM + columnIndex * DIM + value) = GRB_BINARY;
                *(names + rowIndex * DIM * DIM + columnIndex * DIM + value) = *cursor;

                sprintf(names + rowIndex * DIM * DIM + columnIndex * DIM + value, "x[%d ,%d ,%d]", rowIndex, columnIndex, value + 1);
                cursor += strlen(names + rowIndex * DIM * DIM + columnIndex * DIM + value) + 1;
            }
        }
    }
    printf("Finished empty board, create environment");
    /* Create environment */
    error = GRBloadenv(&env, " sudoku.log");
    if (error) goto QUIT;
    /* Create new model */
    error = GRBnewmodel(env, &model, " sudoku ", DIM * DIM * DIM, NULL, lb, NULL,
                        vtype, &names);
    if (error) goto QUIT;
    /* Each cell gets a value */
    for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (value = 0; value < DIM; value++) {
                ind[value] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                val[value] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) goto QUIT;
        }
    }
    /* Each value must appear once in each row */
    for (value = 0; value < DIM; value++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
                ind[rowIndex] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                val[rowIndex] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) goto QUIT;
        }
    }
    /* Each value must appear once in each column */
    for (value = 0; value < DIM; value++) {
        for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
            for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
                ind[columnIndex] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                val[columnIndex] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) goto QUIT;
        }
    }
    /* Each value must appear once in each subgrid */
    for (value = 0; value < DIM; value++) {
        for (ig = 0; ig < SUBDIM; ig++) {
            for (jg = 0; jg < SUBDIM; jg++) {
                count = 0;
                for (rowIndex = ig * SUBDIM; rowIndex < (ig + 1) * SUBDIM; rowIndex++) {
                    for (columnIndex = jg * SUBDIM; columnIndex < (jg + 1) * SUBDIM; columnIndex++) {
                        ind[count] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                        val[count] = 1.0;
                        count++;
                    }
                }
                error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
                if (error) goto QUIT;
            }
        }
    }
    /* Optimize model */
    error = GRBoptimize(model);
    if (error) goto QUIT;
    /* Write model to ’sudoku .lp ’ */
    error = GRBwrite(model, " sudoku.lp");
    if (error) goto QUIT;
    /* Capture solution information */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) goto QUIT;
    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) goto QUIT;
    printf("\nOptimization complete \n");
    if (optimstatus == GRB_OPTIMAL)
        printf(" Optimal objective : %.4e\n", objval);
    else if (optimstatus == GRB_INF_OR_UNBD)
        printf(" Model is infeasible or unbounded \n");
    else
        printf(" Optimization was stopped early \n");
    printf("\n");
    QUIT :
    /* Error reporting */
    if (error) {
        printf(" ERROR : %s\n", GRBgeterrormsg(env));
        exit(1);
    }
    /* Free model */
    /* Free model */
    GRBfreemodel(model);
    /* Free environment */
    GRBfreeenv(env);
    finish();
    return 0;
}

