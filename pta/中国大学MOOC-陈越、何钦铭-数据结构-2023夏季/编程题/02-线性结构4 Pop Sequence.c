#include <stdio.h>
#include <stdlib.h>

/* Stack.h if possible */
struct Stack{
    int MAX_SIZE;
    int* ARRAY;
    int TOP;
    //List
};

typedef struct Stack* Stack;

Stack CreateStack(int MAX_SIZE)
{
    Stack ret = malloc(sizeof(Stack));
    ret->MAX_SIZE = MAX_SIZE;
    ret->ARRAY = malloc(sizeof(*ret->ARRAY)*MAX_SIZE);
    ret->TOP = -1;

    return ret;
}

int isEmpty(Stack S)
{
    int ret = 0;
    if(S->TOP == -1){
        ret = 1;
    }
    return ret;
}

int isFull(Stack S)
{
    int ret = 0;
    if(S->TOP == S->MAX_SIZE - 1){
        ret = 1;
    }
    return ret;
}

int Push(Stack S, int data)
{
    int ret = 0;
    if(isFull(S)){
        ret = -1;
    }
    else{
        S->TOP += 1;
        S->ARRAY[S->TOP] = data;
    }

    return ret;
}

int Pop(Stack S)
{
    int ret = 0;
    if(isEmpty(S)){
        ret = -1;
    }
    else{
        //S->ARRAY[S->TOP] = 0; // This line of code could be deleted
        S->TOP -= 1;
    }

    return ret;
}

int Peek(Stack S)
{
    int ret;
    if(isEmpty(S)){
        ret = -1;
    }
    else{
        ret = *(S->ARRAY+S->TOP);
    }
    return ret;
}

Stack DestroyStack(Stack S)
{
    S->MAX_SIZE = 0;
    S->TOP = -1;
    free(S->ARRAY);
    free(S);
    return NULL;   
}

/* END OF Stack.h */


/*
 *  Start of our main program
 */

int M_SIZE = 0;
int N_NUMBER = 0;
int K_LINES = 0;

int* buffer = NULL;
int* result = NULL;
Stack S;

int isValid();

int main()
{
    // DATA INPUT
    scanf("%d %d %d", &M_SIZE, &N_NUMBER, &K_LINES);
    getchar();

    // memory allocate
    S = CreateStack(M_SIZE);
    buffer = malloc(sizeof(*buffer)*N_NUMBER);
    result = malloc(sizeof(*result)*K_LINES);

    // Main data & process
    for(int i = 0; i < K_LINES; ++i){
        for(int j = 0; j < N_NUMBER; ++j){
            scanf("%d", buffer + j);
        }
        getchar();
        //for(int i = 0; i < N_NUMBER; ++i){
        //    printf("%d\t",*(buffer + i));
        //}
        //putchar('\n');
        *(result + i) = isValid();
    }

    // OUT PUT BY LINES
    for(int i = 0; i < K_LINES; ++i){
        if(*(result + i)){
            printf("YES");
        }
        else{
            printf("NO");
        }
        if(i < K_LINES - 1){
            putchar('\n');
        }
    }

    DestroyStack(S);
    free(buffer);
    free(result);

    return 0;
}

int isValid()
{
    int ret = 1;
    int* pCheck = buffer;

    for(int i = 1; i <= N_NUMBER; ++i){
        if(Push(S, i) == -1){
            ret = 0;
        }
        while(*pCheck == Peek(S)){
            //printf("ARRAY\t%d\tSTACKTOP\t%d\n", *pCheck, Peek(S));
            ++pCheck;
            Pop(S);
        }
    }

    // CLR Stack
    if(!isEmpty(S)){
        ret = 0;
    }
    while (!isEmpty(S))
    {
        Pop(S);
    }
    
    return ret;
}