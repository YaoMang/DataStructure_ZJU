#ifndef _HEADER_ESSENTIAL_H_
#define _HEADER_ESSENTAIL_H_

#include <stdlib.h>

/*
 * 单向链表结点的定义
 * 
 * 拥有一个指针域
 * 
 * Finished
 */
struct Node_SP
{
    typedef int DataType;

    DataType Data;
    struct Node_SP* Next;
};

// 单向链表的定义，包含头节点实现
typedef struct Node_SP* SList;

/*
 * @name CreateList
 * @param void
 * @return Single List
 */
// 创建一个空链表
SList CreateList()
{
    SList ret = (SList)malloc(sizeof(*ret));
    ret->Next = NULL;
    ret->Data = 0;

    return ret;
}

// 检查链表是否为空
int isEmptyList(SList L)
{
    int ret = 0;
    if(!L->Next)
    {
        ret = 1;
    }
    return ret;
}

// 删除单向链表
void DestroySList(SList L)
{
    while(L->Next)
    {

    }
}

// 堆栈的定义（链式实现）
typedef SList Stack;

// 创建一个堆栈
Stack Stack_Create()
{
    Stack ret = CreateList();
    return ret;
}

// 删除一个堆栈
void Stack_Destroy(Stack S)
{
    DestroySList(S);
}


/*
 * 拥有两个指针域的结点的定义
 */
struct Node_DP
{
    typedef int DataType;

    DataType Data;
    struct Node_DP* LP;
    struct Node_DP* RP;
};

// 二叉树，链式结构实现
typedef struct Node_DP* BinaryTree;

// 双向链表
typedef struct Node_DP* DList;

// 矩阵结构定义
struct Matrix
{
    int row;
    int col;
    int** matrix;
};

typedef struct Matrix Matrix;

// 图，邻接矩阵实现
typedef struct Matrix MGraph;

// 创建一个空的图
MGraph CreateMGraph(int Vertex)
{
    MGraph ret;
    ret.col = Vertex;
    ret.row = Vertex;

    // We need a matrix that filled with all 0
    ret.matrix = (int**)calloc(ret.row, sizeof(*ret.matrix));
    for(int i = 0; i < ret.row; ++i)
    {
        ret.matrix[i] = (int*)calloc(ret.col, sizeof(**ret.matrix));
    }

    return ret;
}

// 向图中插入边
int InsertEdge(MGraph G, int V1, int V2, int weight)
{
    if(V1 < G.row && V2 < G.col)
    {
        G.matrix[V1][V2] = weight;
        return 0;
    }
    return -1;
}

// 无向图插入
int InsertEdge_ND(MGraph G, int V1, int V2, int weight)
{
    int ret = 0;
    ret = InsertEdge(G, V1, V2, weight);
    if(ret){
        ret = -1;
        return ret;
    }
    ret = InsertEdge(G, V2, V1, weight);
    if(ret){
        ret = -1;
        return ret;
    }
}

// 图的广度优先遍历
int MGraph_BFS()
{
    return 0;
}

// 无权图的单源最短路算法
int MGraph_Unweighted(MGraph G, int V1, int V2)
{
    return 0;
}

// Dijkstra 算法
int Dijkstra(MGraph G, int V1, int V2)
{
    return 0;
}

// Floyd 算法
int Floyd(MGraph G, MGraph D, MGraph P)
{
    // 初始化
        // 距离矩阵，初始化时进行复制操作
        // 路径矩阵，初始化时设置为不存在的结点编号
    for(int i = 0; i < G.row; ++i)
    {
        for(int j = 0; j < G.col; ++j)
        {
            D.matrix[i][j] = G.matrix[i][j];
            P.matrix[i][j] = -1;
        }
    }

    // 核心算法
    for(int k = 0; k < D.col; ++k)
    {
        // 取点k
        for(int i = 0; i < D.col; ++i)
        {
            for(int j = 0; j < D.col; ++j)
            {
                // i j 之间的距离大于 i k, j k之间的距离，即i j 间存在更短路径
                if(D.matrix[i][k] + D.matrix[k][j] < D.matrix[i][j])
                {
                    // 发现更近的边，更新距离并更新路径
                    D.matrix[i][j] = D.matrix[i][k] + D.matrix[k][j];
                    // 更新i j 之间的更短路径为k
                    P.matrix[i][j] = k;
                    if(i == j && D.matrix[i][j] < 0)
                    {
                        //发现负值圈,返回运行异常
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

// 图 邻接表实现
struct LGraph
{
    int VertexNum;
    struct Node_SP** space;
};

typedef struct LGraph LGraph;

#endif