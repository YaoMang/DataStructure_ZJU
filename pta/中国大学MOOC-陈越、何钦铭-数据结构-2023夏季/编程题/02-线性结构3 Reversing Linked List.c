#include <stdio.h>
#include <stdlib.h>

struct Node{
    int Data;
    int nextAddr;
};

typedef struct Node* List;

const int LIST_SIZE = 100000;
List space = NULL;
int firstAddr = 0;
int totalNum = 0;
int reverseNum = 0;

int read();
int print(int L);

// reverse a list and returns its head pointer
int reverse(int L);

int main()
{
    int L = read();

    L = reverse(L);

    // Proof that function read() could work properly
    //printf("%d", space);
    print(L);

    return 0;
}

int read()
{
    //printf("%d\n", sizeof(*space));
    // Size of a Node is 8 Bytes

    space = malloc(sizeof(*space)*LIST_SIZE);
    scanf("%d %d %d", &firstAddr, &totalNum, &reverseNum);
    getchar();
    int addr, data, next;
    //printf("%d %d %d", firstAddr, totalNum, reverseNum);
    for(int i = 0; i < totalNum; ++i){
        scanf("%d %d %d", &addr, &data, &next);
        getchar();

        //printf("%d %d %d\n", addr, data, next);
        space[addr].Data = data;
        space[addr].nextAddr = next;
    }
    return firstAddr;
}

int print(int L)
{
    //printf("%d",L);
    int addr = L;    
    
    while (space[addr].nextAddr != -1)
    {
        printf("%05d %d %05d\n", addr, space[addr].Data, space[addr].nextAddr);
        addr = space[addr].nextAddr;
    }
    printf("%05d %d %d", addr, space[addr].Data, space[addr].nextAddr);
    
    return 0;
}

int reverse(int L)
{
    int addr = L;
    List tail;
    List ret = malloc(sizeof(*tail));
    tail = ret;
    tail->nextAddr = L;
    //print(ret->nextAddr);

    int isValid = 1;

    while(addr != -1){
        // check if the address is valid
        addr = tail->nextAddr;
        for(int i = 0; i < reverseNum; ++i){
            if(addr == -1){
                isValid = 0;
                break;
            }
            addr = space[addr].nextAddr;
        }
        if(isValid){
            addr = tail->nextAddr;

            int pPrev = addr;
            int pNow = space[pPrev].nextAddr;
            int pNext = space[pNow].nextAddr;

            for(int i = 0; i < reverseNum - 1; ++i){
                // reverse
                space[pNow].nextAddr = pPrev;
                
                // move forward
                pPrev = pNow;
                pNow = pNext;
                pNext = space[pNext].nextAddr;
            }

            tail->nextAddr = pPrev;
            tail = space + addr;
            tail->nextAddr = pNow;
        }
        //print(ret->nextAddr);
    }

    int reti = ret->nextAddr;
    free(ret);

    return reti;
}