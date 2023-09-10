// 分类与查找环的个数

#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

int getSwapNum(vector<int> &InputSeq)
{
    vector<short> isVisited(InputSeq.size(), 0);

    int flag_0;
    int flag_cnt;
    int ret_TotalSwap = 0;


    for(int i = 0; i < isVisited.size(); ++i)
    {
        flag_0 = 0;
        flag_cnt = 0;

        if(isVisited[i])
        {
            continue;
        }
        else{
            int j = i;
            while (!isVisited[j])
            {
                isVisited[j] = 1;
                if(InputSeq[j] == 0)
                {
                    flag_0 = 1;
                    ++flag_cnt;
                }
                else
                    ++flag_cnt;
                
                j = InputSeq[j];
            }
        }
        
        if(flag_0)
            ret_TotalSwap += flag_cnt - 1;
        else{
            if(flag_cnt > 1)
                ret_TotalSwap += flag_cnt + 1;
        }
    }
    
    return ret_TotalSwap;
}

int main()
{
    // INIT
    int N;
    scanf(" %d", &N);

    vector<int> InputSeq;

    InputSeq.resize(N);

    // INPUT
    for(auto& i : InputSeq)
        cin >> i;
    
    // get swap num 
    int swapNum = getSwapNum(InputSeq);

    // OUTPUT
    printf("%d", swapNum);
    return 0;
}