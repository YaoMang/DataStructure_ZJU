#include <stdio.h>
#include <stdlib.h>

// TREE DEFINE

struct BT{
    int LT;
    int RT;
};

typedef struct BT* BT;

BT CreateTree(int MAX_SIZE);

BT CreateTree(int MAX_SIZE)
{
    BT ret = malloc(sizeof(*ret)*MAX_SIZE);
    return ret;
}

struct Node
{
    int data;
    struct Node* Next;
};

typedef struct Node* List;

struct Queue
{
    List head;
};

typedef struct Queue* Queue;

int isEmpty(Queue Q);

Queue CreateQueue()
{
    Queue ret = malloc(sizeof(Queue));
    ret->head = NULL;

    return ret;
}

Queue EnQueue(Queue Q, int data)
{
    if(isEmpty(Q)){
        Q->head = malloc(sizeof(*(Q->head)));
        Q->head->data = data;
        Q->head->Next = NULL;
    }
    else{
        List it = Q->head;
        while(it->Next){
            it = it->Next;
        }
        it->Next = malloc(sizeof(*it));
        it = it->Next;
        it->data = data;
        it->Next = NULL;
    }

    return Q;
}

int DeQueue(Queue Q)
{
    int ret = -1;
    if(isEmpty(Q)){
        ret = -1;
    }
    else{
        ret = Q->head->data;
        List nextNode = Q->head->Next;
        free(Q->head);
        Q->head = nextNode;
    }
    return ret;
}

int isEmpty(Queue Q)
{
    if(Q->head){
        return 0;
    }
    else{
        return 1;
    }
}

int printQueue(Queue Q)
{
    if(isEmpty(Q)){
        return -1;
    }
    else{
        List it = Q->head;
        while(it){
            printf("%d", it->data);
            it = it->Next;
        }
    }
    return 0;
}

void listLeaves(int Tree);

BT space = NULL;
Queue Q = NULL;

int main()
{
    Q = CreateQueue();
    int MAX_SIZE = 0;

    int Tree;
    // READ SIZE MESSAGE
    scanf("%d", &MAX_SIZE);
    getchar();

    space = CreateTree(MAX_SIZE);

    // READ DATA MESSAGE
    for(int i = 0; i < MAX_SIZE; ++i){
        char bufLT, bufRT;
        scanf("%c %c", &bufLT, &bufRT);
        getchar();

        // Pre process of the data input
        if(bufLT == '-')
            bufLT = -1;
        else
            bufLT -= 0x30;
        if(bufRT == '-')
            bufRT = -1;
        else
            bufRT -= 0x30;
        
        space[i].LT = (int)bufLT;
        space[i].RT = (int)bufRT;
    }
    
    // FIND ROOT NODE

    // INIT ARRAY
    int* map_rn = malloc(sizeof(*map_rn)*MAX_SIZE);
    for(int i = 0; i < MAX_SIZE; ++i){
        map_rn[i] = 0;
    }
    // TAG INFO
    for(int i = 0; i < MAX_SIZE; ++i){
        if(space[i].LT != -1){
            map_rn[space[i].LT] = 1;
        }
        if(space[i].RT != -1){
            map_rn[space[i].RT] = 1;
        }
    }
    // GET ROOT NODE
    for(int i = 0; i < MAX_SIZE; ++i){
        if(!map_rn[i]){
            Tree = i;
            break;
        }
    }
    //printf("%d", Tree);

    // DESTROY ARRAY
    free(map_rn);

    //Input TEST
    //for(int i = 0; i < MAX_SIZE; ++i){
    //    printf("%d %d", space[i].LT, space[i].RT);
    //}
    
    // List Leaves
    listLeaves(Tree);
    
    return 0;
}

/*
void listLeaves(int T)
{
    if(space[T].LT == -1 && space[T].RT == -1){
        printf("%d", T);
    }
    if(space[T].LT != -1){
        listLeaves(space[T].LT);
    }
    if(space[T].RT != -1){
        listLeaves(space[T].RT);
    }
}
*/

void listLeaves(int T)
{
    int BT = 0;
    EnQueue(Q, T);
    int tag_1 = 1;
    while(!isEmpty(Q)){
        BT = DeQueue(Q);
        if(space[BT].LT == -1 && space[BT].RT == -1){
            if(tag_1){
                tag_1 = 0;
            }
            else{
                putchar(' ');
            }
            printf("%d", BT);
        }
        if(space[BT].LT != -1){
            EnQueue(Q, space[BT].LT);
        }
        if(space[BT].RT != -1){
            EnQueue(Q, space[BT].RT);
        }
        //printQueue(Q);
    }
}