#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

/* 你的代码将被嵌在这里 */
Position BinarySearch(List L, ElementType X)
{
    Position left = 1;
    Position right = L->Last + 1;
    Position mid = (left + right) / 2;

    while (L->Data[mid] != X)
    {
        if(left == right){
            return NotFound;
        }

        if(L->Data[mid] < X){
            left = mid + 1;
            mid = (left + right) / 2;
        }
        else{
            right = mid - 1;
            mid = (left + right) / 2;
        }
    }

    return mid;
}