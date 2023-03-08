typedef struct stack{
    char* value;
    struct stack *next;
}*Stack, AStack;

int isEmpty(Stack startNode);
void freeNodeStack(Stack startNode);
Stack createNodeStack(char* value);
Stack push(Stack startNode, char* value);
char* pop(Stack* startNode);
void printStack(Stack startNode);
