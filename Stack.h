

#ifndef STACK_H

#define STACK_H
typedef struct StackCells StackCell;

typedef struct Stacks Stack;
#endif


Stack * createEmptyStack();

int isEmpty(Stack * stack);

int getPreviuseValue(StackCell * stackCell);

int getValue(StackCell * stackCell);

int push(Stack * stack, int row, int column, int value);

int getRow(StackCell * stackCell);

int getColumn(StackCell * stackCell);




