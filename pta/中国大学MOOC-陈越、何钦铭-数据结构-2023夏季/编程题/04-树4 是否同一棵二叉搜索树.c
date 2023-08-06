// 本题使用课程内容第二种思路实现

#include <stdio.h>
#include <stdlib.h>

struct D_Node{
    int Data;
    int flag;
    struct D_Node* LT;
    struct D_Node* RT;
};

typedef struct D_Node* BinaryTree;

BinaryTree InsertBST(BinaryTree BST, int Data)
{
    if(BST){
        BinaryTree it = BST;
        int isFound = 0;
        while(1){
            if(Data < it->Data){
                if(it->LT){
                    it = it->LT;
                }
                else{
                    isFound = 1;
                    break;
                }
            }
            else if(Data > it->Data){
                if(it->RT){
                    it = it->RT;
                }
                else{
                    isFound = 2;
                    break;
                }
            }
            else{
                break;
            }
        }

        if(isFound){
            BinaryTree OpTgt = malloc(sizeof(*OpTgt));
            OpTgt->Data = Data;
            OpTgt->LT = NULL;
            OpTgt->RT = NULL;

            if(isFound == 1){
                it->LT = OpTgt;
            }
            else{
                it->RT = OpTgt;
            }
        }
    }
    else{
        BST = malloc(sizeof(*BST));
        BST->Data = Data;
        BST->LT = NULL;
        BST->RT = NULL;
    }

    return BST;
}

BinaryTree BuildTree(int n, int array[])
{
    BinaryTree ret = NULL;

    for(int i = 0; i < n; ++i){
        ret = InsertBST(ret, array[i]);
    }

    return ret;
}

int SetFlag(BinaryTree BST, int flag)
{
    if(BST){
        BST->flag = flag;
        SetFlag(BST->LT, flag);
        SetFlag(BST->RT, flag);
    }
    else{
        return flag;
    }
}

BinaryTree DestroyTree(BinaryTree BST){
    if(!BST){
        return BST;
    }
    else{
        if(BST->LT){
            BST->LT = DestroyTree(BST->LT);
        }
        else if(BST->RT){
            BST->RT = DestroyTree(BST->RT);
        }
        else{
            free(BST);
            BST =  NULL;
            return BST;
        }
    }
}

int ifTheSameTree(BinaryTree Sample, int array[], int N_array)
{
    BinaryTree it; // 迭代器
    int isSameTree = 1;
    SetFlag(Sample, 0); // 设置所有flag为0
        
    for(int i = 0; i < N_array; ++i){
        // 寻找第i个数
        it = Sample;

        // 开始寻找
        while(1){
            // 结点是否被访问过
            if(it->flag){
                // 访问过，继续寻找
                if(array[i] < it->Data){
                    it = it->LT;
                }
                else if(array[i] > it->Data){
                    it = it->RT;
                }
            }
            else{
                // 没有访问过
                if(array[i] == it->Data){
                    // 当前值与结点相等，已经找到，开始下一轮循环
                    it->flag = 1;
                    break;
                }
                else{
                    // 发现没有访问过的结点，不是同一棵树
                    isSameTree = 0;
                    // 跳出循环
                    goto TAG_END_OF_FUNC_147;
                }
            }
        }
    }

    TAG_END_OF_FUNC_147:
    return isSameTree;
}

int main()
{
    int buffer[64];
    int result[255];
    int cnt = -1;

    BinaryTree Tree;

    // READ INPUT
    int N_Num = 1, G_Num = 0;
    while(N_Num){
        scanf("%d", &N_Num);
        if(N_Num){
            scanf("%d", &G_Num);

            // BUILD SAMPLE TREE
            for(int i = 0; i < N_Num; ++i){
                scanf("%d", buffer + i);
            }

            Tree = BuildTree(N_Num, buffer);

            // CHECK IF THE SAME
            for(int i = 0; i < G_Num; ++i){
                for(int j = 0; j < N_Num; ++j){
                    scanf("%d", buffer + j);
                }
                ++cnt;
                result[cnt] = ifTheSameTree(Tree, buffer, N_Num);
            }

            Tree = DestroyTree(Tree);
        }
    }

    for(int i = 0; i < cnt; ++i){
        if(result[i]){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
    if(result[cnt]){
        printf("Yes");
    }
    else{
        printf("No");
    }

    return 0;
}