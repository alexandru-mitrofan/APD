#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "pthread_barrier_mac.h"
#include "utils/arguments.h"
#include <math.h>

void fMapper(TempArgm argm){
    int threadID = argm->threadID;
    argm->bigArgument = calculateListOfPowers(threadID, argm->bigArgument);
}

void fReducer(TempArgm argm){
    int assignedPower = argm->threadID - argm->bigArgument->NR_MAPPER;
    Argm bigArgument = argm->bigArgument;
    int len = 0;
    unsigned int precval;
    Node powerList = NULL;
    for(int i = 0; i < bigArgument->NR_MAPPER;i++){
        SmallArgm smallArgm = bigArgument->vectOfArguments[i];
        Node aux = aux = smallArgm->vectListOfPowers[assignedPower];
         while(aux != NULL){
            powerList = addInOrder(powerList, aux->value);
            aux = aux->next;
        }

    }
    if(powerList != NULL){
        len++;
        precval=powerList->value;
    }
    while(powerList != NULL){
        if(precval!= powerList->value){
            len ++;
        }
        precval = powerList->value;
        powerList = powerList->next;
    }
    

    writeToFile(assignedPower + 2,len);
    freeList(powerList);

    
}

void *f(void* argm){
    TempArgm tempArgm = (TempArgm)argm;
    Argm bigArgm = tempArgm->bigArgument;
    int threadID = tempArgm->threadID;
    if(threadID < bigArgm->NR_MAPPER){
        fMapper(tempArgm);
    }
    pthread_barrier_wait(&(bigArgm->barrier));
    if(threadID >= bigArgm->NR_MAPPER){
        fReducer(tempArgm);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    if(argc < 4){
        printf("Numar prea mic de argumente!\n");
        exit(-1);
    }
    Argm bigArgument = readFromFileArgm(argc, argv);
    int error_code = -1;
    void *status;
    printf("\n\nccc\n\n");
    pthread_t* threads = (pthread_t*)calloc(bigArgument->NR_ARGUMENTS, sizeof(pthread_t));
    TempArgm* vectTempArgm = (TempArgm*)calloc(bigArgument->NR_ARGUMENTS, sizeof(ATempArgm));
    for(int i = 0;i < bigArgument->NR_ARGUMENTS;i++){
        vectTempArgm[i] = (TempArgm)calloc(1, sizeof(ATempArgm));
        vectTempArgm[i]->threadID = i;
        vectTempArgm[i]->bigArgument = bigArgument;
        error_code = pthread_create(&threads[i], NULL, f, (void*)vectTempArgm[i]);
        if(error_code){
            printf("error creare mapper!\n");
            exit(-1);
        }
    }
    for(int i = 0;i < bigArgument->NR_ARGUMENTS;i++){
        error_code = pthread_join(threads[i], &status);
		if (error_code) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
        free(vectTempArgm[i]);
    }
    free(vectTempArgm);
    freeBigArgm(bigArgument);
    free(threads);
    return 0;
}
