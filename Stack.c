
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"

struct StackCells {
    int row;
    int column;
    StackCell *prev;
    StackCell *next;
};

struct Stacks{
    int StackSize;
    int isEmpty;
    StackCell * StackHead;
};
Stack*  newStack;
Stack * createNewStack(){
    newStack = (Stack *) malloc(sizeof(Stack));
    assert(newStack);
    newStack -> isEmpty=1;
    newStack -> StackHead=NULL;
    newStack -> StackSize=0;
}

StackCell * newCell;

StackCell * createNewCell(int row, int column, StackCell * prev){
    newCell = (StackCell *) malloc(sizeof(StackCell));
    newCell->row=row;
    newCell->column=column;
    newCell-> prev = prev;

    return newCell;
}

//1 if empty 0 else
int isEmpty(Stack * stack){
    return stack->isEmpty;
}

StackCell * pop(Stack * stack){
    // if stack has 1 or less objects - ret null
    if (isEmpty(stack)||stack->StackSize==1){
        stack->isEmpty=1;
        return NULL;
    }
    else{
        stack->StackSize-=1;
        stack->StackHead=stack->StackHead->prev;
        stack->isEmpty= 0;
        return stack->StackHead;
    }
};

void push(Stack * stack, int row, int column){
    StackCell * newCell = createNewCell(row,column,stack->StackHead);
    stack->StackHead->next=newCell;
    stack->StackHead=newCell;
    stack->isEmpty=0;
    stack->StackSize+=1;
};

void DeleteStack(Stack * stack){
    while (stack->isEmpty==0){
        stack->StackHead=stack->StackHead->prev;
        free(stack->StackHead->next);
    }
    free(stack);

};








