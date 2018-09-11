

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
<<<<<<< HEAD
    struct StackCells *StackHead;
};

#endif

Stack *newStack;

StackCell *newCell;

=======
    StackCell *StackHead;
};
Stack *newStack;

>>>>>>> 31ae159e868cb05b9ad4d031349cc993742c667c
Stack *createNewStack() {
    newStack = (Stack *) malloc(sizeof(Stack));
    assert(newStack);
    newStack->isEmpty = 1;
    newStack->StackHead = NULL;
    newStack->StackSize = 0;
<<<<<<< HEAD
    return newStack;
}

=======
}

StackCell *newCell;

>>>>>>> 31ae159e868cb05b9ad4d031349cc993742c667c
StackCell *createNewCell(int row, int column, StackCell *prev) {
    newCell = (StackCell *) malloc(sizeof(StackCell));
    newCell->row = row;
    newCell->column = column;
    newCell->prev = prev;

    return newCell;
}

<<<<<<< HEAD
=======
//1 if empty 0 else
>>>>>>> 31ae159e868cb05b9ad4d031349cc993742c667c
int isEmpty(Stack *stack) {
    return stack->isEmpty;
}

StackCell *pop(Stack *stack) {
<<<<<<< HEAD
=======
    // if stack has 1 or less objects - ret null
>>>>>>> 31ae159e868cb05b9ad4d031349cc993742c667c
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
<<<<<<< HEAD
    stack->StackHead->next = newCell;
    stack->StackHead = newCell;
    stack->isEmpty = 0;
    stack->StackSize += 1;
}
=======
    if(stack->StackHead!=NULL){
        stack->StackHead->next = newCell;
        stack->StackHead = newCell;
        stack->isEmpty = 0;
        stack->StackSize += 1;
    }
    else{
        stack->StackHead=newCell;
        stack->StackSize=1;
        stack->isEmpty=0;
    }

};
>>>>>>> 31ae159e868cb05b9ad4d031349cc993742c667c

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


