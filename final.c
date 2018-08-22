#include <stdio.h>
#include <stdlib.h>

#define under "_";

typedef struct Node {
	int value;
	int X;
	int Y;
	int prevVAlue;
	struct node* next;
	struct node* prev;

}Node ;

Node temp;
Node head;
Node* current= &head; //current is a pointer to current location on the list

Node * getNext(){
	return *current->next;
}
//if current move is the first move - returns NULL, else returns the previous Node. note: need to take the value from node
Node * getPrev(){
	if (*current == &head){
		return NULL;
	}
	else{
		return current->prev;
	}
}
 //changes the value and prevValue of current and THEN changes current into previous.
void undo(){
	if (*current->prev == NULL){ //is head
		printf("Error: no moves to undo\n");
		exit();
	}
	Node * temp = current; //copy of current
	*current->value = temp->prevVAlue;
	*current->prevVAlue =temp->value;
	current = getPrev();
	//need to use print the board function
	if (temp->X==0){
		temp->X=under;
	}
	if (temp->Y==0){
		temp->Y=under;
	}

	printf("Undo %d,%d: from %d to %d\n", temp->X,temp->Y,temp->value,temp->prevVAlue);

}

void redo(){
	if (current->next==NULL){
		printf("Error: no moves to redo\n");
		exit();
		}
	current = getNext();
	Node * temp = current; //copy of current
	*current->value = temp->prevVAlue;
	*current->prevVAlue =temp->value;
	//need to use print the board function
	if (temp->X==0){
		temp->X=under;
	}
	if (temp->Y==0){
		temp->Y=under;
	}

	printf("Redo %d,%d: from %d to %d\n", temp->X,temp->Y,temp->value,temp->prevVAlue);

}





