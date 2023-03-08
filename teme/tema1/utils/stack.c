#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void freeNodeStack(Stack startNode){
    free(startNode->value);
    free(startNode);
}

void printStack(Stack startNode){
    if(startNode == NULL){
        printf("Queue gol!\n");
        return;
    }
    for(Stack aux = startNode; aux != NULL; aux = aux->next){
        printf("%s\n", aux->value);
    }
    printf("\n");
}
Stack createNodeStack(char* value){
    Stack output = (Stack)calloc(1, sizeof(AStack));
    output->value = (char*)calloc(30, sizeof(char));
    strcpy(output->value, value);
    output->next = NULL;
    return output;
}

Stack push(Stack startNode, char* value){
    Stack first = createNodeStack(value);
    first->next = startNode;
    return first;
}

int isEmpty(Stack startNode){
    if(startNode == NULL){
        return 1;
    }
    return 0;
}

char* pop(Stack* startNode){
    if((*startNode) == NULL){
        printf("Stack gol!\n");
        return NULL;
    }
    Stack aux = (*startNode);
    (*startNode) = (*startNode)->next;
    char* output = strdup(aux->value);
    freeNodeStack(aux);
    return output;
}