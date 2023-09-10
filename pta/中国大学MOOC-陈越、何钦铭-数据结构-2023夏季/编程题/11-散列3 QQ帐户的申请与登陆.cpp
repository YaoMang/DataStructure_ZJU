#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <string>

using namespace std;


// 为节省空间，密码可以直接散列
struct AcctNode
{
    int Num_1;
    string passwd;
};

struct HashTable
{
    int Size;
    vector<list<AcctNode>> Table;
};

void resolve(string& src, int& dst1, int& dst2)
{
    string operate;
    if(src.size() < 10)
    {
        int lenth = 10 - src.size();
        string fill(lenth, '0');
        operate = fill + src;
    }
    else
    {
        operate = src;
    }

    dst1 = stoi(operate.substr(0, 5));
    dst2 = stoi(operate.substr(5, 10));

    return;
}

const int lookup_code_ne = 0;
const int lookup_code_wpw = 1;
const int loopup_code_success = 2;

int Lookup(string& qn, string& pw, HashTable& H)
{
    int tableNum, NodeNum;
    resolve(qn, NodeNum, tableNum);

    for(auto& N : H.Table[tableNum])
        if(N.Num_1 == NodeNum)
        {
            if(N.passwd == pw)
                return loopup_code_success;
            else
                return lookup_code_wpw;
        }
    
    return lookup_code_ne;
}

int Insert(string& qn, string& pw, HashTable& H)
{
    int tableNum, NodeNum;
    resolve(qn, NodeNum, tableNum);

    for(auto& N : H.Table[tableNum])
        if(N.Num_1 == NodeNum)
            return 0;
    
    AcctNode NewNode;
    NewNode.Num_1 = NodeNum;
    NewNode.passwd = pw;
    H.Table[tableNum].push_back(NewNode);

    return 1;
}

void QQNum_operator(string& ins1, string& ins2, string& ins3, HashTable &H)
{
    char c = ins1.front();
    if(c == 'L')
    {
        switch (Lookup(ins2, ins3, H))
        {
        case lookup_code_ne:
            printf("ERROR: Not Exist\n");
            break;
        case lookup_code_wpw:
            printf("ERROR: Wrong PW\n");
            break;
        default:
            printf("Login: OK\n");
            break;
        }
    }
    else if(c == 'N')
    {
        if(Insert(ins2, ins3, H))
            printf("New: OK\n");
        else
            printf("ERROR: Exist\n");
    }
    return;
}

int main()
{
    // INIT
    int N;
    scanf(" %d", &N);

    HashTable H;
    H.Size = 100000;
    H.Table.resize(H.Size);

    string str_ins1, str_ins2, str_ins3;
    for(int i = 0; i < N; ++i)
    {
        cin >> str_ins1 >> str_ins2 >> str_ins3;
        QQNum_operator(str_ins1, str_ins2, str_ins3, H);
    }

    return 0;
}
