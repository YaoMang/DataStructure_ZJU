// 需要检测是否存在回路

#include <cstdio>
#include <list>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Edge
{
    int order; // input order
    int W; // W for weight
    int V; // V for Vertex
    bool isCrit;
};

struct LGraph
{
    using Vertex = int;
    int nV;
    vector<int> Earlist;
    vector<list<Edge>> G;

    LGraph(int N)
    {
        this->Earlist.resize(N);
        this->G.resize(N);
        this->nV = N;
    }

    void insertVertex(int N1, int N2, int weight, int order)
    {
        Edge E;
        E.order = order;
        E.W = weight;
        E.V = N2;

        this->G[N1].push_back(E);
    }

    bool updateE()
    {
        vector<int> inDegree(this->nV);
        for(auto& E : this->G)
            for(auto& N : E)
                ++inDegree[N.V];
        // INIT START NODE
        queue<int> Q;
        for(int i = 0; i < inDegree.size(); ++i)
            if(inDegree[i] == 0)
            {
                Earlist[i] = 0;
                Q.push(i);
            }
        // GET EARLIEST
        while(!Q.empty())
        {
            int V = Q.front();
            Q.pop();

            for(auto& N : this->G[V])
            {
                if(Earlist[N.V] < Earlist[V] + N.W)
                    Earlist[N.V] = Earlist[V] + N.W;
                --inDegree[N.V];
                if(inDegree[N.V] == 0)
                    Q.push(N.V);
                if(inDegree[N.V] < 0)
                    return false;
            }
        }
    }

    void updateCritEdge()
    {
        vector<int> inDegree(this->nV);
        for(auto& E : this->G)
            for(auto& N : E)
                ++inDegree[N.V];
        // INIT START NODE
        queue<int> Q;
        for(int i = 0; i < inDegree.size(); ++i)
            if(inDegree[i] == 0)
            {
                Earlist[i] = 0;
                Q.push(i);
            }
        // GET EARLIEST
        while(!Q.empty())
        {
            int V = Q.front();
            Q.pop();

            for(auto& N : this->G[V])
            {
                if(Earlist[V] + N.W == Earlist[N.V])
                {
                    Q.push(N.V);
                    N.isCrit = true;
                }
            }
        }
    }
};

bool cmp(int& a, int& b)
{
    return a < b;
}

bool cmpEdge(Edge& a, Edge& b)
{
    return a.order > b.order;
}

void outputCritPath(LGraph& G)
{
    
    vector<int> inDegree(G.nV);
    for(auto& E : G.G)
        for(auto& N : E)
            ++inDegree[N.V];
    // INIT START NODE
    deque<int> Q;
    for(int i = 0; i < inDegree.size(); ++i)
        if(inDegree[i] == 0)
        {
            G.Earlist[i] = 0;
            Q.push_back(i);
        }
    // GET EARLIEST
    sort(Q.begin(), Q.end(), cmp);
    vector<int> path;
    deque<Edge&> path_single;
    while(!Q.empty())
    {
        path_single.clear();
        int V = Q.front();
        Q.pop_front();
        path.push_back(V);
        for(auto& N : G.G[V])
        {
            if(N.isCrit)
                path_single.push_back(N);
        }
        sort(path_single.begin(), path_single.end(), cmpEdge);
        while(!path_single.empty()){
            Q.push_back(path_single.front().V);
            path_single.pop_front();
        }
    }

    int lenth = 0;
    for(auto& i : G.Earlist)
        if (i > lenth)
            lenth = i;
    
    printf("%d\n", lenth);
    for(int i = 0; i < path.size() - 1; ++i)
        printf("%d->%d", path[i], path[i + 1]);

}

int main()
{
    // INIT
    int N,M;
    scanf(" %d %d", &N, &M);

    // READ DATA
        // build graph
    int V1,V2,W;
    LGraph G(N);

    for(int i = 0; i < M; ++i)
    {
        scanf(" %d %d %d", &V1, &V2, &W);
        G.insertVertex(V1, V2, W, i);
    }
    
    // GET CRITICAL PATH
        // cacl E
        // outPut
    if(G.updateE())
    {
        G.updateCritEdge();
        outputCritPath(G);
    }
    else
    {
        printf("0\n");
    }

    return 0;
}