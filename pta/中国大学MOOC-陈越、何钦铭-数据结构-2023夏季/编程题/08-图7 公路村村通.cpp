// 最小生成树 Prim算法实现

#include <cstdio>
#include <list>

using namespace std;

struct MGraph
{
    int Nv;
    int** G;  
};

struct WeightedLGN
{
    using Vertex = int;
    Vertex V;
    int Weight;
};

struct LGraph
{
    int Nv;
    list<WeightedLGN> *G;
};

const int inf = 10000;

int findMinDist(MGraph &MG, int* dist)
{
    using Vertex = int;

    Vertex ret_MinV = -1;
    int mindest = inf;

    for(int V = 0; V < MG.Nv; ++V)
    {
        if(dist[V] != 0 && mindest > dist[V])
        {
            mindest = dist[V];
            ret_MinV = V;
        }
    }

    return ret_MinV;
}

int Prim(MGraph &MG, LGraph &MST)
{
    using Vertex = int;

    int* dist = new int[MG.Nv];
    Vertex* parent = new int[MG.Nv];
    for(int i = 0; i < MG.Nv; ++i)
        parent[i] = 0;

    int Vcnt = 0;
    Vertex W = 0, V;

    for(int i = 0; i < MG.Nv; ++i)
        dist[i] = MG.G[0][i];

    dist[0] = 0;
    parent[0] = -1;
    ++Vcnt;

    while(1)
    {
        V = findMinDist(MG, dist);
        if(V == -1)
            break;
        
        WeightedLGN Node;
        Node.V = V;
        Node.Weight = dist[V];
        MST.G[parent[V]].push_back(Node);
        dist[V] = 0;
        ++Vcnt;

        for(W = 0; W < MG.Nv; ++W)
        { // 对于V的每个邻接点W
            if(dist[W] != 0 && MG.G[V][W] < inf)
            {
                if(MG.G[V][W] < dist[W])
                {
                    dist[W] = MG.G[V][W];
                    parent[W] = V;
                }
            }  
        }     
    }

    delete dist;
    delete parent;

    return Vcnt;
}

int totalWeight(LGraph &MST)
{
    int ret_Weight = 0;
    for(int i = 0; i < MST.Nv; ++i)
    {
        for(auto &N : MST.G[i])
        {
            ret_Weight += N.Weight;
        }
    }

    return ret_Weight;
}

int main()
{
    // INIT
    MGraph MG;
    LGraph LG;
    int N,M;
    
    scanf(" %d %d", &N, &M);
    
    MG.Nv = N;
    MG.G = new int*[N];

    LG.Nv = N;
    LG.G = new list<WeightedLGN>[N]();

    for(int i = 0; i < MG.Nv; ++i)
    {
        MG.G[i] = new int[MG.Nv];
        for(int j = 0; j < MG.Nv; ++j)
        {
            MG.G[i][j] = inf;
        }
    }

    for(int i = 0; i < LG.Nv; ++i)
    {
        list<WeightedLGN> INIT;
        LG.G[i] = INIT;
    }

    // READ DATA
    int src,dst,dis;
    for(int i = 0; i < M; ++i)
    {
        scanf(" %d %d %d", &src, &dst, &dis);
        // 对齐格式
        --src; --dst;

        MG.G[src][dst] = dis;
        MG.G[dst][src] = dis;
    }

    // Prim Algo
    int N_NODE = Prim(MG, LG);

    // OUTPUT
    if(N_NODE < N)
    {
        N_NODE = -1;
    }
    else{
        N_NODE = totalWeight(LG);
    }

    printf("%d\n", N_NODE);

    return 0;
}