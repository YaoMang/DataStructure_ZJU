// 计算最短路径（由某一点出发的），多对多的路径问题

// 使用Floyd 算法实现题目的要求

#include <stdio.h>
#include <stdlib.h>

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

MGraph DestroyGraph(MGraph G)
{
    for(int i = 0; i < G.row; ++i)
    {
        free(G.matrix[i]);
    }
    free(G.matrix);
    G.col = 0;
    G.row = 0;

    return G;
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

// 复制图,返回一个与原图内容一样的图，但存储于不同空间
MGraph CopyMGraph(MGraph G)
{
    MGraph ret = CreateMGraph(G.col);
    for(int i = 0; i < G.col; ++i)
    {
        for(int j = 0; j < G.col; ++j)
        {
            ret.matrix[i][j] = G.matrix[i][j];
        }
    }
    return ret;
}

// Floyd 算法
Matrix Floyd(MGraph G)
{
    // 距离矩阵，初始化时进行复制操作
    MGraph D = CopyMGraph(G);
    
    // 路径矩阵，初始化时设置为不存在的结点编号
    MGraph P = CreateMGraph(G.col);
    for(int i = 0; i < P.row; ++i)
    {
        for(int j = 0; j < P.col; ++j)
        {
            P.matrix[i][j] = -1;
        }
    }

    for(int k = 0; k < D.col; ++k)
    {
        for(int i = 0; i < D.col; ++i)
        {
            for(int j = 0; j < D.col; ++j)
            {
                if(D.matrix[i][k] + D.matrix[k][j] < D.matrix[i][j])
                {
                    // 发现更近的边，更新距离并更新路径
                    D.matrix[i][j] = D.matrix[i][k] + D.matrix[k][j];
                }
                P.matrix[i][j] = k;
            }
        }
    }
    // 释放路径矩阵空间
    DestroyGraph(P);
    return D;
}

void PrintMatrix(Matrix Mat)
{
    for(int i = 0; i < Mat.row; ++i)
    {
        for(int j = 0; j < Mat.col; ++j)
        {
            printf("%d\t", Mat.matrix[i][j]);
        }
        printf("\n");
    }
}


//----------
// 针对本题的程序和函数
//----------

#define INFINITY 0x0fffffff

MGraph read();
void FindAnimal(Matrix D);

int main()
{
    // 输入信息
    MGraph G = read();

    // 得到距离矩阵
    Matrix D = Floyd(G);

    // For DEBUG PURPOSE
    //PrintMatrix(D);

    // 选择最小行输出
    FindAnimal(D);

    return 0;
}

// 用于数据读入
MGraph read()
{
    int n_N = 0;
    int n_E = 0;

    scanf("%d %d", &n_N, &n_E);

    MGraph G = CreateMGraph(n_N);
    for(int i = 0; i < G.col; ++i)
    {
        for(int j = 0; j < G.col; ++j)
        {
            if(i != j)
            {
                G.matrix[i][j] = INFINITY;
            }
            else{
                G.matrix[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < n_E; ++i)
    {
        int n_v1,n_v2,n_wht;
        scanf(" %d %d %d", &n_v1, &n_v2, &n_wht);
        // 由于矩阵中点从0 0 开始，这里在输入时减去1
        InsertEdge_ND(G, n_v1 - 1, n_v2 - 1, n_wht);
    }

    return G;
}

// 寻找一行中的最大值
// DEBUG: WORKING PROPERLY
int findMaxDist(Matrix D, int row)
{
    int ret = 0;
    for(int i = 0; i < D.col; ++i)
    {
        if(D.matrix[row][i] > ret)
        {
            ret = D.matrix[row][i];
        }
    }
    return ret;
}

// 找到需要携带的动物
void FindAnimal(Matrix D)
{
    int Animal, MinDist;
    MinDist = INFINITY;
    for(int i = 0; i < D.row; ++i)
    {
        int MaxDist = findMaxDist(D, i);
        if(MaxDist == INFINITY)
        {
            printf("0\n");
            return;
        }
        if(MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = i + 1;
        }
    }
    printf("%d %d\n", Animal, MinDist);
}
