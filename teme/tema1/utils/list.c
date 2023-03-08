#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
Node initNode(int value){
    Node output = (Node)calloc(1, sizeof(ANode));
    output->value = value;
    output->next = NULL;
    return output;
}

Node addToFirstList(Node startNode, int value){
    Node first = initNode(value);
    if(startNode == NULL){
        return first;
    }
    first->next = startNode;
    return first;
}

Node addInOrder(Node startNode,int value){
    Node order = initNode (value);
    if (startNode == NULL || startNode->value >= value)
    {
        order->next = startNode;

        return order;
    }
 
    // locate the node before the point of insertion
    Node current = startNode;
    while (current->next != NULL && current->next->value < order->value) {
        current = current->next;
    }
 
    order->next = current->next;
    current->next = order;
    return startNode;
}

void freeList(Node startNode){
    Node aux = startNode;
    Node tmp = NULL;
    while(aux != NULL){
        tmp = aux;
        aux = aux->next;
        free(tmp);
    }
    return;
}

int lengthList(Node startNode){
    if(startNode == NULL){
        return 0;
    }
    int output = 0;
    for(Node aux = startNode; aux != NULL; aux = aux->next){
        output++;
    }
    return output;
}

int isInList(Node startNode, int value){
    if(startNode == NULL){
        return 0;
    }
    for(Node aux = startNode; aux != NULL; aux = aux->next){
        if(aux->value == value){
            return 1;
        }
    }
    return 0;
}

void printList(Node startNode){
    if(startNode == NULL){
        printf("Lista Goala!\n");
        return;
    }
    for(Node aux = startNode; aux != NULL; aux = aux->next){
        printf("%d ", aux->value);
    }
    printf("\n");
}