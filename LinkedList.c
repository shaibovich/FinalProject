#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"
#include "LinkedList.h"

struct Nodes {
    int value;
    int x;
    int y;
    int prevValue;
    struct Nodes *next;
    struct Nodes *prev;

};

struct Lists {
    Node *head;
    Node *current;
    List *nextLst;
    List *prevLst;
};

struct ListsofLists {
    List *currentLst;
    List *headLst;
};

int i;
Node *node, *temp;
List *newList, *tempLst;
ListofLists *newGameList;

int getNodeValue(Node *node) {
    return node->value;
}

int getNodeX(Node *node) {
    return node->x;
}

int getNodeY(Node *node) {
    return node->y;
}

int getNodePrevValue(Node *node) {
    return node->prevValue;
}

Node *createNode(int x, int y, int value, int prevValue, Node *next, Node *prev) {
    node = (Node *) malloc(sizeof(Node));
    assert(node);
    node->x = x;
    node->y = y;
    node->value = value;
    node->prevValue = prevValue;
    node->next = next;
    node->prev = prev;
    return node;
}

List *createLinkedList() {
    newList = (List *) malloc(sizeof(List));
    assert(newList);
    newList->head = NULL;
    newList->current = newList->head;
    return newList;
}

ListofLists *createNewLinkedLists() {
    newGameList = (ListofLists *) malloc(sizeof(ListofLists));
    assert(newGameList);
    newGameList->headLst = NULL;
    newGameList->currentLst = newGameList->headLst;
    return newGameList;
}

void deleteNode(Node *node) {
    free(node);
    node = NULL;
}

Node *undoMove(List *list, int isReset) {
    if (list->head == NULL || list->current == NULL || list->head->value == -1 || list->current->value == -1) {
        return NULL;
    }
    temp = list->current;
    if (list->current == list->head) {
        list->current = NULL;
    } else {
        list->current = list->current->prev;
    }
    if (!isReset){
        printUndoValue(temp->y + 1, temp->x + 1, temp->value, temp->prevValue);
    }
    return temp;
}

Node *redoMove(List *list) {
    if (list->head == NULL) {
        return NULL;
    }
    if (list->current == NULL) {
        list->current = list->head;
        printRedoValue(list->current->x + 1, list->current->y + 1, list->current->prevValue, list->current->value);
        return list->current;
    } else if (list->current->next == NULL) {
        return NULL;
    }
    temp = list->current;
    list->current = list->current->next;
    printRedoValue(temp->y + 1, temp->x + 1, temp->prevValue, temp->value);
    return temp;
}

void redoMoves(GameBoard *gameBoard, ListofLists *listArray) {
    if (listArray->headLst == NULL) {
        printNoMovesToRedo();
        return;
    }
    if (listArray->currentLst == NULL) {
        listArray->currentLst = listArray->headLst;
        do {
            temp = redoMove(listArray->headLst);
            if (temp != NULL){
                setValueToCell(gameBoard, getNodeY(temp), getNodeX(temp), getNodeValue(temp));
            }
        } while (temp != NULL);
    } else if (listArray->currentLst->nextLst == NULL){
        return;
    }
    tempLst = listArray->currentLst;
    listArray->currentLst = listArray->currentLst->nextLst;
    redoMove(tempLst);
}

int undoMoves(GameBoard *gameBoard, ListofLists *listArray, int isReset) {
    if (listArray->headLst == NULL) {
        if (!isReset) {
            printNoMovesToUndo();
        }
        return 0;
    }
    tempLst = listArray->headLst;
    if (listArray->currentLst == listArray->headLst) {
        listArray->currentLst = NULL;
        listArray->headLst = NULL;
    } else {
        listArray->currentLst = listArray->currentLst->prevLst;
    }
    do {
        temp = undoMove(tempLst,isReset);
        if (temp != NULL){
            setValueToCell(gameBoard, getNodeY(temp), getNodeX(temp), getNodePrevValue(temp));
        }



    } while (temp != NULL);
    return 1;

}

void deleteNextMoves(List *list) {
    temp = NULL;
    if (list->head == NULL) {
        return;
    } else if (list->current == NULL) {
        temp = list->head->next;
        while (temp != NULL) {
            deleteNode(temp->prev);
            temp = temp->next;
        }
        list->head = NULL;
    } else {
        if (list->current->next == NULL) {
            return;
        }
        temp = list->current->next;
        while (temp != NULL) {
            list->current->next = list->current->next->next;
            deleteNode(temp);
            temp = list->current->next;
        }
    }
}

