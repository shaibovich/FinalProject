#include "GameBoardClass.h"
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
typedef struct Nodes Node;

typedef struct Lists List;

typedef struct ListsofLists ListofLists;
#endif


Node *createNode(int X, int Y, int value, int prevValue, Node *next, Node *prev);

ListofLists *createNewLinkedLists();

void redoMoves(GameBoard *gameBoard, ListofLists *listArray);

int undoMoves(GameBoard *gameBoard, ListofLists *listArray, int isReset);

void deleteArray(ListofLists *listArray);

void addMoves(GameBoard *gameBoard, ListofLists *listArray, int *rows, int *columns, int *values, int length);

void deleteNextMoves(List *list);

int getNodeValue(Node *node);

int getNodeX(Node *node);

int getNodeY(Node *node);

int getNodePrevValue(Node *node);
