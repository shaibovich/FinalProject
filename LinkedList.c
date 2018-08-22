#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "Gameboard.h"

#define under "_";

typedef struct Nodes {
	int value;
	int X;
	int Y;
	int prevValue;
	struct Nodes* next;
	struct Nodes* prev;

}Node ;

typedef struct Lists{
	Node * head;
	Node* current;//current is a pointer to current location on the list
} List;

Node *createNode(int X, int Y,int value, int prevValue, Node *next, Node *prev) {
    Node *node = (Node*) malloc(sizeof(Node));
    assert(node);
    node->X=X;
    node->Y=Y;
    node->value = value;
    node->prevValue= prevValue;
    node->next = next;
    node->prev = prev;
    assert(node->next);
    assert(node->prev);
    return node;
}

List *createLinkedList(){
	List *list = (Node*) malloc(sizeof(List));
	assert(list);
	list->head = NULL;
	list->current=list->head;
	return list;
}


Node * getNext(List * list){
	return list->current->next;
}

//if current move is the first move - returns NULL, else returns the previous Node. note: need to take the value from node
Node * getPrev(List * list){
	if (list->current == list->head){
		return NULL;
	}
	else{
		return list-> current->prev;
	}
}

 //changes the value and prevValue of current and THEN changes current into previous.
Node * undo(List * list){
	if (list->current->prev == NULL){ //is head
		printf("Error: no moves to undo\n");
		exit();
	}
	Node * temp = list-> current; //copy of current
	list->current->value = temp->prevValue;
	list->current->prevValue =temp->value;
	list-> current = getPrev(list);
	//need to use print the board function
	if (temp->X==0){
		temp->X=under;
	}
	if (temp->Y==0){
		temp->Y=under;
	}

	printf("Undo %d,%d: from %d to %d\n", temp->X,temp->Y,temp->value,temp->prevValue);
	return list->current;
}

Node * redo(List * list){
	//last move (no redo)
	if (list->current->next==NULL){
		printf("Error: no moves to redo\n");
		exit();
		}
	list->current = getNext(list);
	Node * temp = list->current; //copy of current
	list->current->value = temp->prevValue;
	list->current->prevValue =temp->value;
	//need to use print the board function
	if (temp->X==0){
		temp->X=under;
	}
	if (temp->Y==0){
		temp->Y=under;
	}

	printf("Redo %d,%d: from %d to %d\n", temp->X,temp->Y,temp->value,temp->prevValue);
	return list->current;
}

void addMove(GameBoard * gameboard , List * list, int row, int column, int value){
	deleteNextMoves(list);
	list->current->next = createNode(row, column,value, getCellValue(gameboard, row, column), NULL, list->current);
	list->current->next->prev = list->current;
}

void deleteNode(Node * node){
	free(node);
}

void deleteLinkedList(List * list){
	free(list);
}

//when undo is done and then no redo
void deleteNextMoves(List * list){
	Node * temp = list->current->next;
	while (temp!=NULL){
		deleteNode(list->current->next);
		list->current->next = list->current->next->next;
		list->current->next->prev = list->current;
		temp = list->current->next;
	}
}



