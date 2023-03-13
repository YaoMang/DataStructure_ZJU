#include <stdio.h>

struct maxSubsequenceSumReturnStruct
{
    int sum;
    int lNum;
    int rNum;
};

typedef struct maxSubsequenceSumReturnStruct MSSRS;

MSSRS maxSubsequenceSum(const int n, int* sequence);

int main()
{
    int n = 0;
    scanf("%d", &n);

    int sequence[n];

    for(int i = 0; i < n; ++i){
        scanf("%d", sequence + i);
    }

    MSSRS dataPrint = maxSubsequenceSum(n, sequence);

    printf("%d %d %d", dataPrint.sum, dataPrint.lNum, dataPrint.rNum);

    return 0;
}

MSSRS maxSubsequenceSum(const int n, int* sequence)
{
    MSSRS ret;
    int lNum = 0;
    int templNum = *(sequence);
    int rNum = 0;
    int sum = 0;
    int tempSum = 0;
    int isNegative = 1;

    for(int i = 0; i < n; ++i){
        tempSum += *(sequence + i);

        if(isNegative){
            if(*(sequence+i) >= 0){
                isNegative = 0;
            }
        }

        if(tempSum > sum){
            sum = tempSum;
            rNum = *(sequence + i);
            lNum = templNum;
        }

        if(tempSum < 0){
            tempSum = 0;
            templNum = *(sequence + i + 1);
        }
    }

    if(isNegative){
        ret.sum = 0;
        ret.lNum = *sequence;
        ret.rNum = *(sequence + n - 1);       
    }
    else{
        ret.sum = sum;
        ret.lNum = lNum;
        ret.rNum = rNum;
    }

    return ret;
}