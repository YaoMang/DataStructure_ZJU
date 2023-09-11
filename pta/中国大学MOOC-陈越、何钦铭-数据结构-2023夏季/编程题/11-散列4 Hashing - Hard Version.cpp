#include <cstdio>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

struct LGraph
{
    using Vertex = int;

    Vertex Nv;
    vector<list<int>> G;
};

int getPos(int i, vector<int>& inSeq)
{
    for(int n = 0; n < inSeq.size(); ++n)
        if(i == inSeq[n])
            return n;
    return -1;
}

void buildGraph(LGraph& LG, vector<int>& inSeq)
{
    int pos;
    int realPos;

    for(auto i : inSeq)
    {
        if(i < 0)
            continue;
        realPos = getPos(i, inSeq);
        pos = i%inSeq.size();
        while(inSeq[pos] != i)
        { // 发生冲突
            LG.G[pos].push_back(realPos);
            ++pos;
            pos = pos%inSeq.size();
        }
    }
}

void Indegree_0(LGraph& LG, vector<int>& mask, vector<int>& res)
{
    // Assume that res is empty
    res.resize(0);
    vector<int> Indegree(LG.Nv, 0);
    for(auto& L : LG.G)
        for(auto& N : L)
            Indegree[N] = 1;
    for(int i = 0; i < Indegree.size(); ++i)
        if(Indegree[i] == 0 && mask [i] == 0)
            res.push_back(i);
}

int MinimiumNode(vector<int>& inSeq, vector<int>& outputTable)
{
    // 题目没有给出数据输入最大值，会导致出错
    int miniNum = 1000000;
    int ret_pos = -1;
    for(auto& i : outputTable)
    {
        if(inSeq[i] < miniNum)
        {
            miniNum = inSeq[i];
            ret_pos = i;
        }
    }
    return ret_pos;
}

void output(vector<int>& inSeq)
{
    LGraph G;
    G.Nv = inSeq.size();
    G.G.resize(G.Nv);

    // BUILD GRAPH
    buildGraph(G, inSeq);

    // OUTPUT
    int ElementNum = 0;
    vector<int> mask(G.Nv, 0);
    for(int i = 0; i < inSeq.size(); ++i)
        if(inSeq[i] < 0)
        {
            mask[i] = 1;
            ++ElementNum;
        }
    ElementNum = inSeq.size() - ElementNum;
    
    // LOOP
        // FIND ALL NODES WITH 0 INDEGREE
        // OUTPUT SMALLEST NODE
        // DELETE NODE
    int optVertx;
    int outputFlag = 0;
    for(int i = 0; i < ElementNum; ++i)
    {
        vector<int> ind_0;
        Indegree_0(G, mask, ind_0);
        optVertx = MinimiumNode(inSeq, ind_0);
        if(outputFlag)
            printf(" ");
        printf("%d", inSeq[optVertx]);
        outputFlag = 1;
        mask[optVertx] = 1;
        G.G[optVertx].clear();
    }
}

int main()
{
    // INIT
    int N;
    cin >> N;
    vector<int> Seq;
    Seq.resize(N, 0);

    // INPUT
    for(auto& i : Seq)
        cin >> i;

    // OUTPUT
    output(Seq);

    return 0;
}