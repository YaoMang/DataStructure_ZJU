#include <stdio.h>

int maxSubsequenceSum(const int n, int* sequence);

int main()
{
    int n = 0;
    scanf("%d", &n);

    int sequence[n];

    for(int i = 0; i < n; ++i){
        scanf("%d", sequence + i);
    }

    printf("%d", maxSubsequenceSum(n, sequence));

    return 0;
}

int maxSubsequenceSum(const int n, int* sequence)
{
    int ret = 0;
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
        }

        if(tempSum < 0){
            tempSum = 0;
        }
    }

    if(isNegative){
        ret = -1;       
    }
    else{
        ret = sum;
    }

    return ret;
}