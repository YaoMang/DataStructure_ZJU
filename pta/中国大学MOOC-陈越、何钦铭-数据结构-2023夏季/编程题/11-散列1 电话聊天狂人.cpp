#include <cstdio>
#include <list>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int Num;
    int Freq;
};

struct Hashtable
{
    int Size;
    vector<list<ListNode>> Array;
};

void Insert(Hashtable &H, string &Key)
{
    string str_s1 = Key.substr(0, 6);
    string str_s2 = Key.substr(6, 11);

    int tableNum, elementNum; 
    tableNum = stoi(str_s2);
    elementNum = stoi(str_s1);

    int foundTag = 0;
    auto& List = H.Array[tableNum];

    if(!List.empty())
    {
        for(auto& N : List)
        {
            if(elementNum == N.Num)
            {
                foundTag = 1;
                ++(N.Freq);
                break;
            }
        }
    }

    if(!foundTag)
    {
        ListNode N;
        N.Freq = 1;
        N.Num = elementNum;

        H.Array[tableNum].push_back(N);
    }
    
    return;
}

void Output(Hashtable &H)
{
    int maxNum = 0;
    int s1_num, s2_num;
    int peoNum = 0;

    for(int i = 0; i < H.Array.size(); ++i)
    {
        auto& L = H.Array[i];
        for(auto j = L.begin(); j != L.end(); ++j)
        {
            if(maxNum < j->Freq){
                maxNum = j->Freq;
                s2_num = i;
                s1_num = j->Num;
                peoNum = 1;
            }
            else if(maxNum == j->Freq)
            {
                ++peoNum;
                if(s1_num > j->Num)
                {
                    s1_num = j->Num;
                    s2_num = i;
                }
            }
        }
    }

    printf("%06d%05d ", s1_num, s2_num);
    printf("%d", maxNum);
    if(peoNum > 1)
    {
        printf(" %d", peoNum);
    }
    printf("\n");
}

int main()
{
    // INIT
    int N;

    scanf("%d", &N);

    Hashtable H;
    H.Size = 100000;
    H.Array.resize(H.Size);

    // INPUT
    string Key;
    for(int i = 0; i < N; ++i)
    {
        cin >> Key; Insert(H, Key);
        cin >> Key; Insert(H, Key);
    }

    // OUTPUT
    Output(H);

    return 0;
}