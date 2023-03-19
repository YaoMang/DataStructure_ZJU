#include <stdint.h>
#include <stdlib.h>

#define INVALID_VALUE 0x01 << (sizeof(ElementType)*8 - 1)

typedef struct _S_LIST_NODE Node;
typedef struct _S_LIST* List;
typedef int ElementType;
typedef Node* Position;
typedef uint8_t bool;

struct _S_LIST_NODE{
    ElementType data;
    Node* next;
};

struct _S_LIST{
    Node* head;
};

List MakeEmpty();
ElementType FindKth(List L, int i);
Position Find(List L, ElementType X);
bool Insert(List L, ElementType X, int i);
bool Delete(List L, int i);
int Length(List L);

List MakeEmpty()
{
    List L = (List)malloc(sizeof(*L));
    L->head = NULL;

    return L;
}

ElementType FindKth(List L, int i)
{
    Node* p = L->head;
    ElementType ret = INVALID_VALUE;
    if(p != NULL){
        int n = 0;
        for(n = 0; n < i; ++n){
            if(p->next != NULL){
                p = p->next;
            }
            else{
                break;
            }
        }

        if(n == i){
            ret = p->data;
        }
        else{
            ret = INVALID_VALUE;
        }
    }
    return ret;
}

Position Find(List L, ElementType X)
{
    Position ret = NULL;
    Node* p = L->head;
    if(p != NULL){
        while(p->next != NULL){
            p = p->next;
            if(p->data == X){
                ret = p;
                break;
            }
        }
    }
    return ret;
}

bool Insert(List L, ElementType X, int i)
{
    bool ret;

    /*insert before*/
    Node* p_ib = L->head;
    /*insert after*/
    Node* p_ia = NULL;

    if(p_ib != NULL){
        int cnt = 0;
        while(cnt < i && p_ib->next != NULL){
            p_ia = p_ib;
            p_ib = p_ib->next;

            ++cnt;
        }

        if(cnt == i){
            Node* newNode = (Node*)malloc(sizeof(*newNode));
            newNode->data = X;
            newNode->next = p_ib;
            p_ia->next = newNode;
            ret = 1;
        }
    }
    
    return ret;
}

bool Delete(List L, int i)
{
    bool ret = 1;
    Node* n_ptr = L->head;
    Node* n_ptr_prev = NULL;
    Node* freeTarget = NULL;

    if(n_ptr != NULL){
        int cnt = 0;
        while(cnt < i && n_ptr ->next != NULL){
            n_ptr_prev = n_ptr;
            n_ptr = n_ptr->next;

            ++cnt;
        }

        if(cnt == i){
            if(n_ptr_prev == NULL){
                if(n_ptr->next == NULL){
                    free(L->head);
                    L->head = NULL;
                }
                else{
                    L->head = n_ptr->next;
                    free(n_ptr);
                }
            }
            else{
                freeTarget = n_ptr;
                n_ptr_prev->next = n_ptr->next;
                free(freeTarget);
            }
            ret = 1;
        }
    }

    return ret;
}

int Length(List L)
{
    Position p = L->head;
    int lenth = 0;

    while(p != NULL){
        ++lenth;
        p = p->next;
    }

    return lenth;
}

bool AppendNode(List L, ElementType X)
{
    Node* last = L->head;
    
    Node* newNode = (Node*)malloc(sizeof(*newNode));
    newNode->data = X;
    newNode->next = NULL;

    if(last != NULL){
        while(last->next != NULL){
            last = last->next;
        }
        last->next = newNode;
    }
    else{
        L->head = newNode;
    }

    return 1;
}

/* TEST PROGRAM */

#include <stdio.h>
int printList(List L)
{
    Node* n_ptr = L->head;

    for(int i = 0; i < Length(L); ++i){
        printf("%d ", n_ptr->data);
        n_ptr = n_ptr->next;
    }
    printf("\n");
    return 0;
}

int main()
{
    List list = MakeEmpty();
    for(int i = 0; i < 15; ++i){
        AppendNode(list, i);
    }

    printList(list);
    Delete(list, 0);
    printList(list);

    return 0;
}