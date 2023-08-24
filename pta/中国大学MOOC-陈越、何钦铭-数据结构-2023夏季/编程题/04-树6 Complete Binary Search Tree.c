// 完全二叉搜索树

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const int* a, const int* b)
{
    return *a - *b;
}

// 得到左子树的规模，计算方法如下
// N = 2^H - 1 + X
// X = min(X, 2^(H-1))
// L = 2^(H-1) - 1 + X
int GetLSubTreeSize(int n)
{
    int H = (int)log2(n + 1);
    int powER = pow(2, H - 1);
    int X = n + 1 - powER * 2;
    X = X < powER ? X : powER;
    return powER - 1 + X;
}

// 实际上是从一个数组到另一个数组的搬运过程
void solve(int base[], int result[], int Left, int Right, int TRoot)
{
    // 得到目前树大小
    int n = Right - Left + 1;
    // 确定树不为空
    if(n == 0){
        return;
    }
    // 得到左子树大小
    int LSize = GetLSubTreeSize(n);
    // 填充根节点
    result[TRoot] = base[Left + LSize];
    
    // 递归解决左右子树填充问题
    solve(base, result, Left, Left + LSize - 1, TRoot * 2 + 1);
    solve(base, result, Left + LSize + 1, Right, TRoot * 2 + 2);
}

int main()
{
    // 数据输入
    int n_Num = 0;
    scanf("%d", &n_Num);
    int* array = malloc(sizeof(*array)*n_Num);
    int* target = malloc(sizeof(*target)*n_Num);
    for(int i = 0; i < n_Num; ++i){
        scanf("%d", array + i);
    }

    // 排序
    qsort(array, n_Num, sizeof(*array), compare);

    // 得到完全二叉搜索树
    solve(array, target, 0, n_Num - 1, 0);

    free(array);
    // 层序遍历输出
    for(int i = 0; i < n_Num - 1; ++i){
        printf("%d ", target[i]);
    }
    printf("%d", target[n_Num - 1]);

    return 0;
}