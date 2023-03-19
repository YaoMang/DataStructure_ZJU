#include <stdint.h>
#include <stdlib.h>

#define INVALID_VALUE 0x01 << (sizeof(ElementType)*8 - 1)

typedef struct _S_LIST_ARRAY* List;
typedef int ElementType;
typedef int Position;
typedef uint8_t bool;

#define MAXSIZE 256

struct _S_LIST_ARRAY{
    ElementType data[MAXSIZE];
    Position last;
};

List MakeEmpty();
ElementType FindKth(List L, int i);
Position Find(List L, ElementType X);
bool Insert(List L, ElementType X, int i);
bool Delete(List L, int i);
int Length(List L);

List MakeEmpty()
{
    List L = malloc(sizeof(*L));
    L->last = -1;
    return L;
}

ElementType FindKth(List L, int i)
{
    ElementType ret;
    if(i <= L->last){
        ret = L->data[i];
    }
    return ret;
}

Position Find(List L, ElementType X)
{
    Position ret = -1;
    for(int i = 0; i <= L->last; ++i){
        if(L->data[i] == X){
            ret = i;
            break;
        }
    }
    return ret;
}

bool Insert(List L, ElementType X, int i)
{
    bool ret = 0;
    if(L->last < MAXSIZE - 1 && i <= L->last){
        ret = 1;
        for(int n = L->last; n >= i; --n){
            L->data[n + 1] = L->data[n];
        }
        L->data[i] = X;
        ++(L->last);
    }
    return ret;
}

bool Delete(List L, int i)
{
    bool ret = 0;
    if(i >= 0 && i <= L->last){
        ret = 1;
        for(int n = i; n < L->last; ++n){
            L->data[n] = L->data[n+1];
        }
        L->data[L->last] = 0;
        --(L->last);
    }
    return ret;
}

int Length(List L)
{
    return L->last + 1;
}

/*-------------------------------------*/

#include <stdio.h>

bool push_back(List L, ElementType X)
{
    bool ret = 0;
    if(L->last < MAXSIZE - 1){
        ++(L->last);
        L->data[L->last] = X;
        ret = 1;
    }
    return ret;
}

void printList(List L)
{
    for(int i = 0; i <= L->last; ++i){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

int main()
{
    List L = MakeEmpty();
    for(int i = 0; i < 10; ++i){
        push_back(L, i);
    }

    printList(L);

    Delete(L, 0);

    printList(L);


    return 0;
}