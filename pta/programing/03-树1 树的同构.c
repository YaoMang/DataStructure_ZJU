#include <stdio.h>
#include <stdlib.h>

#define Null -1

typedef char ElementType;
typedef struct Tree*  Tree;

struct Tree
{
    ElementType Data;
    Tree L;
    Tree R;
};

typedef struct TreeArray* TreeArray;

struct TreeArray
{
    ElementType Data;
    int L;
    int R;
};

int convert(char c)
{
    if(c == '-'){
        return Null;
    }
    else{
        return c - '0';
    }
}

TreeArray input()
{
    int cnt = 0;
    scanf("%d", &cnt);

    TreeArray TS = NULL;

    TS = (TreeArray)malloc((cnt + 1) * sizeof(*TS));
    TS->Data = '*';
    TS->L = cnt;

    int check[TS->L];
    for(int i = 0; i < cnt; ++i){
        check[i] = 0;
    }

    TreeArray it = TS + 1;
    for(int i = 1; i <= cnt; ++i){
        scanf("\n%c %c %c", &(it->Data), &(it->L), &(it->R));
        it->L = convert((char)it->L);
        it->R = convert((char)it->R);
        if(it->L != Null){
            check[TS->L] = 1; 
        }
        if(it->R != Null){
            check[TS->R] = 1;
        }
        ++it;
    }

    for(int i = 0; i < cnt; ++i){
        if(check[i] == 0){
            TS->R = i;
            break;
        }
    }

    return TS;
}

Tree FetchNode(TreeArray TS, int Node)
{
    if(Node == Null){
        return NULL;
    }
    else{
        Tree Node_t = (Tree)malloc(sizeof(*Node_t));
        Node_t->Data = TS[Node].Data;
        Node_t->L = FetchNode(TS, TS[Node].L);
        Node_t->R = FetchNode(TS, TS[Node].R);

        return Node_t;
    }
}

Tree buildTree(TreeArray TS)
{
    //printf("starting build\n");
    if(TS->L == 0){
        return NULL;
    }

    //printf("fetch node, start\n");

    Tree ROOT = FetchNode(TS + 1, TS->R);

    //printf("finished build\n");

    return ROOT;
}

int iso(Tree T1, Tree T2)
{
    //printf("Now:%c %c", T1->Data, T2->Data);
    if(T1 == NULL && T2 == NULL){
        return 1;
    }
    if(T1 == NULL || T2 == NULL){
        return 0;
    }
    if(T1->Data != T2->Data){
        return 0;
    }
    if(iso(T1->L, T2->L)){
        return iso(T1->R, T2->R);
    }
    return iso(T1->L, T2->R) && iso(T1->R, T2->L);
}

void showArray(TreeArray TS)
{
    int cnt = TS->L;
    for(int i = 1; i <= cnt; ++i){
        printf("%c %d %d\n", TS[i].Data, TS[i].L, TS[i].R);
    }
}

void showTree(Tree T)
{
    if(T){
        printf("%c ", T->Data);
        showTree(T->L);
        showTree(T->R);
    }
}

int main()
{
    TreeArray TS1, TS2;
    Tree T1, T2;

    TS1 = input();
    TS2 = input();

    //printf("INPUT");

    //showArray(TS1);
    //showArray(TS2);

    T1 = buildTree(TS1);
    //showTree(T1);
    free(TS1);
    T2 = buildTree(TS2);
    //showTree(T2);
    free(TS2);


    //showTree(T1);
    //showTree(T2);

    //printf("HI");

    if(iso(T1, T2)){
        printf("Yes");
    }
    else{
        printf("No");
    }
}