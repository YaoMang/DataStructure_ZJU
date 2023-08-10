// 图的建立以及遍历

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

// 链表结点
struct Node{
    int Data;
    struct Node* Next;
};

typedef struct Node* List;

// 图，使用邻接表实现
struct Graph{
    int Size;
    List Element;    
};

typedef struct Graph* Graph;

// 存储点，用于处理距离
struct Point2D{
    int x;
    int y;
};

typedef struct Point2D Point2D;

// 创建图
Graph CreateGraph(int Size)
{
    Graph ret = (Graph)malloc(sizeof(*ret));
    ret->Size = Size;
    ret->Element = calloc(Size, sizeof(*ret->Element));

    return ret;
}

// 连接两顶点
Graph ConnectVertex(Graph G, int Vertex_1, int Vertex_2)
{
    List it = G->Element + Vertex_1;
    while(it->Next){
        it = it->Next;
    }
    it->Next = malloc(sizeof(*it));
    it->Next->Data = Vertex_2;
    it->Next->Next = NULL;

    it = G->Element + Vertex_2;
    while(it->Next){
        it = it->Next;
    }
    it->Next = malloc(sizeof(*it));
    it->Next->Data = Vertex_1;
    it->Next->Next = NULL;

    return G;
}

// 计算两点距离
double calDistance(Point2D* a, Point2D* b)
{
    int Delta_X = a->x - b->x;
    int Delta_Y = a->y - b->y;

    return sqrt(Delta_X * Delta_X + Delta_Y * Delta_Y);
}

// 计算到边界的距离
int calDistanceBoundary(Point2D* a)
{
    int N = abs(a->y - 50);
    int S = abs(a->y + 50);
    int E = abs(a->x - 50);
    int W = abs(a->x + 50);

    int LR = W < E ? W : E;
    int TB = N < S ? N : S;
    int Total = LR < TB ? LR : TB;

    return Total;
}

// 深度优先遍历，递归实现
void DFS(Graph G, int Vertex, int* Visited)
{
    // 标记访问
    Visited[Vertex] = 1;

    List it;

    for(it = (G->Element + Vertex)->Next; it; it = it->Next){
        if(!Visited[it->Data]){
            DFS(G, it->Data, Visited);
        }
    }
}

// 图中两点是否相连
int isConnected(Graph G, int Vertex_1, int Vertex_2)
{
    // 使用特定变量请记住初始化
    int* Visited = calloc(G->Size, sizeof(*Visited));
    DFS(G, Vertex_1, Visited);

    if(Visited[Vertex_1] && Visited[Vertex_2]){
        return 1;
    }
    else{
        return 0;
    }
}

int main()
{
    // 读入内容
    int N = 0; // 鳄鱼数量
    int D = 0; // 跳跃距离
    scanf("%d %d", &N, &D);

    // 读入鳄鱼坐标
    Point2D* array = malloc(sizeof(*array)*N);
    for(int i = 0; i < N; ++i){
        scanf("%d %d", &array[i].x, &array[i].y);
    }

    // 定义最后两个为岛顶点和边界顶点
    Graph G = CreateGraph(N + 2);

    // 根据距离关系连接顶点
    for(int i = 0; i < N; ++i){
        for(int j = i + 1; j < N; ++j){
            if(calDistance(array + i, array + j) <= D){
                ConnectVertex(G, i, j);
            }
        }
    }

    Point2D BondPoint;
    BondPoint.x = 0; BondPoint.y = 0;
    for(int i = 0; i < N; ++i){
        if(calDistanceBoundary(array + i) <= D){
            ConnectVertex(G, i, N);
        }
        if(calDistance(&BondPoint, array + i) - 15 <= D){
            ConnectVertex(G, i, N + 1);
        }
    }

    free(array);

    if(isConnected(G, N, N + 1)){
        printf("Yes");
    }
    else{
        printf("No");
    }
}