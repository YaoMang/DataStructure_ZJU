// 各种排序的实现，此文件的一部分可以作为 essential.h的组成部分

#include <stdlib.h>

/**
 * @brief 各种排序方式以及其比较，命名规则为 X_Sort，方向为从小到大
 * @param DataType*, int N
 * @author YaoMang
 * 
 */

// 交换两元素（基础设施）
void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;

    return;
}

/**
 * @brief 简单排序部分
 * 
 */

// 冒泡排序
void Bubble_Sort(int Elements[], int N)
{
    for(int P = N; P > 0; --P)
    {
        int flag = 0;
        // P为最后一个下标加1
        for(int i = 0; i < P - 1; ++i)
        {
            // 遍历P之前的数组,下标从0到P-2
            if(Elements[i] > Elements[i + 1])
            {
                // 当A[i]大于A[i+1]时交换两元素的位置
                swap(&Elements[i], &Elements[i+1]);
                flag = 1;
            }
        }
        if(!flag){
            // 在一次循环中没有发生交换，即排序已经完成
            break;
        }
    }

    return;
}

// 插入排序
void Insertion_Sort(int Elements[], int N)
{
    for(int P = 1; P < N; ++P)
    {
        // 从A[1]开始进行插入

        // 选中将要插入的数据
        int Tmp = Elements[P];

        int i;
        for(i = P; i > 0 && Elements[i-1] > Tmp; --i)
        {
            // 与已经排序完成的序列做对比，若数据小于序列，则序列右移
            Elements[i] = Elements[i-1];
        }
        // 完成插入操作（新牌落位）
        Elements[i] = Tmp;
    }
    return;
}

// 简单选择排序


/**
 * @brief 其他排序部分
 * 
 */

// 希尔排序(插入排序的改进)，不具有稳定性

// Sedgewick递增序列
// S_i = 4^i-3x2^i+1
int SedgewickSeq(int i)
{
    return (1 << 2*i) + 3 * (1 << i) + 1;
}

void Shell_Sort_Sedgewick(int Elements[], int N)
{
    
}

void Shell_Sort_Hibbard(int Elements[], int N)
{

}

// 堆排序(改进的选择排序)

// 快速排序(和冒泡排序一样属于交换排序)

// 归并排序

/**
 * @brief 主程序部分
 * 
 * @return int 
 */

#include <stdio.h>

int main()
{
    // 读入输入
    int N;
    scanf("%d", &N);

    int* array = malloc(sizeof(*array)*N);
    for(int i = 0; i < N; ++i)
    {
        scanf("%d", array + i);
    }

    // 在这里插入等待测试的函数
    // Bubble_Sort(array, N); // 冒泡排序，由于交换的时间代价，无法通过测试 
    // Insertion_Sort(array, N); // 效率相对冒泡排序更高，因为不涉及交换操作
    // 


    // 输出结果
    for(int i = 0; i < N - 1; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("%d", array[N-1]);

    return 0;
}