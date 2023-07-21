#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef struct Tree* BinTree;
typedef BinTree Position;

struct Tree
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

BinTree Insert( BinTree BST, ElementType X )
{
    if(BST == NULL){
        BST = (BinTree)malloc(sizeof(*BST));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
        return BST;
    }

    BinTree nextNode = NULL;
    BinTree operator = BST;
    char LRIndicator = 0;
    do{
        if(X > operator->Data){
            operator = nextNode;
            nextNode = operator->Right;
            LRIndicator = 1;
        }
        else if(X < operator->Data){
            operator = nextNode;
            nextNode = operator->Left;
            LRIndicator = 0;
        }
        else{
            return BST;
        }
    }while(nextNode);

    if(LRIndicator){
        operator->Right = (BinTree)malloc(sizeof(*operator));
        operator = operator->Right;
    }
    else{
        operator->Left = (BinTree)malloc(sizeof(*operator));
        operator = operator->Left;
    }

    operator->Data = X;
    operator->Left = NULL;
    operator->Right = NULL;

    return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
    if(BST == NULL){
        printf("Not Found\n");
        return BST;
    }

    BinTree nextNode = NULL;
    BinTree prevNode = NULL;
    BinTree operator = BST;
    do{
        if(X > operator->Data){
            prevNode = operator;
            operator = nextNode;
            nextNode = operator->Right;
        }
        else if(X < operator->Data){
            prevNode = operator;
            operator = nextNode;
            nextNode = operator->Left;
        }
        else{
            if(operator->Left == NULL && operator->Right == NULL){
                if(prevNode == NULL){
                    free(operator);
                    BST = NULL;
                    return BST;
                }
                else{
                    BinTree* delete = prevNode->Left == operator ? &prevNode->Left : &prevNode->Right;
                    free(*delete);
                    *delete = NULL;
                    return BST;
                }
            }

            if(operator->Left == NULL || operator->Right == NULL){
                if(prevNode == NULL){
                    if(operator->Left == NULL){
                        BST = operator->Right;
                    }
                    else{
                        BST = operator->Left;
                    }
                    free(operator);
                    return BST;
                }
                else{
                    BinTree* delete = prevNode->Left == operator ? &prevNode->Left : &prevNode->Right;
                    if(operator->Left == NULL){
                        *delete = operator->Right;
                    }
                    else{
                        *delete = operator->Left;
                    }
                    free(operator);
                    return BST;
                }
            }

            BinTree baseNode = operator;
            BinTree prevNode2 = NULL;
            nextNode = operator->Left;
            do{
                prevNode2 = operator;
                operator = nextNode;
                nextNode = nextNode->Right;
            }while(nextNode);

            BinTree* delete = prevNode->Left == baseNode ? &prevNode->Left : &prevNode->Right;

            prevNode2->Right = operator->Left;
            operator->Left = baseNode->Left;
            operator->Right = baseNode->Right;
            free(*delete);
            *delete = operator;
            return BST;
        }
    }while(nextNode);

    printf("Not Found\n");
    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    if(BST == NULL){
        return NULL;
    }

    BinTree operator = BST;
    BinTree nextNode = NULL;
    do{
        if(X > operator->Data){
            nextNode = operator->Right;
        }
        else if(X < operator->Data){
            nextNode = operator->Left;
        }
        else{
            return operator;
        }
        operator = nextNode;
    }while (nextNode);
    return NULL;
}

Position FindMin( BinTree BST )
{
    if(BST == NULL){
        return BST;
    }

    while(BST->Left != NULL){
        BST = BST->Left;
    }

    return BST;
}

Position FindMax( BinTree BST )
{
    if(BST == NULL){
        return BST;
    }

    while(BST->Right != NULL){
        BST = BST->Right;
    }

    return BST;
}
