#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long int ll;

struct Clearing
{
    void addfw(int index) { fw.push_back(index); }
    void addbw(int index) { bw.push_back(index); }
    vector<int> fw;
    vector<int> bw;
};

ll f(int i, Clearing c[], ll memo[])
{
    int s = c[i].fw.size();
    if(memo[i] != -1) { return memo[i]; } // Make sure that the grandma provides a 1
    if(s == 0) { memo[i] = 0; return 0; }
    ll result = 0;
    int j;
    for(j = 0; j < s; j++) { result += f(c[i].fw[j], c, memo); }
    memo[i] = result;
    return result;
}

ll g(int i, Clearing c[], ll memo[], ll memo2[])
{
    ll biggest = -1;
    ll j, s, cur, key;
    s = c[i].bw.size();
    if(s == 0) { return memo[i]; }
    for(j = 0; j < s; j++){
        key = c[i].bw[j];
        if(memo2[key] > -1) { cur = memo2[key]; }
        else { cur = g(key, c, memo, memo2); }
        if(cur > biggest) { biggest = cur; }
    }
    biggest += memo[i];
    memo2[i] = biggest;
    return biggest;
}

int main()
{
    int N, M, i, a, b;
    scanf("%d %d", &N, &M);
    Clearing c[N+1];
    for(i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        // goes from a to b
        c[a].addfw(b); // forward goes to GM
        c[b].addbw(a);
    }

    // Recursion
    ll memo[N+1];
    ll memo2[N+1];
    for(i = 0; i < N + 1; i++) { memo[i] = -1; memo2[i] = -1;}
    memo[N] = 1;
    ll trash = f(1, c, memo);

    // Get the path with more options
    cout << g(N, c, memo, memo2) << endl;
}