// 计算最优编码长度（题中编码不一定是哈夫曼编码）

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 二叉树，链式实现
typedef struct BinTree BinTree;
struct BinTree{
    int Data;
    char c;
    BinTree* LT;
    BinTree* RT;
};

// 堆，顺序结构实现
typedef struct Heap Heap;
struct Heap{
    int Size;
    int Capacity;
    BinTree** space;
};

// 最小堆定义
BinTree minNode;

typedef Heap* minHeap;

// 建立一个最小堆
minHeap CreateMinHeap()
{
    minHeap MinH = malloc(sizeof(*MinH));
    MinH->space = NULL;
    MinH->Size = 0;
    MinH->Capacity = 0;

    return MinH;
}

void swap(BinTree** a, BinTree** b)
{
    BinTree* temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// 直接调整得到最小堆，这一操作会使得原来的堆被覆盖
minHeap AdjustMinHeap(minHeap H, BinTree* Array, int n)
{
    if(H->space){
        free(H->space);
    }
    H->Size = n;
    H->Capacity = n;
    H->space = malloc(sizeof(*H->space)*(n + 1));
    H->space[0] = &minNode;
    // memcpy
    for(int i = 1; i <= n; ++i){
        H->space[i] = Array + i - 1;
    }
    // Adjust

    // DEBUG
    //for(int i = 1; i <= H->Size; ++i){
    //    printf("No %d, Weight: %d, Value: %c\n", i, H->space[i]->Data, H->space[i]->c);
    //}

    // 设置初始结点为最后一个结点的父结点
    int i = n/2;
    // 检查该节点的左右子树
    if(n/2 * 2 + 1 <= H->Size){// 右子树存在
        if(H->space[H->Size]->Data < H->space[i]->Data){
            swap(&H->space[H->Size], &H->space[i]);
        }
    }
    if(H->space[i]->Data > H->space[i * 2]->Data){// 检查左子树
        swap(&H->space[i], &H->space[i * 2]);
    }
    --i;
    
    // 检查剩余的结点
    while(i != 0){
        if(H->space[i]->Data > H->space[i * 2 + 1]->Data){// 右子树
            swap(&H->space[i], &H->space[i * 2]);
        }
        if(H->space[i]->Data > H->space[i * 2]->Data){ // 左子树
            swap(&H->space[i], &H->space[i * 2]);
        }
        --i;
    }
    
    //DEBUG
    //for(int i = 1; i <= H->Size; ++i){
    //    printf("No %d, Weight: %d, Value: %c\n", i, H->space[i]->Data, H->space[i]->c);
    //}

    return H;
}

minHeap Insert(minHeap H, BinTree* Data)
{
    // Size + 1
    ++H->Size;
    if(H->Size > H->Capacity){
        --H->Size;
        return NULL;
    }
    // 为最后一个结点赋值
    H->space[H->Size] = Data;

    // 调整堆
    int i = H->Size;
    while(H->space[i]->Data < H->space[i/2]->Data)
    {
        // 当结点小于其父结点时，交换其与父结点，直至结点大于其父结点
        swap(&H->space[i], &H->space[i/2]);
        i /= 2;
    }
    return H;
}

// 从堆中删除最小值
BinTree* DeleteMin(minHeap H)
{
    // 检查最小堆是否为空
    if(!H->Size){
        return NULL;
    }

    // 得到最小值
    BinTree* ret = H->space[1];
    
    H->space[1] = H->space[H->Size];
    --(H->Size);

    int Parent = 1;
    int Child = 0;
    while (Parent * 2 <= H->Size)
    {
        // 选择左右子树中较小的交换
        Child = Parent * 2;
        if((Child != H->Size) && (H->space[Child]->Data > H->space[Child + 1]->Data))
        {
            ++Child;
        }
        if(H->space[Parent]->Data < H->space[Child]->Data){
            break;
        }
        swap(&H->space[Child], &H->space[Parent]);
        Parent = Child;
    }
    return ret;
}

// 哈夫曼树定义
typedef BinTree* HuffmanTree;

// 哈夫曼算法，建立哈夫曼树，使用堆实现
HuffmanTree Huffman(BinTree Array[], int n)
{
    int i;
    HuffmanTree T;
    
    minHeap H = CreateMinHeap();
    H = AdjustMinHeap(H, Array, n);

    // 合并次数为 H->Size - 1
    int cnt = H->Size;
    for(i = 1; i < cnt; ++i)
    {
        // 分配新的结点
        T = malloc(sizeof(*T));
        // 得到左右子树
        T->LT = DeleteMin(H);
        T->RT = DeleteMin(H);
        // 得到结点权重
        T->Data = T->LT->Data + T->RT->Data;
        T->c = 'n';
        Insert(H, T);

        // DEBUG
        //printf("Now Node: %d, value: %c, Weight: %d\n", i, T->c, T->Data);
    }
    T = DeleteMin(H);
    T->Data = T->RT->Data + T->LT->Data;

    return T;
}

// 计算编码长度
int WPL(HuffmanTree T, int height)
{
    // 判断没有左右子树
    if(!T->LT && !T->RT)
    {
        return (T->Data)*height;
    }
    else
    {
        return WPL(T->LT, height + 1) + WPL(T->RT, height + 1);
    }
}

// 先序遍历，输出树信息
void Tranverse(HuffmanTree T)
{
    if(T)
    {
        printf("Node: %c\n", T->c);
        printf("Weight: %d\n", T->Data);
        Tranverse(T->LT);
        Tranverse(T->RT);
        return;
    }
    else
    {
        return;
    }
}

void BinTree_Destroy(BinTree* T)
{
    if(!T->LT && !T->RT){
        free(T);
    }
    else{
        if(T->LT){
            BinTree_Destroy(T->LT);
            T->LT = NULL;
        }
        if(T->RT){
            BinTree_Destroy(T->RT);
            T->RT = NULL;
        }
    }
}

// 前缀码检查
int PrefixCheck(char* c, char** str, int n)
{
    int isValid = 1;
    HuffmanTree T = malloc(sizeof(*T));
    T->c = 'n';
    T->LT = NULL;
    T->RT = NULL;

    // 根据输入信息建立二叉树
    for(int i = 0; i < n; ++i)
    {
        HuffmanTree it = T;
        for(int j = 0; j < strlen(*(str + i)); ++j)
        {
            // 内层循环，插入一个结点
            char compare = str[i][j];
            if(compare == '0'){
                // 向左侧延拓
                if(it->LT){
                    // 左侧已经有子树
                    if(it->LT->c != 'n'){
                        // 左侧子树是叶节点
                        isValid = 0;
                        goto TAG_END_OF_FUNC;
                    }
                    // 完成前进
                    it = it->LT;
                }
                else{
                    // 左侧没有子树
                    // 建立一个新的结点
                    it->LT = malloc(sizeof(*it));
                    // 完成前进
                    it = it->LT;

                    it->c = 'n';
                    it->LT = NULL;
                    it->RT = NULL;
                }
            }
            else{
                // 向右侧延拓
                if(it->RT){
                    // 右侧已经有子树
                    if(it->RT->c != 'n'){
                        // 右侧子树是叶节点
                        isValid = 0;
                        goto TAG_END_OF_FUNC;
                    }
                    // 完成前进
                    it = it->RT;
                }
                else{
                    // 右侧没有子树
                    // 建立一个新的结点
                    it->RT = malloc(sizeof(*it));
                    // 完成前进
                    it = it->RT;
    
                    it->c = 'n';
                    it->LT = NULL;
                    it->RT = NULL;
                }
            }
            // 检查是否为最后一个编码
            if(j == strlen(*(str + i)) - 1)
            {
                it->c = c[i];
                // 检查是否为叶节点
                if(it->LT || it->RT)
                {
                    isValid = 0;
                    goto TAG_END_OF_FUNC;
                }
            }
        }
    }
    TAG_END_OF_FUNC:
    BinTree_Destroy(T);
    return isValid;
}

int main()
{
    minNode.Data = 0;
    // 读入数据
    int c_Num = 0;
    int s_Num = 0;
    scanf("%d", &c_Num);
    BinTree* TreeArray = malloc(sizeof(*TreeArray)*c_Num);
    for(int i = 0; i < c_Num; ++i){
        // 跳过空白字符读取
        scanf(" %c %d", &TreeArray[i].c, &TreeArray[i].Data);
        TreeArray[i].LT = NULL;
        TreeArray[i].RT = NULL;
    }

    // 建树
    HuffmanTree T;
    T = Huffman(TreeArray, c_Num);

    // DEBUG
    //Tranverse(T);

    // 计算最小编码长度
    int CodeLen = WPL(T, 0);

    // DEBUG
    //printf("%d", CodeLen);
    
    // 读入学生数量数据

    // 分配数据存储空间
    scanf("%d", &s_Num);
    int BUFFER = 256;
    char* c = malloc(sizeof(*c)*c_Num);
    char** str = malloc(sizeof(*str)*c_Num);
    for(int i = 0; i < c_Num; ++i)
    {
        *(str + i) = malloc(sizeof(**str)*BUFFER);
    }

    // 读入学生数据
    for(int s = 0; s < s_Num; ++s){
        int isValid = 1;
        int sCodeLen = 0;
        for(int i = 0; i < c_Num; ++i){
            scanf(" %c %s", c + i, *(str + i));
            sCodeLen += strlen(*(str + i)) * (TreeArray + i)->Data;
        }
        if(CodeLen != sCodeLen){
            isValid = 0;
            goto TAG_OUTPUT_AREA;
        }
        isValid = PrefixCheck(c, str, c_Num);

        TAG_OUTPUT_AREA:
        if(isValid){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
}