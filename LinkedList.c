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
    int isFirst;
    int isLast;
};

struct ListsofLists {
    List *currentLst;
    List *headLst;
    int isFirst;
    int isLast;
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
    newList->prevLst = NULL;
    newList->nextLst = NULL;
    newList->isLast = 1;
    newList->isFirst = 1;
    return newList;
}

ListofLists *createNewLinkedLists() {
    newGameList = (ListofLists *) malloc(sizeof(ListofLists));
    assert(newGameList);
    newGameList->headLst = NULL;
    newGameList->currentLst = newGameList->headLst;
    newGameList->isFirst = 1;
    newGameList->isLast = 1;
    return newGameList;
}

void deleteNode(Node *node) {
    free(node);
    node = NULL;
}

Node *undoMove(List *list, int isReset) {
    if (list->head == NULL || list->isFirst == 1) {
        /* list only init */
        return NULL;
    } else if (list->current->prev == NULL) {
        /* use the first node */
        temp = list->current;
        list->isFirst = 1;
    } else {
        /* have move to undo*/
        temp = list->current;
        list->current = temp->prev;
    }
    list->isLast = 0;
    if (!isReset) {
        printUndoValue(temp->y + 1, temp->x + 1, temp->value, temp->prevValue);
    }
    return temp;
}

Node *redoMove(List *list) {
    if (list->head == NULL || list->isLast == 1) {
        /* list is empty */
        return NULL;
    }

    if (list->current->next == NULL) {
        list->isLast = 1;
        temp = list->current;
        printRedoValue(temp->y + 1, temp->x + 1, temp->prevValue, temp->value);
        list->isFirst = 0;
        return temp;
    } else {
        /* list have next  */
        if (list->isFirst == 1){
            temp = list->current;
        } else {
            temp = list->current->next;
        }
        printRedoValue(temp->y + 1, temp->x + 1, temp->prevValue, temp->value);
        list->current = list->current->next;
        list->isFirst = 0;
        return temp;
    }
}

void redoMoves(GameBoard *gameBoard, ListofLists *listArray, int withStar) {
    if (listArray->headLst == NULL || listArray->isLast == 1) {
        /* list is empty */
        printNoMovesToRedo();
        return;
    }
    if (listArray->currentLst->nextLst == NULL) {
        listArray->isLast = 1;
        tempLst = listArray->currentLst;
        temp = redoMove(tempLst);
    } else {
        /* there is next, redo to currentLst->nextLst */
        if (listArray->isFirst == 1){
            tempLst = listArray->currentLst;
        } else {
            tempLst = listArray->currentLst->nextLst;
        }
        listArray->currentLst = listArray->currentLst->nextLst;
        temp = redoMove(tempLst);
    }
    listArray->isFirst = 0;
    do {
        if (temp != NULL) {
            setValueToCell(gameBoard, getNodeY(temp), getNodeX(temp), getNodeValue(temp));
        }
        temp = redoMove(tempLst);
    } while (temp != NULL);
    printGameBoard(gameBoard, withStar);

}

int undoMoves(GameBoard *gameBoard, ListofLists *listArray, int isReset, int withStars) {
    if (listArray->headLst == NULL || listArray->isFirst == 1) {
        /* list only init || list point to first */
        if (!isReset) {
            printNoMovesToUndo();
        }
        return 0;
    }
    if (listArray->currentLst->prevLst == NULL) {
        /* if list point to first lst */
        tempLst = listArray->currentLst;
        listArray->isFirst = 1;
    } else {
        /* list have prev */
        tempLst = listArray->currentLst;
        listArray->currentLst = listArray->currentLst->prevLst;
    }
    listArray->isLast = 0;
    do {
        temp = undoMove(tempLst, isReset);
        if (temp != NULL) {
            setValueToCell(gameBoard, getNodeY(temp), getNodeX(temp), getNodePrevValue(temp));
        }
    } while (temp != NULL);
    printGameBoard(gameBoard, withStars);
    return 1;

}

