

#ifndef STACK_H

#define STACK_H
typedef struct StackCells StackCell;

typedef struct Stacks Stack;
#endif


Stack * createNewStack();

int isEmpty(Stack * s   tack);

StackCell * pop(Stack * stack);

void DeleteStack(Stack * stack);

void push(Stack * stack, int row, int column);







