#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal( BinTree BT );  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}
/* 你的代码将被嵌在这里 */

// 文件中所有操作均由递归实现
BinTree Insert( BinTree BST, ElementType X )
{
    if(!BST){
        // 传入结点无效，填充结点
        BST = (BinTree)malloc(sizeof(*BST));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    else{
        if(X > BST->Data){ // 递归插入右子树
            BST->Right = Insert(BST->Right, X);
        }
        else if(X < BST->Data){ // 递归插入左子树
            BST->Left = Insert(BST->Left, X);
        }
    }
    return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
    Position Tmp;
    if(!BST){
        printf("Not Found\n");
    }
    else{
        if(X < BST->Data){
            BST->Left = Delete(BST->Left, X);
        }
        else if(X > BST->Data){
            BST->Right = Delete(BST->Right, X);
        }
        else{
            if(BST->Left && BST->Right){
                // 同时具有左右子结点
                
                // 从左子树中找到最大元素
                Tmp = FindMax(BST->Left);
                BST->Data = Tmp->Data;
                
                // 删除最大元素
                BST->Left = Delete(BST->Left, Tmp->Data);
            }
            else{
                // 只具有左结点或者右结点，或者是叶节点
                Tmp = BST;
                if(BST->Left){
                    BST = BST->Left;    
                }
                else if(BST->Right){
                    BST = BST->Right;
                }
                else{
                    BST = NULL;
                }
                free(Tmp);
            }
        }
    }
    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    if(!BST){
        return NULL;
    }
    if(X > BST->Data){
        return Find(BST->Right, X);
    }
    else if(X < BST->Data){
        return Find(BST->Left, X);
    }
    else{
        return BST;
    }
}

Position FindMin( BinTree BST )
{
    // 空树的判断
    if(!BST){
        return NULL;
    }

    if(BST->Left){
        return FindMin(BST->Left);
    }
    else{
        return BST;
    }
}

Position FindMax( BinTree BST )
{
    // 空树的判断
    if(!BST){
        return NULL;
    }

    if(BST->Right){
        return FindMax(BST->Right);
    }
    else{
        return BST;
    }
}