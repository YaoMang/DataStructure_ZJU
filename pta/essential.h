#ifndef _HEADER_ESSENTIAL_H_
#define _HEADER_ESSENTAIL_H_

#include <stdlib.h>

/*
 * Singly Linked List
 * 
 * Have a single Pointer Domain
 */
struct Node_SP
{
    int Data;
    struct Node_SP* Next;
};

typedef struct Node_SP* List;

List CreateList()
{
    List ret = (List)malloc(sizeof(*ret));
    ret->Next = NULL;
    ret->Data = 0;

    return ret;
}

List isEmptyList(List L)
{
    if(L->Next){
        
    }
}



#endif