#include "GameBoardClass.h"
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
typedef struct Nodes Node;

typedef struct Lists List;
#endif


Node *createNode(int X, int Y, int value, int prevValue, Node *next, Node *prev);

List *createLinkedList();

void deleteLinkedList(List *list);

Node *getNext(List *list);

Node *getPrev(List *list);

Node *undoMove(List *list, int isReset);

Node *redoMove(List *list);

void addMove(GameBoard *gameboard, List *list, int row, int column, int value);

void deleteNextMoves(List *list);

int getNodeValue(Node *node);

int getNodeX(Node *node);

int getNodeY(Node *node);

int getNodePrevValue(Node *node);
