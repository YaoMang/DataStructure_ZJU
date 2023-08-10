// 并查集

#include <stdio.h>
#include <stdlib.h>

// 集合结点
struct setNode{
    int Data;
    int Parent;
};

typedef struct setNode* Set;

void SetConnect(Set S, int a, int b)
{
    // 找到a,b的根结点
    int parent_a, parent_b;
    int it = a;
    while(S[it].Parent > 0){
        it = S[it].Parent;
    }
    parent_a = it;

    it = b;
    while(S[it].Parent > 0){
        it = S[it].Parent;
    }
    parent_b = it;

    if(parent_a == parent_b){
        return;
    }

    // 规模大小为负数
    if(S[parent_a].Parent < S[parent_b].Parent){
        S[parent_b].Parent = parent_a;
        --S[parent_a].Parent;
    }
    else{
        S[parent_a].Parent = parent_b;
        --S[parent_b].Parent;
    }

    return;
}

int subSets(Set S, int size)
{
    int cnt = 0;
    for(int i = 1; i <= size; ++i){
        if(S[i].Parent < 0){
            ++cnt;
        }
    }
    return cnt;
}

int ifConnected(Set S, int a, int b)
{
    int parent_a, parent_b;

    // 迭代器
    int it = a;
    // 检查父结点
    while(S[it].Parent > 0){
        it = S[it].Parent;
    }
    parent_a = it;
    
    it = b;
    while(S[it].Parent > 0){
        it = S[it].Parent;
    }
    parent_b = it;

    if(parent_a == parent_b){
        return 1;
    }
    else{
        return 0;
    }
}

int main()
{
    // 读入数据数量
    int n_Node = 0;
    scanf("%d", &n_Node);

    Set SetSpace = (Set)malloc(sizeof(*SetSpace)*(n_Node+1));
    for(int i = 1; i <= n_Node; ++i){
        SetSpace[i].Data = i;
        SetSpace[i].Parent = -1;
    }

    // 读入操作
    char buf;
    int n_1, n_2;
    while(buf != 'S'){
        scanf("%c %d %d", &buf, &n_1, &n_2);
        if(buf == 'I'){
            SetConnect(SetSpace, n_1, n_2);
        }
        else if(buf == 'C'){
            if(ifConnected(SetSpace, n_1, n_2)){
                printf("yes\n");
            }
            else{
                printf("no\n");
            }
        }
    }

    if(subSets(SetSpace, n_Node) == 1){
        printf("The network is connected.\n");
    }
    else{
        printf("There are %d components.\n", subSets(SetSpace, n_Node));
    }

    return 0;
}