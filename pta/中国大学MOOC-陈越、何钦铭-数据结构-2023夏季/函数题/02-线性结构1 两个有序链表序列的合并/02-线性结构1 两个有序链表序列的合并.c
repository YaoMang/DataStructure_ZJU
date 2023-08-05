#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    List ret = malloc(sizeof(*ret));
    List itR = NULL;
    List itP = ret;
    List N1 = L1->Next;
    List N2 = L2->Next;

    while(N1 && N2){
        if(N1->Data < N2 ->Data){
            itR = N1;
            N1 = N1->Next;
        }
        else{
            itR = N2;
            N2 = N2->Next;
        }

        if(ret->Next){
            itP->Next = itR;
            itP = itR;
        }
        else{
            ret->Next = itR;
            itP = ret->Next;
        }
    }

    itR = (N1 ? N1 : N2);
    while (itR)
    {
        itP->Next = itR;
        itP = itR;
        itR = itR->Next;   
    }

    L1->Next = NULL;
    L2->Next = NULL;

    return ret;
}