void addMove(GameBoard *gameBoard, List *list, int row, int column, int prevValue) {
    if (list->head == NULL) {
        list->head = createNode(row, column, getCellValue(gameBoard, column, row), 0, NULL, NULL);
        list->current = list->head;
    } else {
        list->current->next = createNode(row, column, getCellValue(gameBoard, column, row), prevValue, NULL, list->current);
        list->current->next->prev = list->current;
        list->current = list->current->next;
    }
}

void addMoveByEach(GameBoard *gameBoard, List *list, int *rows, int *columns, int *values, int length) {
    for (i = 0; i < length; i++) {
        addMove(gameBoard, list, rows[i], columns[i], values[i]);
    }
}

void deleteLinkedListArray(ListofLists *listArray) {
    tempLst = NULL;
    if (listArray->headLst == NULL) {
        return;
    }
    else if (listArray->currentLst == NULL) {
        tempLst = listArray->headLst->nextLst;
        while (tempLst != NULL) {
            deleteNextMoves(tempLst->prevLst);
            tempLst = tempLst->nextLst;
        }
        listArray->headLst = NULL;
    } else {
        if (listArray->currentLst->nextLst == NULL) {
            return;
        }
        tempLst = listArray->currentLst;
        while (tempLst != NULL) {
            listArray->currentLst = listArray->currentLst->prevLst;
            deleteNextMoves(tempLst);
            tempLst = listArray->currentLst;

        }
    }
}

void addMoves(GameBoard *gameBoard, ListofLists *listArray, int *rows, int *columns, int *values, int length) {
    deleteLinkedListArray(listArray);
    if (listArray->headLst == NULL) {
        listArray->headLst = createLinkedList();
        addMoveByEach(gameBoard, listArray->headLst, rows, columns, values, length);
        listArray->currentLst = listArray->headLst;
        listArray->currentLst->nextLst = NULL;
        listArray->currentLst->prevLst = NULL;
    } else {
        listArray->currentLst->nextLst = createLinkedList();
        addMoveByEach(gameBoard, listArray->currentLst->nextLst, rows, columns, values, length);
        listArray->currentLst->nextLst->prevLst = listArray->currentLst;
        listArray->currentLst = listArray->currentLst->nextLst;
    }
}

void addMovesFromList(GameBoard * gameBoard, ListofLists * listArray, List * moveLst){
    deleteLinkedListArray(listArray);
    if (listArray->headLst == NULL){
        listArray->headLst = moveLst;
        listArray->currentLst = listArray->headLst;
        listArray->currentLst->nextLst =  NULL;
        listArray->currentLst->prevLst = NULL;
    } else {
        listArray->currentLst->nextLst = moveLst;
        listArray->currentLst->nextLst->prevLst = listArray->currentLst;
        listArray->currentLst = listArray->currentLst->nextLst;
    }
}

void deleteLinkedList(List *list) {
    deleteNextMoves(list);
    if (list->current != NULL) {
        while (list->current != list->head) {
            list->current = list->current->prev;
            deleteNode(list->current->next);
        }
        deleteNode(list->current);
    }
    free(list);
    list = NULL;
}

void deleteArray(ListofLists *listArray) {
    deleteLinkedListArray(listArray);
    if (listArray->currentLst != NULL) {
        while (listArray->currentLst != listArray->headLst) {
            listArray->currentLst = listArray->currentLst->prevLst;
            deleteLinkedList(listArray->currentLst->nextLst);
        }
        deleteLinkedList(listArray->currentLst);
    }
    free(listArray);
    listArray = NULL;
}

void emptyLst(List * lst){
    if (lst->current != NULL){
        while (lst->current != lst->head){
            lst->current = lst->current->prev;
            deleteNode(lst->current->next);
        }
        deleteNode(lst->current);
    }
    if (lst->head != NULL){
        free(lst->head);
        lst->head = NULL;
    }
}

Node * deleteCellFromList(List * lst, int column, int row){
    if (lst->current == NULL){
        return NULL;
    } else {
        temp = lst->current;
        while (temp != lst->head){
            if (temp->x == column && temp->y == row){
                temp->prev->next=temp->next;
                temp->next->prev = temp->prev;
                return temp;
            }
            temp = temp->prev;
        }
    }
    return NULL;
}



