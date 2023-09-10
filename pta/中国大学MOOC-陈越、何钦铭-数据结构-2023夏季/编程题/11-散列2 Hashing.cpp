#include <cstdio>
#include <vector>

using namespace std;

struct HashTable
{
    int Size;
    vector<int> Seq;
};

bool isPrime(int N)
{
    bool flag = true;

    // 注意例外情况，1不是素数
    if(N == 1)
        return false;

    for(int i = 2; i * i <= N; ++i)
    {
        if(N%i == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

int FindPrime(int N)
{
    int i;
    for(i = N; 1; ++i)
    {
        if(isPrime(i))
            break;
    }
    return i;
}

void Insert(vector<int> &outSeq, HashTable &H, int Key, int cnt)
{
    int HashSpace = Key%H.Size;
    int InsertSpace;
    int loopCtrl = 0;
    int InsertFlag = 0;
    while(loopCtrl < H.Size)
    {
        InsertSpace = HashSpace + loopCtrl * loopCtrl;
        InsertSpace %= H.Size;

        if(H.Seq[InsertSpace] == -1)
        {
            H.Seq[InsertSpace] = Key;
            InsertFlag = 1;
            break;
        }
        ++loopCtrl;
    }

    if(InsertFlag)
        outSeq[cnt] = InsertSpace;
    else
        outSeq[cnt] = -1;
    
    return;
}

int main()
{
    // INIT
    int userSpace, userInput;
    scanf(" %d %d", &userSpace, &userInput);

    HashTable H;
    H.Size = FindPrime(userSpace);

    H.Seq.resize(H.Size);
    for(auto& i : H.Seq)
        i = -1;

    vector<int> outSeq(userInput, -1);

    // Insert
    for(int i = 0; i < userInput; ++i)
    {
        scanf(" %d", &userSpace);
        Insert(outSeq, H, userSpace, i);
    }

    // Output
    for(int i = 0; i < outSeq.size() - 1; ++i)
    {
        if(outSeq[i] != -1)
            printf("%d ", outSeq[i]);
        else
            printf("- ");
    }
    if(outSeq[outSeq.size() - 1] != -1)
            printf("%d", outSeq[outSeq.size() - 1]);
        else
            printf("-");

    return 0;
}