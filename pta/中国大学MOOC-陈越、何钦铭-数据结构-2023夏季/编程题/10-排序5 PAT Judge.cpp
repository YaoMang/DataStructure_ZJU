// 表排序

#include <vector>
#include <iostream>
#include <cstdio>
#include <list>
#include <algorithm>

using namespace std;

vector<int> fullPoint;

struct StudentNode
{
    int id;
    int tP; // totalPoint
    int pS; // perfectSubmit
    vector<int> points;

    void totalPoint()
    {
        int ret_totalPoint = 0;
        for(auto i : this->points)
        {
            if(i < 0)
                i = 0;
            ret_totalPoint += i;
        }
        this->tP = ret_totalPoint;
    }

    void perfectSubmit()
    {
        int cnt = 0;
        for(int i = 0; i < this->points.size(); ++i)
            if(fullPoint[i] == this->points[i])
                ++cnt;
        this->pS = cnt;
    }
};

bool compareFunc(StudentNode* S1, StudentNode* S2)
{
    if(S1->tP == S2->tP)
    {
        if(S1->pS == S2->pS)
        {
            return S1->id < S2->id;
        }
        return S1->pS > S2->pS;
    }
    return S1->tP > S2->tP;
}

struct StudentList
{
    vector<StudentNode*> ptr;
    vector<StudentNode> SL;

    void InsertRecord(int id, int pN, int pP)
    {
        int flag_found = 0;
        if(this->SL[id].id == id)
        {
            // found
            flag_found = 1;
            if(pP > this->SL[id].points[pN])
                this->SL[id].points[pN] = pP;
            return;
        }
        if(!flag_found)
        {
            StudentNode NewNode;
            NewNode.id = id;
            NewNode.points.resize(fullPoint.size());
            for(auto &i : NewNode.points)
                i = -2;
            NewNode.points[pN] = pP;
            SL[id] = NewNode;
        }
    }
};

int main()
{
    // INIT
    int N,K,M;
    scanf(" %d %d %d", &N, &K, &M); 

    fullPoint.resize(K);
    for(int i = 0; i < K; ++i)
    {
        cin >> fullPoint[i];
    }

    StudentList S;
    S.SL.resize(N + 1);
    
    // READ DATA
    string str_id;
    int id,pN,pP;
    for(int i = 0; i < M; ++i)
    {
        cin >> str_id >> pN >> pP;
        id = stoi(str_id);

        --pN;
        S.InsertRecord(id, pN, pP);
    }

    for(auto& N : S.SL)
    {
        N.perfectSubmit();
        N.totalPoint();
    }
    
    // SORT
    S.ptr.resize(N);
    for(int i  = 0; i < S.ptr.size(); ++i)
        S.ptr[i] = &S.SL[i + 1];
    sort(S.ptr.begin(), S.ptr.end(), compareFunc);

    int lastTN = -1;
    int cnt = 1;
    int lag = 0;
    for(auto& N : S.ptr)
    {
        int flag_all0 = 1;
        for(auto& i : N->points)
            if(i >= 0)
            {
                flag_all0 = 0;
                break;
            }
        if(flag_all0)
        {
            continue;
        }

        if(lastTN == N->tP)
        {
            ++lag;
        }
        else
        {
            lag = 0;
        }
        lastTN = N->tP;

        printf("%d %05d %d", cnt - lag, N->id, N->tP);
        for(auto i : N->points)
        {
            if(i < -1)
                printf(" -");
            else
            {
                if(i == -1)
                    ++i;
                printf(" %d", i);
            }
        }
        printf("\n");
        ++cnt;
    }
}

