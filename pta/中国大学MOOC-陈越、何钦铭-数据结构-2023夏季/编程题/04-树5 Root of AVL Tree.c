// AVL树的基本操作

#include <stdio.h>
#include <stdlib.h>

struct AVL_Node{
    int Data;
    int Height;
    struct AVL_Node* LT;
    struct AVL_Node* RT;
};

typedef struct AVL_Node* AVLTree;

int Max(int a, int b){
    return a > b ? a : b;
}

// 递归实现
int GetHeight(AVLTree A){
    if(!A){
        // A为空树
        return -1;
    }
    else{
        // A不为空，它的高度等于两子树高最大值加1
        A->Height = Max(GetHeight(A->LT),GetHeight(A->RT))+1;
    }
    return A->Height;
}

// 左单旋
AVLTree SLR(AVLTree A)
{
    AVLTree B = A->LT;
    A->LT = B->RT;
    B->RT = A;
    A->Height = GetHeight(A);
    B->Height = GetHeight(B);

    return B;
}

// 右单旋
AVLTree SRR(AVLTree A)
{
    AVLTree B = A->RT;
    A->RT = B->LT;
    B->LT = A;
    A->Height = GetHeight(A);
    B->Height = GetHeight(B);

    return B;
}

// 左-右双旋
AVLTree LRDR(AVLTree A)
{
    // 对A左子树作右单旋
    A->LT = SRR(A->LT);
    // 对A作左单旋
    return SLR(A);
}

AVLTree RLDR(AVLTree A)
{
    // 对A右子树作左单旋
    A->RT = SLR(A->RT);
    // 对A作右单旋
    return SRR(A);
}

// 递归实现
AVLTree Insert(AVLTree A, int Data)
{
    // 判断树是否为空
    if(!A){
        // 树为空，填充传入结点
        A = (AVLTree)malloc(sizeof(*A));
        A->Data = Data;
        A->LT = NULL;
        A->RT = NULL;
        A->Height = 0;
    }
    else if(Data < A->Data){
        // 左子树递归插入
        A->LT = Insert(A->LT, Data);
        // 插入完毕，检查是否需要旋转
        if(GetHeight(A->LT)-GetHeight(A->RT)==2){
            if(Data < A->LT->Data){
                // 插入值在左子树的左子树上，左单旋
                A = SLR(A);
            }
            else{
                // 插入值在左子树的右子树上，左右双旋
                A = LRDR(A);
            }
        }
    }
    else if(Data > A->Data){
        // 右子树递归插入
        A->RT = Insert(A->RT, Data);
        // 插入完毕，检查是否需要旋转
        if(GetHeight(A->LT)-GetHeight(A->RT)==-2){
            if(Data > A->RT->Data){
                // 插入值在右子树的右子树上，右单旋
                A = SRR(A);
            }
            else{
                // 插入值在右子树的左子树上，右左双旋
                A = RLDR(A);
            }
        }
    }
    return A;
}

int main()
{
    // 读入数字数量
    int n_Num = 0;
    scanf("%d", &n_Num);

    // 创建树
    int buf = 0;
    AVLTree AT=NULL;
    for(int i = 0; i < n_Num; ++i){
        scanf("%d", &buf);
        AT = Insert(AT, buf);
    }

    // 打印根节点
    printf("%d", AT->Data);

    return 0;
}