// 比较归并排序与插入排序

#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool cmp(int a, int b)
{
    return a < b;
}

void Insertion_Sort_ns(int* sor, int nS, int N)
{
    if(nS >= N)
        return;
    int Tmp = sor[nS];
    int P;
    for(P = nS; P > 0 && cmp(Tmp, sor[P - 1]); --P)
        sor[P] = sor[P - 1];
    sor[P] = Tmp;
}

int isInsertionSort(int* ori, int* sor, int& N)
{
    int cnt = 0;
    while(sor[cnt] <= sor[cnt + 1] && cnt < N - 1)
        ++cnt;
    int ret = 1;
    for(int i = ++cnt; i < N; ++i)
        if(ori[i] != sor[i])
            ret = 0;
    N = cnt;
    return ret;
}

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void Heap_Sort_ns(int* sor, int N)
{
    int i;
    for(i = N - 1; i >= 0; --i)
    {
        if(sor[i] < sor[0])
        {
            swap(sor + i, sor);
            break;
        }
    }
    int lastElement = i;
    int greaterNode;
    int nowPos = 0;
    while(nowPos * 2 + 1 < lastElement)
    {
        if(sor[nowPos] < sor[nowPos*2 + 1] || sor[nowPos] < sor[nowPos*2 + 2])
        {
            if(sor[nowPos*2 + 1] < sor[nowPos*2 + 2] && nowPos*2 + 2 < lastElement)
            {
                swap(sor + nowPos*2 + 2, sor + nowPos);
                nowPos = nowPos*2 + 2;
            }
            else
            {
                swap(sor + nowPos*2 + 1, sor + nowPos);
                nowPos = nowPos * 2 + 1;
            }
        }
    }
}

int main()
{
    // INIT
    int N;

    int* original;
    int* sorted;

    scanf(" %d", &N);
    original = (int*)malloc(sizeof(*original) * N);
    sorted = (int*)malloc(sizeof(*sorted) * N);

    // INPUT
    for(int i = 0; i < N; ++i)
        scanf(" %d", original + i);
    for(int i = 0; i < N; ++i)
        scanf(" %d", sorted + i);
    
    int insPro = N;
    if(isInsertionSort(original, sorted, insPro))
    {
        Insertion_Sort_ns(sorted, insPro, N);
        printf("Insertion Sort\n");
    }
    else
    {
        Heap_Sort_ns(sorted, N);
        printf("Heap Sort\n");
    }

    for(int i = 0; i < N; ++i)
    {
        if(i)
            printf(" ");
        printf("%d", sorted[i]);
    }

    free(original);
    free(sorted);

    return 0;
}