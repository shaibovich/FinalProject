/**
 * SudokuSolver source file
 * This file will solve a sudoku game according to ILP soultions.
 * Main function solveSudoko will use Gruobi framework for ILP soultions
 */


#include "sudokuSolver.h"
#include "gurobi1_c.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int *ind, *ind2, error, optimstatus, DIM, rowIndex, columnIndex, value, ig, jg, count, gameColumnBlock, gameRowsBlock;
int rowSolver, columnSolver, valueSolver;
char *vtype;
double *val, *lb, *sol, objval,  *val2;
GRBmodel *model;

GRBenv *env;

void init() {
    ind = (int *) malloc(sizeof(int) * DIM);
    assert(ind);
    ind2 = (int*) malloc(sizeof(int) * DIM);
    assert(ind2);
    val2 = (double *) malloc (sizeof(double) * DIM);
    assert(val2);
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
    free(ind2);
    free(val2);
    ind = NULL, val = NULL, lb = NULL, vtype = NULL, sol = NULL, ind2 = NULL, val2 = NULL;
}

void copySolToGameBoard(GameBoard *gameBoard) {
    for (rowSolver = 0; rowSolver< DIM; rowSolver++) {
        for (columnSolver = 0; columnSolver< DIM; columnSolver++) {
            for (valueSolver = 0; valueSolver< DIM; valueSolver++) {
                if (sol[DIM * DIM * rowSolver + DIM * columnSolver + valueSolver] == 1) {
                    setCellValue(gameBoard, columnSolver, rowSolver, valueSolver + 1);
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


int setCurrentlyValue(GameBoard * gameBoard){
    for (rowIndex =0; rowIndex < DIM; rowIndex ++){
        for (columnIndex = 0; columnIndex <DIM; columnIndex++){
            if (getCellValue(gameBoard,columnIndex, rowIndex) != 0){
                ind2[0] = DIM * DIM * rowIndex + DIM* columnIndex + (getCellValue(gameBoard,columnIndex, rowIndex)-1);
                val2[0] = 1;
                error = GRBaddconstr(model, 1, ind2, val2, GRB_EQUAL, 1.0, NULL);
                if (error) return 0;
            }

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
                for (rowIndex = ig * gameColumnBlock; rowIndex < (ig + 1) * gameColumnBlock; rowIndex++) {
                    for (columnIndex= jg * gameRowsBlock; columnIndex < (jg + 1) * gameRowsBlock; columnIndex++) {
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


    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error) goto QUIT;

    /* Create new model */
    error = GRBnewmodel(env, &model, "sudoku", DIM * DIM * DIM, NULL, lb, NULL, vtype, NULL);
    if (error) goto QUIT;


    /* Each cell in the sudoku gets value */
    if (!eachCellGetsValue()) goto QUIT;

    /* Each cell of the gameBoard that have value will remain in the same value */
    if (!setCurrentlyValue(gameBoard)) goto QUIT;

    /* Each cell in each row will get unique value */
    if (!oneEachRow()) goto QUIT;

    /* Each cell in each column will get unique value */
    if (!oneEachColumn()) goto QUIT;

    /* Each cell in each subgrind will get unique value */
    if (!oneEachGrind()) goto QUIT;

    /* Optimize the ILP */
    error = GRBoptimize(model);
    if (error) goto QUIT;

    /* Write date into model */
    error = GRBwrite(model, "sudoku.lp");
    if (error) goto QUIT;

    /* Capture solution information */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) goto QUIT;

    /* Capture the objval */
    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) goto QUIT;


    error = GRBgetdblattrarray (model, GRB_DBL_ATTR_X, 0, DIM * DIM * DIM, sol);
    if(error) goto QUIT;

    if (optimstatus != 2) {
        error = 1;
    } else {
        copySolToGameBoard(solBoard);
        error = 0;
    }

    QUIT :
    if (error) {
        finish();
        return 0;

    }
    finish();
    return 1;
}
