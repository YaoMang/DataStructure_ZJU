// 需要检测是否存在回路

#include <cstdio>
#include <list>
#include <queue>

using namespace std;

struct WEdge
{
    using Vertex = int;

    Vertex V; 
    int weight;
};

struct LGraph
{
    int Nv;
    list<WEdge> *G;
};

void buildGraph(LGraph &G, int M)
{
    int src, dst, time;
    WEdge TEMP;
    for(int i = 0; i < M; ++i)
    {
        scanf(" %d %d %d", &src, &dst, &time);
        
        TEMP.V = dst;
        TEMP.weight = time;

        G.G[src].push_back(TEMP);
    }
}

int getTotalTime(LGraph &G)
{
    using Vertex = int;
    // use dist[] as tag array of if visited
    int* dist = new int[G.Nv];
    for(int i = 0; i < G.Nv; ++i)
        dist[i] = 0;
    
    vector<int> Indegree(G.Nv, 0);
    for(int i = 0; i < G.Nv; ++i)
    {
        for(auto& Node : G.G[i])
        {
            ++Indegree[Node.V];
        }
    }

    queue<int> Q;

    // 挑选出起始元素
    for(int i = 0; i < G.Nv; ++i)
        if(Indegree[i] == 0)
            Q.push(i);
    
    // 开始BST
    int cnt = 0;
    while(!Q.empty())
    {
        // 队列弹出元素
        Vertex V = Q.front();
        Q.pop();
        ++cnt;

        // 将弹出元素所有邻接点入队
        for(auto& Node : G.G[V])
        {
            if(--Indegree[Node.V] == 0)
                Q.push(Node.V);
            if(dist[Node.V] < dist[V] + Node.weight)
                dist[Node.V] = dist[V] + Node.weight;
        }
    }

    if(cnt == G.Nv)
    {
        int ret_max = 0;
        for(int i = 0; i < G.Nv; ++i)
            if(ret_max < dist[i])
                ret_max = dist[i];
        
        return ret_max;
    }
    else
        return -1;
}

int main()
{
    // INIT
    int N,M;
    scanf(" %d %d", &N, &M);

    LGraph G;
    G.Nv = N;
    G.G = new list<WEdge>[N]();

    for(int i = 0; i < G.Nv; ++i)
    {
        list<WEdge> INIT;
        G.G[i] = INIT;
    }

    // READ&BUILD GRAPH
    buildGraph(G, M);

    // GET TOTAL TIME
    int total_time = getTotalTime(G);

    // OUTPUT
    if(total_time == -1)
    {
        printf("%s", "Impossible\n");
    }
    else{
        printf("%d\n", total_time);
    }

    return 0;
}