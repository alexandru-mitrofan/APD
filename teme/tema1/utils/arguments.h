#include "stack.h"
#include "list.h"
#define LEN_STEST_PATH 100
//#include "pthread_barrier_mac.h"
typedef struct smallArgm{
    int numberOfPowers;
    Node* vectListOfPowers;
}*SmallArgm,ASmallArgm;

typedef struct argm{
    int NR_MAPPER;
    int NR_REDUCER;
    int NR_ARGUMENTS;
    SmallArgm* vectOfArguments;
    pthread_barrier_t barrier;
    pthread_mutex_t mutex;
    Stack pathOfFiles;
}*Argm, AArgm;

typedef struct tempArg{
    int threadID;
    Argm bigArgument;
}*TempArgm, ATempArgm;

void writeToFile(int power,int len);
Argm initBigArgument(int NR_MAPPER, int NR_REDUCER);
Argm readFromFileArgm(int argc, char* argv[]);
Argm calculateListOfPowers(int threadID, Argm argm);
void freeBigArgm(Argm bigArgm);
int binarySearchPow(unsigned int mini,unsigned int maxi,unsigned int nr ,unsigned int power);