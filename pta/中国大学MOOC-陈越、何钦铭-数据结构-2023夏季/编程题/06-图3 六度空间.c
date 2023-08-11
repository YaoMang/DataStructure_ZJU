// 广度优先遍历，并记录层数

#include <stdio.h>
#include <stdlib.h>

typedef struct Node* List;

// 链式结构结点定义
struct Node{
    int Data;
    List Next;
};

// 图，邻接表实现
struct Graph{
    int Size;
    List Elements;
};

typedef struct Graph* Graph;

// 队列，链式结构实现
typedef List Queue;

Queue CreateQueue()
{
    Queue ret = malloc(sizeof(*ret));
    ret->Data = 0;
    ret->Next = NULL;

    return ret;
}

Queue Enqueue(Queue Q, int Data)
{
    Queue it = Q;
    while(it->Next){
        it = it->Next;
    }
    it->Next = malloc(sizeof(*it));
    it->Next->Data = Data;
    it->Next->Next = NULL;

    return Q;
}

int Dequeue(Queue Q)
{
    int ret;
    if(Q->Next){
        ret = Q->Next->Data;
        Queue Temp = Q->Next;
        Q->Next = Temp->Next;
        free(Temp);
    }
    else{
        ret = -1;
    }

    return ret;
}

int isQueueEmpty(Queue Q)
{
    return !Q->Next;
}

void DestroyQueue(Queue Q)
{
    // 从链开头释放链表空间
    Queue Temp;
    if(Q->Next){
        Temp = Q->Next->Next;
        free(Q->Next);
        Q->Next = Temp;
    }
    free(Q);
}

// 广度优先搜索
int BFS(Graph G, int Vertex)
{
    int ret = 1;
    // 记录层数和每层的末尾顶点
    int level = 0, tail = 0, last = Vertex;
    // 创建广度优先搜索需要的基本组件
    int* Visited = calloc(G->Size, sizeof(*Visited));
    Queue Q = CreateQueue();
    
    // 入队
    Enqueue(Q, Vertex);
    Visited[Vertex] = 1;

    // 迭代器
    int it_v;
    List it_e;
    // 队列不为空
    while(!isQueueEmpty(Q)){
        it_v = Dequeue(Q);
        
        it_e = G->Elements + it_v;

        // FOR DEBUG USAGE
        //if(it_e->Next){
        //    printf("NEXT DATA: %d\n", it_e->Next->Data);
        //}

        while(it_e->Next){
            it_e = it_e->Next;
            if(!Visited[it_e->Data]){
                Visited[it_e->Data] = 1;
                Enqueue(Q, it_e->Data);
                ++ret;
                tail = it_e->Data;
            }
        }
        // 最后一个连接的顶点
        if(it_v == last){
            ++level;
            last = tail;
        }
        if(level == 6){
            break;
        }
    }
    // 返还相应空间
    DestroyQueue(Q);
    free(Visited);

    return ret;
}

// 六度空间
int SDS(Graph G)
{
    // 注意第一个位置是空出来的
    int count = 0;
    for(int i = 1; i < G->Size; ++i){
        count = BFS(G, i);
        printf("%d: %.02f%%\n", i, (double)count/(G->Size-1)*100);
    }
    return 0;
}

int ConnectVertex(Graph G, int Vertex_1, int Vertex_2)
{
    // 这种实现方式假定输入是无重复的,不检查值是否已经存在
    List it = G->Elements + Vertex_1;
    while(it->Next){
        it = it->Next;
    }
    it->Next = malloc(sizeof(*it));
    it->Next->Data = Vertex_2;
    it->Next->Next = NULL;

    it = G->Elements + Vertex_2;
    while (it->Next){
        it = it->Next;
    }
    it->Next = malloc(sizeof(*it));
    it->Next->Data = Vertex_1;
    it->Next->Next = NULL;
    
    return 0;
}

Graph CreateGraph(int Size)
{
    Graph ret = malloc(sizeof(*ret));
    ret->Size = Size;
    ret->Elements = calloc(Size, sizeof(*ret->Elements));

    return ret;
}

int main()
{
    // 读入数据
    int N, M;
    scanf("%d %d", &N, &M);

    // 创建图并读入数据
    Graph G = CreateGraph(N+1); // 空置第一个位置，便于实现

    int Vertex_1, Vertex_2;
    for(int i = 0; i < M; ++i){
        scanf("%d %d", &Vertex_1, &Vertex_2);
        ConnectVertex(G, Vertex_1, Vertex_2);
    }

    // 六度空间
    SDS(G);

    return 0;
}