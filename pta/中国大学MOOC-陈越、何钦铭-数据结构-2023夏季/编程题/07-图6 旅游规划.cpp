#include <vector>
#include <cstdio>

using namespace std;

const int inf = 100000;

struct GraphNode
{
    int dis;
    int fee;
};

using Vertex = int;

// 返回未被收录顶点中dist最小者
Vertex FindMin(GraphNode** G, bool* collected, vector<int> &dist, int size)
{
    int mindist = inf;
    int ret = -1;
    for(int i = 0; i < size; ++i)
    {
        // 选择V的邻接点
        if(collected[i] == false && mindist > dist[i])
        { // 没有收录并且距离大于目前距离
            mindist = dist[i];
            ret = i;
        }
    }
    return ret;
}

void Dijkstra(GraphNode** G, Vertex S, vector<int> &path, int size)
{
    // 其余部分为原始Dijkstra算法
    bool collected[size];
    for(auto &c : collected)
    {
        c = false;
    }
    collected[S] = true;

    vector<int> dist(size, inf);
    vector<int> cost(size, inf);

    for(int i = 0; i < size; ++i)
    {
        dist[i] = G[S][i].dis;
        if(dist[i] < inf)
        { // 这里需要同时完成第一步路径的处理
            path[i] = S;
        }
    }
    dist[S] = 0;
    cost[S] = 0;
    path[S] = -1;
    
    while (1)
    {
        // 从所有未访问的顶点中选取距离最小的顶点
        Vertex V = FindMin(G, collected, dist, size);
        if( V == -1 )
            break;
        collected[V] = true;

        for(int i = 0; i < size; ++i)
        {
            // V的每个未收录邻接点
            if(G[V][i].dis < inf && collected[i] == false)
            {
                if(dist[V] + G[V][i].dis < dist[i])
                {
                    path[i] = V;
                    dist[i] = dist[V] + G[V][i].dis;
                    cost[i] = cost[V] + G[V][i].fee;
                }
                else if(    (dist[V] + G[V][i].dis == dist[i]) && 
                            (cost[V] + G[V][i].fee < cost[i]))
                { // 改进部分，距离相等，此时考虑更低的费用
                    cost[i] = cost[V] + G[V][i].fee;
                    path[i] = V;
                }
            }
        }
    }
}

int main()
{
    // 对应初始输入变量
    int N,M,S,D;

    scanf(" %d %d %d %d", &N, &M, &S, &D);

    // 路径存储
    vector<int> path(N, -1);

    // 邻接矩阵
    GraphNode** G = new GraphNode*[N];
    for(int i = 0; i < N; ++i)
    {
        G[i] = new  GraphNode[N];
    }

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            G[i][j].dis = inf;
            G[i][j].fee = inf;
        }
    }

    int src,dst,dis,fee;
    for(int i = 0; i < M; ++i)
    {
        scanf(" %d %d %d %d", &src, &dst, &dis, &fee);
        G[src][dst].dis = dis;
        G[src][dst].fee = fee;
        G[dst][src].dis = dis;
        G[dst][src].fee = fee;
    }

    Dijkstra( G, S, path, N);

    // OUTPUT
    int it = D;
    int cost = 0;
    int dist = 0;
    while(path[it] != -1)
    {
        cost += G[it][path[it]].fee;
        dist += G[it][path[it]].dis;
        it = path[it];
    }

    printf("%d %d", dist, cost);

    return 0;
}