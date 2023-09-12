#include <vector>
#include <iostream>

using namespace std;

void getPreorder(vector<int>& psO, vector<int>& inO, vector<int>& prO)
{
    int root = psO.back();
    int root_pos;
    for(int i = 0; i < psO.size(); ++i)
        if(inO[i] == root)
            root_pos = i;
    prO[0] = root;
    vector<int> LT(root_pos);
    vector<int> RT(prO.size() - root_pos - 1);
    vector<int> psO_LT(root_pos);
    vector<int> psO_RT(prO.size() - root_pos - 1);
    vector<int> inO_LT(root_pos);
    vector<int> inO_RT(prO.size() - root_pos - 1);
    for(int i = 0; i < LT.size(); ++i)
    {
        psO_LT[i] = psO[i];
        inO_LT[i] = inO[i];
    }
    for(int i = root_pos; i < inO.size() - 1; ++i)
    {
        psO_RT[i - root_pos] = psO[i];
        inO_RT[i - root_pos] = inO[i + 1];
    }
    
    getPreorder(psO_LT, inO_LT, LT);
    getPreorder(psO_RT, inO_RT, RT);

    for(int i = 0; i < LT.size(); ++i)
    {
        prO[i + 1] = LT[i];
    }
    for(int i = 0; i < RT.size(); ++i)
    {
        prO[i + 1 + LT.size()] = RT[i];
    }
    return;
}

int main()
{
    // INIT
    int N;
    cin >> N;
    vector<int> preorder(N);
    vector<int> inorder(N);
    vector<int> postorder(N);
    
    for(int i = 0; i < N; ++i)
        cin >> postorder[i];
    for(int i = 0; i < N; ++i)
        cin >> postorder[i];

    getPreorder(postorder, inorder, preorder);
    printf("Preorder:");
    for(auto& i : preorder)
    {
        cout << " " << i;
    }
    return 0;
}