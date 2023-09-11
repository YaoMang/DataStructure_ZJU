// KMP 算法
// Knuth Morris Pratt

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void BuildMatch(string& pattern, vector<int>& match)
{
    match.resize(pattern.size());
    int i, j;
    int m = match.size(); /* O(m) */
    match[0] = -1;

    for(j = 1; j < m; ++j) /* O(m) */
    {
        i = match[j - 1];
        while ((i>=0) && (pattern[i + 1] != pattern[j]))
            i = match[i];
        if (pattern[i + 1] == pattern[j])
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}

using Position = int;
Position KMP(string& str, string& pattern)
{
    int n = str.size(); /* O(n) */
    int m = pattern.size(); /* O(m) */
    int s,p;

    if(n < m)
        return -1;

    vector<int> match;
    BuildMatch(pattern, match); /* Tm = O(m) */
    s = p = 0;
    while( s < n && p < m){ /* O(n) */
        if(str[s] == pattern[p])
        {
            ++s;
            ++p;
        }
        else if (p > 0) 
            p = match[p - 1] + 1;
        else 
            ++s;
    }
    return (p == m)? (s - m) : -1;
}

int main()
{
    string str;
    string pat;

    cin >> str;
    int N;
    cin >> N;

    int pos;
    for(int i = 0; i < N; ++i)
    {
        pat.clear();
        cin >> pat;
        pos = KMP(str, pat);
        if(pos == -1)
            cout << "Not Found" <<'\n';
        else
        {
            for(int i = pos; i < str.size(); ++i)
                cout << str[i];
            cout << '\n';
        }
    }

    return 0;
}