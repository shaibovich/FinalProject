/*
 * fina.h
 *
 *  Created on: 14 баев 2018
 *      Author: noabe
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct Nodes Node;
typedef struct Lists List;
Node *createNode(int X, int Y,int value, int prevValue, Node *next, Node *prev) ;
List *createLinkedList();
Node * getNext(List * list);
Node * getPrev(List * list);
Node * undo(List * list);
Node * redo(List * list);
void addMove(GameBoard * gameboard , List * list, int row, int column, int value);
void deleteNextMoves(List * list);
#endif /* LINKEDLIST_H_ */
