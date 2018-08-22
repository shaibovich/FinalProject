////
//// Created by Shai Leibovich on 19/08/2018.
////
//
///* Copyright 2013, Gurobi Optimization, Inc. */
//
///* This example formulates and solves the following simple MIP model:
//
//     maximize    x +   y + 2 z
//     subject to  x + 2 y + 3 z <= 4
//                 x +   y       >= 1
//     x, y, z binary
//*/
//
//#include <stdlib.h>
//#include <stdio.h>
//#include "gurobi_c.h"
//
//int main(void)
//{
//    GRBenv   *env   = NULL;
//    GRBmodel *model = NULL;
//    int       error = 0;
//    double    sol[3];
//    int       ind[3];
//    double    val[3];
//    double    obj[3];
//    char      vtype[3];
//    int       optimstatus;
//    double    objval;
//
//    /* Create environment - log file is mip1.log */
//    error = GRBloadenv(&env, "mip1.log");
//    if (error) {
//        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Create an empty model named "mip1" */
//    error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
//    if (error) {
//        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//
//    /* Add variables */
//
//    /* coefficients - for x,y,z (cells 0,1,2 in "obj") */
//    obj[0] = 1; obj[1] = 1; obj[2] = 2;
//
//    /* variable types - for x,y,z (cells 0,1,2 in "vtype") */
//    vtype[0] = GRB_BINARY; vtype[1] = GRB_BINARY; vtype[2] = GRB_BINARY;
//
//    /* add variables to model */
//    error = GRBaddvars(model, 3, 0, NULL, NULL, NULL, obj, NULL, NULL, vtype, NULL);
//    if (error) {
//        printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Change objective sense to maximization */
//    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
//    if (error) {
//        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* update the model - to integrate new variables */
//
//    error = GRBupdatemodel(model);
//    if (error) {
//        printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//
//    /* First constraint: x + 2 y + 3 z <= 4 */
//
//    /* variables x,y,z (0,1,2) */
//    ind[0] = 0; ind[1] = 1; ind[2] = 2;
//    /* coefficients (according to variables in "ind") */
//    val[0] = 1; val[1] = 2; val[2] = 3;
//
//    /* add constraint to model - note size 3 + operator GRB_LESS_EQUAL */
//    /* -- equation value (4.0) + unique constraint name */
//    error = GRBaddconstr(model, 3, ind, val, GRB_LESS_EQUAL, 4.0, "c0");
//    if (error) {
//        printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Second constraint: x + y >= 1 */
//    ind[0] = 0; ind[1] = 1;
//    val[0] = 1; val[1] = 1;
//
//    /* add constraint to model - note size 2 + operator GRB_GREATER_EQUAL */
//    /* -- equation value (1.0) + unique constraint name */
//    error = GRBaddconstr(model, 2, ind, val, GRB_GREATER_EQUAL, 1.0, "c1");
//    if (error) {
//        printf("ERROR %d 2nd GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Optimize model - need to call this before calculation */
//    error = GRBoptimize(model);
//    if (error) {
//        printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Write model to 'mip1.lp' - this is not necessary but very helpful */
//    error = GRBwrite(model, "mip1.lp");
//    if (error) {
//        printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Get solution information */
//
//    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
//    if (error) {
//        printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* get the objective -- the optimal result of the function */
//    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
//    if (error) {
//        printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* get the solution - the assignment to each variable */
//    /* 3-- number of variables, the size of "sol" should match */
//    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, 3, sol);
//    if (error) {
//        printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* print results */
//    printf("\nOptimization complete\n");
//
//    /* solution found */
//    if (optimstatus == GRB_OPTIMAL) {
//        printf("Optimal objective: %.4e\n", objval);
//        printf("  x=%.0f, y=%.0f, z=%.0f\n", sol[0], sol[1], sol[2]);
//    }
//        /* no solution found */
//    else if (optimstatus == GRB_INF_OR_UNBD) {
//        printf("Model is infeasible or unbounded\n");
//    }
//        /* error or calculation stopped */
//    else {
//        printf("Optimization was stopped early\n");
//    }
//
//    /* IMPORTANT !!! - Free model and environment */
//    GRBfreemodel(model);
//    GRBfreeenv(env);
//
//    return 0;
//}



#include <printf.h>

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

void printValueOutOfRange() {
    printf("Error: value not in range 0-N\n");
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
    printf("Error: board is not empty \n");
}

void printGeneratorFailed() {
    printf("Error: puzzle generator failed\n");
}

void printNoMovesToUndo() {
    printf("Error: no moves to undo\n");
}

void printUndoValue(int x, int y, int oldValue, int newValue) {
    printf("Undo %d,%d: from %d to %d\n", x, y, oldValue, newValue);
}

void printNoMovesToRedo() {
    printf("Error: no moves to redo\n");
}

void printredoValue(int x, int y, int oldValue, int newValue) {
    printf("Redo %d,%d: from %d to %d\n", x, y, oldValue, newValue);
}

void printFileCannotBeCreated() {
    printf("Error: File cannot be created or modified\n");
}

void printSaveTo(int x){
    printf("Saved to: %d\n", x);
}

void printCellAlreadyContains(){
    printf("Error: cell already contains a value\n");
}

void hintCell(int value){
    printf("Hint: set cell to %d\n", value);
}

void printNumberOfsolutions(int num){
    printf("Number of solutions: %d\n", num);
}

void printGoodBoard(){
    printf("This is a good board!\n");
}

void printBadPuzzle(){
    printf("The puzzle has more than 1 solution, try to edit it further\n");
}

void printSetCell(int x, int y, int value){
    printf("Cell <%d,%d> set to %d\n", x, y, value);
}

void printBoardReset(){
    printf("Board reset\n".);
}

void printExit(){
    printf("Exiting...\n");
}





