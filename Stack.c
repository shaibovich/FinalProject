

#ifndef STACK_C
#define STACK_C

#include <stdlib.h>
#include <assert.h>
#include "Stack.h"


struct StackCells {
    int row;
    int column;
    struct StackCells *prev;
    struct StackCells *next;
};

struct Stacks {
    int StackSize;
    int isEmpty;
    struct StackCells *StackHead;
};

#endif

Stack *newStack;

StackCell *newCell;

Stack *createNewStack() {
    newStack = (Stack *) malloc(sizeof(Stack));
    assert(newStack);
    newStack->isEmpty = 1;
    newStack->StackHead = NULL;
    newStack->StackSize = 0;
    return newStack;
}

StackCell *createNewCell(int row, int column, StackCell *prev) {
    newCell = (StackCell *) malloc(sizeof(StackCell));
    newCell->row = row;
    newCell->column = column;
    newCell->prev = prev;

    return newCell;
}

int isEmpty(Stack *stack) {
    return stack->isEmpty;
}

StackCell *pop(Stack *stack) {
    if (isEmpty(stack) || stack->StackSize == 1) {
        stack->isEmpty = 1;
        return NULL;
    } else {
        stack->StackSize -= 1;
        stack->StackHead = stack->StackHead->prev;
        stack->isEmpty = 0;
        return stack->StackHead;
    }
}

void push(Stack *stack, int row, int column) {
    StackCell *newCell = createNewCell(row, column, stack->StackHead);
    stack->StackHead->next = newCell;
    stack->StackHead = newCell;
    stack->isEmpty = 0;
    stack->StackSize += 1;
}

void DeleteStack(Stack *stack) {
    while (stack->isEmpty == 0) {
        stack->StackHead = stack->StackHead->prev;
        free(stack->StackHead->next);
    }
    free(stack);

}

int getColumn(StackCell *cell) {
    return cell->column;
}

int getRow(StackCell *cell) {
    return cell->row;
}


