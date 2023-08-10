// 图的深度优先和广度优先遍历以及图的表示

#include <stdio.h>
#include <stdlib.h>

// 图结构的定义，这里使用邻接矩阵实现
struct Matrix{
    int Rows;
    int Cols;
    int* Element;
};

typedef struct Matrix* Graph;

// 队列，循环队列，连续结构实现
struct Queue{
    int Size;
    int Capacity;
    int* space;
    
    int front;
    int rare;
};

typedef struct Queue* Queue;

// 创建一个循环队列
Queue CreateQueue(int Size)
{
    Queue ret = (Queue)malloc(sizeof(*ret));

    ret->Size = 0;
    ret->Capacity = Size;
    ret->space = (int*)malloc(sizeof(int)*Size);
    ret->front = 0;
    ret->rare = 0;

    return ret;
}

// 入队
int Enqueue(Queue Q, int Data)
{
    // 检查队列是否已满
    if(Q->Size < Q->Capacity){
        // 队列存在剩余空间

        // 确定目前队尾位置
        Q->rare = Q->rare % Q->Capacity;
        Q->space[Q->rare] = Data;
        ++(Q->rare);
        ++(Q->Size);
        
        return 0;
    }
    else{
        return -1;
    }
}

// 出队
int Dequeue(Queue Q)
{
    int ret = 0;

    // 确认队列不为空
    if(Q->Size != 0){
        Q->front = Q->front % Q->Capacity;
        ret = Q->space[Q->front];
        ++(Q->front);
        --(Q->Size);
    }
    else{
        ret = -1;
    }

    return ret;
}

int isQueueFull(Queue Q)
{
    return Q->Size == Q->Capacity;
}

int isQueueEmpty(Queue Q)
{
    return Q->Size == 0;
}

// 销毁队列
void DestroyQueue(Queue Q)
{
    free(Q->space);
    free(Q);

    return;
}

void printArray(int* array, int n)
{
    printf("{ ");
    for(int i = 0; i < n; ++i){
        printf("%d ", array[i]);
    }
    printf("}\n");
}

// 建立一个图
Graph CreateGraph(int Size)
{
    Graph ret = (Graph)malloc(sizeof(*ret));

    ret->Cols = Size;
    ret->Rows = Size;
    ret->Element = (int*)malloc(sizeof(*ret->Element) * Size * Size);

    // 初始值设置（可以通过 calloc直接获得对应全零空间）
    for(int i = 0; i < Size * Size; ++i){
        ret->Element[i] = 0;
    }

    // DEBUG
    //for(int i = 0; i < Size; ++i){
    //    for(int j = 0; j < Size; ++j){
    //        ret->Element[i][j] = 0;
    //    }
    //}

    return ret;
}

// 广度优先搜索，从小到大顺序
void BFS(Graph G)
{
    // 创建标记和队列
    int* Visited = calloc(G->Cols, sizeof(*Visited));
    Queue Q = CreateQueue(G->Cols);

    int* VisitSeq = (int*)malloc(sizeof(*VisitSeq)*G->Cols);
    int cnt = 0;
    
    // 从小到大遍历
    for(int i = 0; i < G->Cols; ++i){
        // 判断顶点是否被访问过
        if(!Visited[i]){
            // 遇到没有访问过的结点
            Enqueue(Q, i);
            // 入队标记访问
            Visited[i] = 1;

            VisitSeq[cnt] = i;
            ++cnt;

            // 队列不为空
            while(!isQueueEmpty(Q)){
                // 出队
                int it = Dequeue(Q);

                // 广度优先遍历
                for(int j = 0; j < G->Cols; ++j){
                    if(G->Element[it * G->Cols + j] && Visited[j] == 0){
                        // 未访问过的连通结点按顺序入队
                        Enqueue(Q, j);
                        // 标记访问，防止重复入队
                        Visited[j] = 1;

                        VisitSeq[cnt] = j;
                        ++cnt;
                    }
                }
            }
            // 寻找连通集结束
            printArray(VisitSeq, cnt);
            cnt = 0;
        }
    }

    free(Q);
    free(Visited);
    free(VisitSeq);
}

// 深度优先搜索，非递归实现
void DFS(Graph G)
{
    // 堆栈
    int* S = malloc(sizeof(*S)*G->Cols);
    int top = -1;

    // 访问标记
    int* Visited = calloc(G->Cols, sizeof(*Visited));

    // 计数器
    int cnt = 0;
    // 保存访问结果
    int* VisitSeq = (int*)malloc(sizeof(*VisitSeq)*G->Cols);

    for(int i = 0; i < G->Cols; ++i){
        // 判断顶点是否访问过
        if(!Visited[i]){
            // 未访问，标记为已经访问
            Visited[i] = 1;

            VisitSeq[cnt] = i;
            ++cnt;
            
            // 将顶点压栈
            ++top;
            S[top] = i;
            
            // 迭代器
            int it = i;
            // 找到未访问邻接点标记
            int wasFound = 0;
            // 判断堆栈不为空
            while(top != -1){
                // 寻找邻接点
                wasFound = 0;
                for(int j = 0; j < G->Cols; ++j){
                    if(G->Element[it*G->Cols + j] && Visited[j]==0){
                        // 找到邻接点，标记访问
                        it = j;
                        Visited[j] = 1;

                        VisitSeq[cnt] = j;
                        ++cnt;
                        
                        // 将这一点压栈
                        ++top;
                        S[top] = j;

                        // 修改标记
                        wasFound = 1;

                        break;
                    }
                }

                if(wasFound){ // 迭代器修改
                    it = S[top];
                }
                else{ // Pop对应内容，回到上一个顶点
                    --top;
                    it = S[top];
                }
            }

            // 寻找连通集结束,打印连通集
            printArray(VisitSeq, cnt);
            cnt = 0;
        }
    }
    free(S);
    free(VisitSeq);
    free(Visited);
}


int main()
{
    // 读入行数列数相关数据
    int V = 0, E = 0;
    scanf("%d %d", &V, &E);

    Graph G = CreateGraph(V);

    // 读入边信息
    int Vertex_1, Vertex_2;
    for(int i = 0; i < E; ++i){
        scanf("%d %d", &Vertex_1, &Vertex_2);
        G->Element[Vertex_1 * G->Cols + Vertex_2] = 1;
        G->Element[Vertex_2 * G->Cols + Vertex_1] = 1;
    }

    // 深度优先遍历
    DFS(G);

    // 广度优先遍历
    BFS(G);

    return 0;
}