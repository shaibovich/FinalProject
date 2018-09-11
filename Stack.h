#ifndef STACK_H
#define STACK_H
typedef struct StackCells StackCell;

typedef struct Stacks Stack;


Stack *createNewStack();

int isEmpty(Stack *stack);

StackCell *pop(Stack *stack);

void DeleteStack(Stack *stack);

void push(Stack *stack, int row, int column);

int getColumn(StackCell *cell);

int getRow(StackCell *cell);
#endif