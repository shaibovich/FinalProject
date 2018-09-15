
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
typedef struct Nodes Node;

typedef struct Lists List;

typedef struct ListsofLists ListofLists;
#include "GameBoardClass.h"
#endif


Node *createNode(int X, int Y, int value, int prevValue, Node *next, Node *prev);

ListofLists *createNewLinkedLists();

void deleteLinkedList(List *list);

void redoMoves(GameBoard *gameBoard, ListofLists *listArray);

int undoMoves(GameBoard *gameBoard, ListofLists *listArray, int isReset);

void deleteArray(ListofLists *listArray);

void addMoves(GameBoard *gameBoard, ListofLists *listArray, int *rows, int *columns, int *values, int length);

void deleteNextMoves(List *list);

int getNodeValue(Node *node);

int getNodeX(Node *node);

int getNodeY(Node *node);

int getNodePrevValue(Node *node);

List *createLinkedList();

void addMove(GameBoard *gameBoard, List *list, int row, int column, int prevValue);

void emptyLst(List * lst);

Node * deleteCellFromList(List * lst, int column, int row);

void addMovesFromList(GameBoard * gameBoard, ListofLists * listArray, List * moveLst);
