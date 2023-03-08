#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "pthread_barrier_mac.h"
#include "arguments.h"
#include <math.h>

int binarySearchPow(unsigned int mini,unsigned int maxi,unsigned int nr ,unsigned int power){
    int mid;
    int realnr;
    while(mini <= maxi){
        mid = mini + (maxi - mini) / 2;
        realnr = pow(mid, power);
        if(realnr == nr)
            return 1;
        if(realnr < nr)
            mini = mid + 1;
        else
            maxi = mid - 1;
        
    }
    return 0;

}

Argm calculateListOfPowers(int threadID, Argm argm){
    while(argm->pathOfFiles != NULL){
        pthread_mutex_lock(&(argm->mutex));
        char* path = pop(&(argm->pathOfFiles));
        printf("Proccesing file: %s din thread: %d\n", path, threadID);
        pthread_mutex_unlock(&(argm->mutex));
        FILE* smallTestFile = fopen(path, "r");
        int numberOfValues = -1;
        fscanf(smallTestFile, "%d", &numberOfValues);
        for(int i = 0;i < numberOfValues;i++){
            unsigned int value = 0;
            fscanf(smallTestFile, "%d", &value);
            if(value <= 0){
                continue;
            }
            if(value != 0){
                for(int k = 2; k < argm->NR_REDUCER + 2; k++){
                    
                    if(value == 1){
                        argm->vectOfArguments[threadID]->vectListOfPowers[k-2] = 
                            addToFirstList(argm->vectOfArguments[threadID]->vectListOfPowers[k-2], value);
                    }else{
                        unsigned int maxi = (unsigned int)pow(2,(int)floor(32.0/k)+1);
                        if(binarySearchPow(2,maxi,value,k) == 1){

                            argm->vectOfArguments[threadID]->vectListOfPowers[k-2] = 
                                addToFirstList(argm->vectOfArguments[threadID]->vectListOfPowers[k-2], value);
                        }
                    }
                    
                }
            }
        }
        free(path);
        fclose(smallTestFile);
    }
    return argm; 
}

Argm initBigArgument(int NR_MAPPER, int NR_REDUCER){
    Argm output = calloc(1, sizeof(AArgm));
    output->NR_MAPPER = NR_MAPPER;
    output->NR_REDUCER = NR_REDUCER;
    output->NR_ARGUMENTS = NR_MAPPER + NR_REDUCER;
    output->pathOfFiles = NULL;
    return output;
}

Argm readFromFileArgm(int argc, char* argv[]){
    char testPath[100];
    strcpy(testPath, argv[3]);
    Argm bigArgument = initBigArgument(atoi(argv[1]), atoi(argv[2]));
    pthread_barrier_init(&(bigArgument->barrier), NULL, bigArgument->NR_MAPPER + bigArgument->NR_REDUCER);
    pthread_mutex_init(&(bigArgument->mutex), NULL);
    int nrSmallTests;
    FILE* testFile = fopen(testPath, "r+");
    FILE* output = fopen("./output.txt", "w+");
    fscanf(testFile, "%d", &nrSmallTests);
    char smallTestPath[100];
    for(int i = 0; i < nrSmallTests;i++){
        fscanf(testFile, "%s", smallTestPath);
        bigArgument->pathOfFiles = push(bigArgument->pathOfFiles, smallTestPath);
    }
    fclose(testFile);
    fclose(output);
    bigArgument->vectOfArguments = (SmallArgm*)calloc(bigArgument->NR_ARGUMENTS, sizeof(SmallArgm));
    for(int i = 0;i < bigArgument->NR_ARGUMENTS; i++){
        bigArgument->vectOfArguments[i] = (SmallArgm)calloc(1, sizeof(ASmallArgm));
        bigArgument->vectOfArguments[i]->numberOfPowers = bigArgument->NR_REDUCER;
        bigArgument->vectOfArguments[i]->vectListOfPowers = (Node*)calloc(bigArgument->NR_REDUCER, sizeof(Node));
    }
    return bigArgument;
}

void writeToFile( int power, int len){
    char path[20] = "./outX.txt";
    path[5] = power + '0';
    FILE* outputFile = fopen(path, "w");
    fprintf(outputFile, "%d", len);
    fclose(outputFile);
}

void freeSmallArgm(SmallArgm smallArgm){
    for(int i = 0;i < smallArgm->numberOfPowers;i++){
        freeList(smallArgm->vectListOfPowers[i]);
    }
    free(smallArgm->vectListOfPowers);
    free(smallArgm);
}

void freeBigArgm(Argm bigArgm){
    for(int i = 0; i < bigArgm->NR_ARGUMENTS;i++){
        freeSmallArgm(bigArgm->vectOfArguments[i]);
    }
    free(bigArgm->vectOfArguments);
    pthread_barrier_destroy(&(bigArgm->barrier));
    pthread_mutex_destroy(&(bigArgm->mutex));
    free(bigArgm);
}