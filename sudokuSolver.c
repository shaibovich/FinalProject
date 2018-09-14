


#include "sudokuSolver.h"
#include "gurobi1_c.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int *ind, error, optimstatus, DIM, rowIndex, columnIndex, value, ig, jg, count, gameColumnBlock, gameRowsBlock;
char *vtype;
double *val, *lb, *sol, objval;
GRBmodel *model;

GRBenv *env;

void init() {
    ind = (int *) malloc(sizeof(int) * DIM);
    assert(ind);
    val = (double *) malloc(sizeof(double) * DIM);
    assert(val);
    lb = (double *) malloc(sizeof(double) * DIM * DIM * DIM);
    assert(lb);
    vtype = (char *) malloc(sizeof(char) * DIM * DIM * DIM);
    assert(vtype);
    sol = (double *) malloc(DIM * DIM * DIM * sizeof(double));
    assert(sol);
    for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (value = 0; value < DIM; value++) {
                lb[DIM * DIM * rowIndex + DIM * columnIndex + value] = 0.0;
                sol[DIM * DIM * rowIndex + DIM * columnIndex + value] = 0.0;
            }
        }
        val[rowIndex] = 0.0;
        ind[rowIndex] = 0;
    }
}

void finish() {
    GRBfreemodel(model);
    GRBfreeenv(env);
    free(ind);
    free(val);
    free(lb);
    free(vtype);
    free(sol);
    ind = NULL, val = NULL, lb = NULL, vtype = NULL, sol = NULL;
}

void copySolToGameBoard(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (value = 0; value < DIM; value++) {
                if (sol[DIM * DIM * rowIndex + DIM * columnIndex + value] == 1) {
                    setCellValue(gameBoard, columnIndex, rowIndex, value + 1);
                }
            }
        }
    }
}

void createEmptyModel(GameBoard *gameBoard) {
    for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (value = 0; value < DIM; value++) {
                if (getCellValue(gameBoard, columnIndex, rowIndex) == value + 1)
                    *(lb + rowIndex * DIM * DIM + columnIndex * DIM + value) = 1;
                else
                    *(lb + rowIndex * DIM * DIM + columnIndex * DIM + value) = 0;
                *(vtype + rowIndex * DIM * DIM + columnIndex * DIM + value) = GRB_BINARY;
            }
        }
    }
}

int eachCellGetsValue() {
    for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (value = 0; value < DIM; value++) {
                ind[value] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                val[value] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) return 0;
        }
    }
    return 1;
}


int oneEachRow() {
    for (value = 0; value < DIM; value++) {
        for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
            for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
                ind[rowIndex] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                val[rowIndex] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) return 0;
        }
    }
    return 1;
}

int oneEachColumn() {
    for (value = 0; value < DIM; value++) {
        for (rowIndex = 0; rowIndex < DIM; rowIndex++) {
            for (columnIndex = 0; columnIndex < DIM; columnIndex++) {
                ind[columnIndex] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                val[columnIndex] = 1.0;
            }
            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) return 0;
        }
    }
    return 1;
}

int oneEachGrind() {
    for (value = 0; value < DIM; value++) {
        for (ig = 0; ig < gameRowsBlock; ig++) {
            for (jg = 0; jg < gameColumnBlock; jg++) {
                count = 0;
                for (rowIndex = ig * gameRowsBlock; rowIndex < (ig + 1) * gameRowsBlock; rowIndex++) {
                    for (columnIndex = jg * gameColumnBlock; columnIndex < (jg + 1) * gameColumnBlock; columnIndex++) {
                        ind[count] = rowIndex * DIM * DIM + columnIndex * DIM + value;
                        val[count] = 1.0;
                        count++;
                    }
                }
                error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
                if (error) return 0;
            }
        }
    }
    return 1;
}


int solveSudoko(GameBoard *gameBoard, GameBoard *solBoard) {
    env = NULL;
    model = NULL;
    DIM = getNumberOfRows(gameBoard);
    gameColumnBlock = getNumberOfBlockColumn(gameBoard);
    gameRowsBlock = getNumberOfRowsBlock(gameBoard);
    init();
    error = 0;

    /* Create an empty model */
    createEmptyModel(gameBoard);

    /* Create environment */
    error = GRBloadenv(&env, "sudoku.log");
    if (error) goto QUIT;
    /* Create new model */
    error = GRBnewmodel(env, &model, "sudoku", DIM * DIM * DIM, NULL, lb, NULL, vtype, NULL);

    if (error) goto QUIT;

    if (!eachCellGetsValue()) goto QUIT;

    if (!oneEachRow()) goto QUIT;

    if (!oneEachColumn()) goto QUIT;

    if (!oneEachGrind()) goto QUIT;

    /* Optimize model */
    error = GRBoptimize(model);
    if (error) goto QUIT;
    /* Write model to ’sudoku.lp ’ */
    error = GRBwrite(model, "sudoku.lp");
    if (error) goto QUIT;
    /* Capture solution information */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) goto QUIT;

    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) goto QUIT;

    if (optimstatus == GRB_OPTIMAL) {
        error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, DIM * DIM * DIM, sol);
        if (error) goto QUIT;
        copySolToGameBoard(solBoard);
        printGameBoard(gameBoard, 1);
        error = 0;
    } else {
        error = 1;
    }
    QUIT :
    if (error) {
        finish();
        return 0;

    }
    finish();
    return 1;
}
