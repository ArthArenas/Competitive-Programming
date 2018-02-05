#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<unsigned int, unsigned int> ii;

struct City
{
    City(): children(0), parent(0), visited(false) {}
    unsigned int children;
    unsigned int parent;
    bool visited;
    void add(unsigned int index) { v.push_back(index); }
    vector<unsigned int> v;
};

int main()
{
    // Read and set data
    unsigned int N, i, a, b;
    scanf("%d", &N);
    City c[N + 1];
    unsigned int d[N];
    ii r[N - 1];
    ii road;
    for(i = 0; i < N - 1; i++){
        scanf("%d %d", &a, &b);
        c[a].add(b);
        c[b].add(a);
        road.first = a;
        road.second = b;
        r[i] = road;
    }
    // Topological Sort
    unsigned int s, j, n;
    queue<unsigned int> q;
    q.push(1);
    d[N-1] = 1;
    unsigned int track = N - 2;
    unsigned int parent;
    while(!q.empty()){
        j = q.front();
        q.pop();
        c[j].visited = true;
        s = c[j].v.size();
        for(i = 0; i < s; i++){
            if(!c[c[j].v[i]].visited) {
                q.push(c[j].v[i]);
                d[track] = c[j].v[i];
                track--;
                c[c[j].v[i]].parent = j;
            }
        }
    }
    for(i = 0; i < N; i++){
        parent = c[d[i]].parent;
        c[parent].children += c[d[i]].children + 1;
    }
    for(i = 0; i < N - 1; i++){
        if(c[r[i].first].parent == r[i].second) { n = c[r[i].first].children;}
        else { n = c[r[i].second].children; }
        n++;
        printf("%u\n", n * (N - n));
    }
}