// 这个问题甚至不需要复结构，数组即可实现桶排序问题

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 初始化变量
    int* array = calloc(51, sizeof(*array));
    int n_Num = 0;

    // 读入数据
    scanf(" %d", &n_Num);
    int temp;
    for(int i = 0; i < n_Num; ++i)
    {
        scanf(" %d", &temp);
        ++array[temp];
    }

    // 输出结果
    for(int i = 0; i < 51; ++i)
    {
        if(array[i])
        {
            printf("%d:%d\n", i, array[i]);
        }
    }

    return 0;
}

