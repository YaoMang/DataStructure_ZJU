// 这道题目请小心细节以及记住之前顶点的定义，耗费时间过长，写程序时还请务必小心谨慎】
// 从这一题目开始，将不会每次实现相关基础组件以节省代码量，相关组件的C版本后序会置于essential.h中

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

// 前半部分可以直接复制之前的程序
// 这里是新加入的部分
// 无权图的最短路径

// 实质上是BFS ，记录父结点
// 需要借助队列实现

// 通用队列实现
typedef List LQueue;
LQueue CreateLQueue()
{
    LQueue Q = malloc(sizeof(*Q));
    Q->Data = 0;
    Q->Next = NULL;

    return Q;
}

void EnLQueue(LQueue Q, int data)
{
    LQueue it;
    it = Q;
    while(it->Next)
    {
        it = it->Next;
    }
    it->Next = malloc(sizeof(*it));
    it = it->Next;
    it->Data = data;
    it->Next = NULL;
}

int DeLQueue(LQueue Q)
{
    int ret = 0;
    if(Q)
    {
        if(Q->Next)
        {
            ret = Q->Next->Data;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }

    // DELETE HEAD NODE
    LQueue it = Q->Next;
    Q->Next = it->Next;
    free(it);

    return ret;
}

int isLQueueEmpty(LQueue Q)
{
    if(Q->Next)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// 由于不是单纯的BFS
int findPath(Graph G, int Vertex1, int Vertex2, int* patharray)
{
    // 初始化用于访问结点的指针
    List it = NULL;

    // 初始化队列
    LQueue Q = CreateLQueue();

    // 首个顶点入队
    EnLQueue(Q, Vertex1);
    patharray[Vertex1] = Vertex1;
    int dist[Vertex2 + 1];
    for(int i = 0; i < Vertex2 + 1; ++i)
    {
        dist[i] = -1;
    }
    dist[Vertex1] = 0;

    while(!isLQueueEmpty(Q))
    {
        // 将队列弹出顶点设置为父结点
        int parent = DeLQueue(Q);
        // 父结点指针
        it = parent + G->Element;
        
        while(it->Next)
        {
            it = it->Next;
            
            // 若结点还没有被访问过，则入队
            if(dist[it->Data] == -1)
            {
                EnLQueue(Q, it->Data);
                // 写入结点父结点信息
                patharray[it->Data] = parent;
                // 设置距离
                dist[it->Data] = dist[parent] + 1;
            }
        }
    }

    free(Q);

    if(patharray[Vertex2] != -1)
    {
        return dist[Vertex2];
    }
    else
    {
        return 0;
    }
}

// 调整出发点，使其按照距离由小到大的顺序进入队列
void adjustFirstJump(Graph G, Point2D* array, int N)
{
    // 对首个结点开始调整（岛结点）
    int cnt = 0;
    List it = G->Element[N + 1].Next;
    // 统计与第一个结点连接的结点数量
    while(it)
    {
        ++cnt;
        it = it->Next;
    }

    int* FirstJump = malloc(sizeof(*FirstJump) * cnt);
    it = G->Element[N + 1].Next;
    for(int i = 0; i < cnt; ++i)
    {
        FirstJump[i] = it->Data;
        it = it->Next;
    }

    // 对结点进行排序
    // 选择排序
    Point2D BondPoint;
    BondPoint.x = 0; BondPoint.y = 0;
    for(int P = 1; P < cnt; ++P)
    {
        int Tmp = FirstJump[P];

        int i;
        for(i = P; i > 0 && (calDistance(&array[FirstJump[i - 1]], &BondPoint) > calDistance(&array[Tmp], &BondPoint)); --i)
        {
            FirstJump[i] = FirstJump[i - 1];
        }
        FirstJump[i] = Tmp;
    }

    // 填充链表结点
    it = G->Element[N + 1].Next;
    for(int i = 0; i < cnt; ++i)
    {
        it->Data = FirstJump[i];
        it = it->Next;
    }

    //it = G->Element[N].Next;
    //for(int i = 0; i < cnt; ++i)
    //{
    //    printf("%d %f\n", it->Data, calDistance(array + it->Data, &BondPoint));
    //    it = it->Next;
    //}
    free(FirstJump);

    return;
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
        if(calDistance(&BondPoint, array + i) - 7.5 > 0 && calDistance(&BondPoint, array + i) - 7.5 <= D){// 排除鳄鱼在岛上的情况
            ConnectVertex(G, i, N + 1);
        }
    }
    // 直接连接岸边与BOND - 针对测试用例5
    if(calDistanceBoundary(&BondPoint) - 7.5 <= D)
    {
        ConnectVertex(G, N, N + 1);
    }

    // 调整第一跳的顺序，使得第一跳路径距离较短的结点先行进入 - 针对测试用例4
    adjustFirstJump(G, array, N);

    //List it = G->Element[N].Next;
    //while(it){
    //    printf("%d %f\n", it->Data, calDistance(array + it->Data, &BondPoint));
    //    it = it->Next;
    //}

    int* patharray = malloc(sizeof(*patharray)*(N+2));
    for(int i = 0; i < N + 2; ++i)
    {
        patharray[i] = -1;
    }

    // 得到路径
    // N + 1 is Bond, N is Boundary
    int isConnected = findPath(G, N + 1, N, patharray);

    
    //for(int i = 0; i < N; ++i)
    //{
    //    printf("%d %d\n", array[i].x, array[i].y);
    //}
    //printf("\n");

    // 甚至不用返回距离，因为可以直接通过栈顶得到
    int Stack[50];
    int top = -1;
    if(isConnected)
    {
        int i = N;

        while(i != patharray[i])
        {
            ++top;
            Stack[top] = i;
            i = patharray[i];
        }

        printf("%d\n", isConnected);
        while(top != -1)
        {
            if(Stack[top] < N)
            {
                //printf("%d\t", Stack[top]);
                printf("%d %d\n", array[Stack[top]].x, array[Stack[top]].y);
            }
            --top;
        }
    }
    else
    {
        printf("%d\n", isConnected);
    }

    free(array);
    free(patharray);

    return 0;
}