// 这个任务希望我们通过堆栈的操作得到后序遍历的结果
// 思路可以来自课程讨论

#include <stdio.h>
#include <stdlib.h>

/*----------*/
// DEFINITION OF STACK
// THIS VERSION OF STACK IS IMPLEMENTED WITH SINGLY LINKED LIST
/*----------*/

struct Node{
    int Data;
    struct Node* Next;
};

typedef struct Node* Stack;

Stack CreateStack()
{
    Stack ret = malloc(sizeof(*ret));
    ret->Data = -1;
    ret->Next = NULL;

    return ret;
}

int isEmpty(Stack S)
{
    return S->Next?0:1;
}

void Push(Stack S, int Data)
{
    Stack it = malloc(sizeof(*it));
    it->Data = Data;
    it->Next = S->Next;
    S->Next = it;

    return;
}

int Pop(Stack S, int Data)
{
    if(isEmpty(S)){
        //PRINT IS FOR DEBUG ONLY
        printf("POP ERROR, STACK EMPTY!");

        return -1;
    }
    Stack temp = S->Next;
    S->Next = temp->Next;
    
    int ret = temp->Data;
    free(temp);
    return ret;
}

/*----------*/
// END OF STACK IMPLEMENTATION
/*----------*/

struct BinaryTree{
    int Data;
    struct BinaryTree* LT;
    struct BinaryTree* RT;
};

typedef struct BinaryTree* BinaryTree;

Stack S = NULL;
int NumInput = 0;
int* StackOP = NULL;

// TARGET IS BUILD A TREE WITH INFO
void read();
BinaryTree buildTree(int* StackOP, int n);
void postTraversal(BinaryTree BT);

int main()
{
    read();

/*
 *   for(int i = 0; i < NumInput*2; ++i){
 *       printf("%d\n",StackOP[i]);
 *   }
 */ // Input check

    BinaryTree BT = NULL;
    BT = buildTree(StackOP, NumInput);
    postTraversal(BT);
    return 0;
}

void read()
{
    // STEP 1 READ INPUT
    scanf("%d", &NumInput);
    StackOP = calloc(2*NumInput,sizeof(*StackOP));

    char buffer[32];
    int input;

    for(int i = 0; i < NumInput*2; ++i){
        scanf("%s", buffer);
        if(buffer[1] == 'u'){
            scanf("%d", &input);
            StackOP[i] = input;
            getchar();
        }
        //printf("%s\n", buffer);
    }
}

// 根据堆栈操作顺序建立二叉树
// 填充规则为：上次操作为push，遇到push时填充左子树，上次操作为pop，遇到push时填充右子树
// 指针指向上次操作的值（POP/PUSH）

BinaryTree buildTree(int* StackOP, int n)
{
    BinaryTree ROOT = malloc(sizeof(*ROOT));
    ROOT->Data = 0;
    ROOT->LT = NULL;
    ROOT->RT = NULL;

    BinaryTree it = ROOT;

    // MANUAL STACK
    BinaryTree SA[30];
    int top = -1;

    int lastOP=0;

    if(StackOP[0]){
        ROOT->Data = StackOP[0];
        lastOP = 1;
        ++top;
        SA[top]= it;
    }

    for(int i = 1; i < n*2; ++i){
        if(StackOP[i]){
            if(lastOP){
                it->LT = malloc(sizeof(*it));
                it = it->LT;
                it->Data = StackOP[i];
                it->LT = NULL;
                it->RT = NULL;

                // push
                ++top;
                SA[top] = it;

                // printf("PUSHED WITH %d in LT\n", StackOP[i]);
            }
            else{
                it->RT = malloc(sizeof(*it));
                it = it->RT;
                it->Data = StackOP[i];
                it->LT = NULL;
                it->RT = NULL;

                // push
                ++top;
                SA[top] = it;

                // printf("PUSHED WITH %d in RT\n", StackOP[i]);
            }
            lastOP = 1;
        }
        else{
            lastOP = 0;

            if(top != -1){
                it = SA[top];
                --top;
                // printf("POPED %d in RT %d\n", StackOP[i], it->Data);
            }
            else{
                printf("STACK ERROR");
                return 0;
            }
        }
    }

    return ROOT;
}

int flag = 0;
void postTraversal(BinaryTree BT)
{
    if(BT->LT){
        postTraversal(BT->LT);
    }
    if(BT->RT){
        postTraversal(BT->RT);
    }
    if(flag){
        printf(" %d", BT->Data);
    }
    else{
        printf("%d", BT->Data);
    }
    flag = 1;
}
