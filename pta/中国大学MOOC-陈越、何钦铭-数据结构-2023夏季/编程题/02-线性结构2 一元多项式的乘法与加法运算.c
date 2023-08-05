#include <stdio.h>
#include <stdlib.h>

void fix(int** x)
{
    int* it = *x;
    for(int i = 0; i < *it; ++i){
        while(*(it + 2*i + 1) == 0){
            for(int n = i; n < *it; ++n){
                *(it + 2 * n + 1) = *(it + 2 * n + 3);
                *(it + 2 * n + 2) = *(it + 2 * n + 4);
            }
            --*it;
        }
    }
}

int input(int** iptr)
{
    int cnt = 0;
    int* it = NULL;
    scanf("%d", &cnt);

    *iptr = malloc((cnt*2 + 1)*sizeof(int));
    it = *iptr;
    *it = cnt;
    ++it;

    for(int i = 0; i < cnt; ++i){
        scanf("%d %d", it, it + 1);
        it += 2;
    }

    return 0;
}

int print(int** iptr)
{
    if(**iptr){
        int* it = *iptr;
        int cnt = *it;
        //printf("%d ", cnt);
        ++it;
        for(int i = 0; i < cnt; ++i){
            printf("%d %d", *it, *(it + 1));
            it += 2;
            if(i < cnt - 1){
                printf(" ");
            }
        }
        printf("\n");

        return 0;
    }
    else{
        printf("0 0\n");

        return 0;
    }
}

int* sum(int** a, int** b)
{
    if(**a < 0 || **b < 0){
        return NULL;
    }

    int eleCnt = **a + **b;
    int mallocSize = eleCnt * 2 + 1;

    int* temp = malloc(mallocSize * sizeof(int));

    int* ita = *a;
    int* itb = *b;
    int* itt = temp;

    int cnta = *ita;
    int cntb = *itb;
    ita += 2;
    itb += 2;

    while(ita - *a <= cnta*2 && itb - *b <= cntb*2){
        if(*ita > *itb){
            *itt = *(ita - 1);
            ++itt;
            *itt = *ita;
            ++itt;

            ita += 2;
        }
        else if(*ita < *itb){
            *itt = *(itb - 1);
            ++itt;
            *itt = *itb;
            ++itt;

            itb += 2;
        }
        else{
            if(*(ita - 1) + *(itb - 1)){
                *itt = *(ita - 1) + *(itb - 1);
                ++itt;
                *itt = *ita;
                ++itt;
            }
            else{
                --eleCnt;
            }
            

            ita += 2;
            itb += 2;
            --eleCnt;
        }
    }

    //printf("END OF SUM\n");

    int* it_Left = NULL;
    int* it_Left_s = NULL;
    if(ita - *a <= cnta*2){
        it_Left = ita;
        it_Left_s = *a;
    }
    else if(itb - *b <= cntb*2){
        it_Left = itb;
        it_Left_s = *b;
    }

    //printf("END OF COMPARE\n");
    //printf("%x", it_Left);

    while(it_Left && it_Left - it_Left_s <= *it_Left_s * 2){
        *itt = *(it_Left -1);
        ++itt;
        *itt = *it_Left;
        ++itt;

        it_Left += 2;
    }

    //printf("END OF APPEND\n");

    mallocSize = eleCnt*2 + 1;
    int* ret = malloc(mallocSize * sizeof(int));
    *ret = eleCnt;

    int* it_ret = ret;
    ++it_ret;
    itt = temp;

    for(int i = 0; i < eleCnt; ++i){
        *it_ret = *itt;
        ++it_ret;
        ++itt;
        *it_ret = *itt;
        ++it_ret;
        ++itt;
    }

    //printf("END OF COPY\n");

    free(temp);

    fix(&ret);

    return ret;
}

int* product(int**a, int**b)
{
    int** temp_s = NULL;

    int cnta = **a;
    int cntb = **b;

    temp_s = malloc(cnta * sizeof(*temp_s));
    for(int i = 0; i < cnta; ++i){
        *(temp_s+i) = malloc(2*cntb*sizeof(**temp_s) + 1);
    }

    //printf("TEMP SPACE ALLOCATE COMPLETE\n");

    for(int j = 0; j < cnta; ++j){
        int* ita = *(a) + 2*j + 1;
        int* itb = *b;
        int* it = *(temp_s + j);
        *it = cntb;

        ++itb;
        ++it;

        for(int i = 0; i < cntb; ++i){
            *it = (*ita) * (*itb);
            ++it;
            ++itb;
            *it = *(ita + 1) + (*itb);
            ++it;
            ++itb;
        }
    }

    //printf("PRODUCT CACULATE COMPLETE\n");

    int* emptySeq = malloc(sizeof(*emptySeq));
    *emptySeq = 0;
    int* sumSeq = emptySeq;
    int* sumSeq_prev = NULL;
    
    //printf("EMPTY SUM CREATED\n");
    //print(sumSeq);

    for(int i = 0; i < cnta; ++i){
        sumSeq_prev = sumSeq;
        sumSeq = sum(&sumSeq, temp_s + i);
        free(sumSeq_prev);
    }
    
    for(int i = 0; i < cnta; ++i){
        //print(temp_s + i);
        free(*(temp_s+i));
    }
    free(temp_s);

    fix(&sumSeq);

    return sumSeq;
}

int main()
{
    int* x = NULL;
    int* y = NULL;

    input(&x);
    //print(&x);
    input(&y);
    //print(&y);

    int* pdtPtr = product(&x, &y);
    print(&pdtPtr);
    free(pdtPtr);
    int* sumptr = sum(&x, &y);
    print(&sumptr);
    free(sumptr);
    
    free(x);
    free(y);
}