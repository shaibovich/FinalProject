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
};

Node *node, *temp;
List *newList;

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


Node *getNext(List *list) {
    return list->current->next;
}

Node *getPrev(List *list) {
    if (list->current == list->head) {
        return NULL;
    } else {
        return list->current->prev;
    }
}

Node *copyNode(Node *node) {
    return createNode(node->x, node->y, node->value, node->prevValue, node->next, node->prev);
}

void deleteNode(Node *node) {
    free(node);
}

Node *undoMove(List *list, int isReset) {
    if (list->head == NULL||list->current==NULL||list->head->value==-1||list->current->value==-1) {
        if (!isReset) {
            printNoMovesToUndo();
        }
        return NULL;
    }
    temp = list->current;
    if (list->current == list->head) {
        list->current = NULL;
    } else {
        list->current = list->current->prev;
    }
    printUndoValue(temp->y + 1, temp->x + 1, temp->value, temp->prevValue);
    return temp;
}

Node *redoMove(List *list) {
    if (list->head == NULL) {
        printNoMovesToRedo();
        return NULL;
    }
    if (list->current == NULL) {
        list->current = list->head;
        printRedoValue(list->current->x + 1, list->current->y + 1, list->current->prevValue, list->current->value);
        return list->current;
    } else if (list->current->next == NULL) {
        printNoMovesToRedo();
        return NULL;
    }
    temp = list->current;
    list->current = list->current->next;
    printRedoValue(temp->y + 1, temp->x + 1, temp->prevValue, temp->value);
    return temp;
}


void deleteNextMoves(List *list) {
    temp = NULL;
    if (list->head == NULL) {
        return;
    } else if (list->current == NULL) {
        temp = list->head->next;
        while (temp != NULL) {
            free(temp->prev);
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


void addMove(GameBoard *gameBoard, List *list, int row, int column, int value) {
    deleteNextMoves(list);
    if (list->head == NULL) {
        list->head = createNode(row, column, getCellValue(gameBoard, column, row), 0, NULL, NULL);
        list->current = list->head;
    } else {
        list->current->next = createNode(row, column, getCellValue(gameBoard, column, row), value, NULL, list->current);
        list->current->next->prev = list->current;
        list->current = list->current->next;
    }
}

void deleteLinkedList(List *list) {
    deleteNextMoves(list);
    if (list->current != NULL) {
        while (list->current != list->head) {
            list->current = list->current->prev;
            free(list->current->next);
        }
        free(list->current);
    }
    free(list);
}