void deleteNextMoves(List *list) {
    if (list->head == NULL || list->isLast == 1) {
        return;
    } else {
        if (list->isLast == 0 && list->isFirst == 1){
            deleteNode(list->head);
            list->head = NULL;
        } else {
            temp = list->current->next;
            do {
                list->current->next = list->current->next->next;
                deleteNode(temp);
                temp = list->current->next;
            } while (temp != NULL);
        }

    }
    list->isLast = 1;
}

void addMove(GameBoard *gameBoard, List *list, int row, int column, int prevValue) {
    if (list->head == NULL) {
        list->head = createNode(row, column, getCellValue(gameBoard, column, row), 0, NULL, NULL);
        list->current = list->head;
        list->isLast = 1;
        list->isFirst = 0;
    } else {
        list->current->next = createNode(row, column, getCellValue(gameBoard, column, row), prevValue, NULL,
                                         list->current);
        list->current->next->prev = list->current;
        list->current = list->current->next;
        list->isLast = 1;
        list->isFirst = 0;
    }
}

void addMoveByEach(GameBoard *gameBoard, List *list, int *rows, int *columns, int *values, int length) {
    for (i = 0; i < length; i++) {
        addMove(gameBoard, list, rows[i], columns[i], values[i]);
    }
}

void deleteLinkedListArray(ListofLists *listArray) {
    if (listArray->headLst == NULL || listArray->isLast == 1) {
        return;
    } else {
        if (listArray->isFirst == 1 && listArray->isLast == 0){
            deleteLinkedList(listArray->headLst);
            listArray->headLst = NULL;
        } else {
            tempLst = listArray->currentLst->nextLst;
            do {
                listArray->currentLst->nextLst= listArray->currentLst->nextLst->nextLst;
                deleteLinkedList(tempLst);
                tempLst = listArray->currentLst->nextLst;
            } while (tempLst != NULL);
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
        listArray->isFirst = 0;
        listArray->isLast = 1;
    } else {
        listArray->currentLst->nextLst = createLinkedList();
        addMoveByEach(gameBoard, listArray->currentLst->nextLst, rows, columns, values, length);
        listArray->currentLst->nextLst->prevLst = listArray->currentLst;
        listArray->currentLst = listArray->currentLst->nextLst;
        listArray->isFirst = 0;
        listArray->isLast = 1;
    }
}

void addMovesFromList(ListofLists *listArray, List *moveLst) {
    deleteLinkedListArray(listArray);
    if (listArray->headLst == NULL) {
        listArray->headLst = moveLst;
        listArray->currentLst = listArray->headLst;
        listArray->currentLst->nextLst = NULL;
        listArray->currentLst->prevLst = NULL;
        listArray->isFirst = 0;
        listArray->isLast = 1;
    } else {
        listArray->currentLst->nextLst = moveLst;
        listArray->currentLst->nextLst->prevLst = listArray->currentLst;
        listArray->currentLst = listArray->currentLst->nextLst;
        listArray->isFirst = 0;
        listArray->isLast = 1;
    }
}

void deleteLinkedList(List *list) {
    deleteNextMoves(list);
    if (list->head != NULL) {
        temp = list->head;
        do {
            list->head = list->head->next;
            deleteNode(temp);
            temp = list->head;
        } while (temp != NULL);
    }
}

void deleteArray(ListofLists *listArray) {
    deleteLinkedListArray(listArray);
    if (listArray->headLst != NULL){
        tempLst = listArray->headLst;
        do {
            listArray->headLst = listArray->headLst->nextLst;
            deleteLinkedList(tempLst);
            tempLst = listArray->headLst;
        } while (tempLst != NULL);
    }
}

void emptyLst(List *lst) {
    if (lst->current != NULL) {
        while (lst->current != lst->head) {
            lst->current = lst->current->prev;
            deleteNode(lst->current->next);
        }
        deleteNode(lst->current);
    }
    if (lst->head != NULL) {
        free(lst->head);
        lst->head = NULL;
    }
}

Node *deleteCellFromList(List *lst, int column, int row) {
    if (lst->current == NULL) {
        return NULL;
    } else {
        temp = lst->current;
        while (temp != lst->head) {
            if (temp->x == column && temp->y == row) {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                return temp;
            }
            temp = temp->prev;
        }
    }
    return NULL;
}



