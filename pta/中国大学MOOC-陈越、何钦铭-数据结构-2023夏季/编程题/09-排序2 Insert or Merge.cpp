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

void Merge_Sort_sec(int* sor, int Sec, int N)
{
    int* array = (int*)malloc(sizeof(*array) * Sec * 2);
    int pos;
    for(pos = 0; pos < N; pos += 2 * Sec)
    {
        int cnt_a = pos;
        int cnt_b = pos + Sec;
        int cnt_c = 0;

        while (
            cnt_a - pos < Sec && 
            cnt_b - pos - Sec < Sec && 
            cnt_a < N && 
            cnt_b < N
            )
        {
            if(cmp(sor[cnt_a], sor[cnt_b]))
            {
                array[cnt_c] = sor[cnt_a];
                ++cnt_a;            
            }
            else
            {
                array[cnt_c] = sor[cnt_b];
                ++cnt_b;
            }
            ++cnt_c;
        }
        
        while (cnt_a - pos < Sec && cnt_a < N)
        {
            array[cnt_c] = sor[cnt_a];
            ++cnt_a;
            ++cnt_c;
        }
        while (cnt_b - pos - Sec < Sec && cnt_b < N)
        {
            array[cnt_c] = sor[cnt_b];
            ++cnt_b;
            ++cnt_c;
        }
        
        // Writeback
        for(int i = 0; i < cnt_c; ++i)
            sor[pos + i] = array[i];
    }
    free(array);
}

int get_Merge_Sort_Sec(int* sor, int N)
{
    int MerNum;
    for(MerNum = 2; MerNum <= N; MerNum*=2)
    {
        for(int now = MerNum; now < N; now += 2 * MerNum)
        {
            if(!cmp(sor[now - 1], sor[now]))
                return MerNum;
        }
    }
}

void Merge_Sort_ns(int* sor, int N)
{
    int Sec = get_Merge_Sort_Sec(sor, N);
    Merge_Sort_sec(sor, Sec, N);
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
        Merge_Sort_ns(sorted, N);
        printf("Merge Sort\n");
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