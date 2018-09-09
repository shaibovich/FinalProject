CC = gcc
OBJS = utils.o GameBoardClass.o InputController.o sudokuSolver.o LinkedList.o Stack.o FileController.o GameManager.o main.o
EXEC = sudoku


GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

COMP_FLAG1 =
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
utils.o: utils.c utils.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
GameManager.o: GameManager.c GameManager.h LinkedList.h InputController.h FileController.h sudokuSolver.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
main.o: main.c GameManager.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
FileController.o: FileController.c FileController.h utils.h GameBoardClass.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
GameBoardClass.o: GameBoardClass.c GameBoardClass.h utils.h GameManager.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
LinkedList.o: LinkedList.c LinkedList.h utils.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
InputController.o: InputController.c InputController.h utils.h GameManager.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
sudokuSolver.o: sudokuSolver.c sudokuSolver.h GameBoardClass.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
clean:
	rm -f *.o $(EXEC)
