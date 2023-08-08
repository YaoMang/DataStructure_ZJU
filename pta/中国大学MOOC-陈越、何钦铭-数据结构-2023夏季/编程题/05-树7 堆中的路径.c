// 堆的基本操作
// 题目要求依次插入

#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_VALUE 10000
#define MIN_DATA_VALUE -10000

// 堆
struct Heap{
    int* Data;
    int Size;
    int Capacity;
};

// 最小堆
typedef struct Heap* MinHeap;

// 建立一个空堆
MinHeap CreateMinHeap()
{
    MinHeap ret = (MinHeap)malloc(sizeof(*ret));
    ret->Data = NULL;
    ret->Size = 0;
    ret->Capacity = 0;

    return ret;
}

int swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;

    return 0;
}


// 直接在数组中完成堆的调整，要求数组是一个完全二叉树，并且空出array[0]，这个函数会释放原有数据
MinHeap AjustMinHeap(MinHeap MH, int array[], int n)
{
    // 检查原数据是否有效
    if(MH->Data){
        // 释放原最小堆空间
        free(MH->Data);
        MH->Data = NULL;
    }
    
    MH->Data = array;
    MH->Data[0] = MIN_DATA_VALUE - 1;

    MH->Capacity = n;
    MH->Size = n;

    // 开始调整操作

    // 设置初始结点为最后一个结点的父结点
    int i = n/2;
    // 检查结点是否有右子树
    if(2 * i + 1 <= MH->Size){
        if(MH->Data[2*i + 1] < MH->Data[i]){ // 具有右子树且右子树小于父结点
            // 交换两结点
            swap(&(MH->Data[2*i + 1]), &(MH->Data[i]));
        }
        if(MH->Data[2*i] < MH->Data[i]){ // 左子树判断
            // 交换
            swap(&(MH->Data[2*i]), &(MH->Data[i]));
        }
        --i;
    }

    for(; i > 0; --i){
        if(MH->Data[i] > MH->Data[2*i + 1]){
            swap(&(MH->Data[i]), &(MH->Data[2*i + 1]));
        }
        if(MH->Data[i] > MH->Data[2 * i]){
            swap(&(MH->Data[i]), &(MH->Data[2*i]));
        }
    }

    return MH;
}

void Insert(MinHeap MH, int n)
{
    ++MH->Size;
    MH->Data[MH->Size] = n;
    
    int i = MH->Size;
    while(MH->Data[i] < MH->Data[i/2]){
        swap(&MH->Data[i], &MH->Data[i/2]);
        i /= 2;
    }
}

void printTrace(MinHeap MH, int n)
{
    int i = n;
    while(i != 1){
        printf("%d ", MH->Data[i]);
        i /= 2;
    }
    printf("%d", MH->Data[i]);

    return;
}

int main()
{
    int n_Num, n_Traversal;

    scanf("%d %d", &n_Num, &n_Traversal);
    int* array = (int*)malloc(sizeof(*array)*(n_Num + 1));

    MinHeap MH = CreateMinHeap();
    MH->Data = array;
    *array = MIN_DATA_VALUE - 1;
    int buf;

    for(int i = 1; i <= n_Num; ++i){
        scanf("%d", &buf);
        Insert(MH, buf);
    }

    for(int i = 0; i < n_Traversal; ++i){
        scanf("%d", &n_Num);
        printTrace(MH, n_Num);
        if(i < n_Traversal - 1){
            printf("\n");
        }
    }

    return 0;
}
