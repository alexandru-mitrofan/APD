#include <stdio.h>
#include <stdlib.h>	

typedef struct node{
    int value;
    struct node *next;
}*Node, ANode;

Node initNode(int value);
Node addToFirstList(Node startNode, int value);
Node addInOrder(Node startNode, int value);
void freeList(Node startNode);
void printList(Node startNode);
int isInList(Node startNode, int value);
int lengthList(Node startNode);
