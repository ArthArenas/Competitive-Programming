#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<int>> adjList;

vector<int> levels;

int LCA(adjList& aL, int a, int b) {
	// may have several ancestors
	vector<bool> visited((int)aL.size(), false);
	queue<int> q;
	q.push(a); visited[a] = true;
	q.push(b); visited[b] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto it = aL[u].begin(); it != aL[u].end(); it++) {
			if (levels[*it] && levels[*it] == levels[u] - 1) {
				if (visited[*it]) return *it;
				else {
					q.push(*it);
					visited[*it] = true;
				}
			}
		}
	}
	return -1;
}

bool BFS(adjList& aL, int s) {
	queue<int> q;
	q.push(s);
	levels[s] = 1;
	int u;
	bool done = false;
	while (!q.empty() && !done) {
		u = q.front();
		q.pop();
		for (auto it = aL[u].begin(); it != aL[u].end() && !done; it++) {
			if (levels[*it] && levels[*it] == levels[u] + 1) {
				// we're pointing at it again, so we run the LCA
				// check the nodes subject to LCA check
				// which are all nodes from the lower level with conenction
				// to *it, that are not u
				for (auto itt = aL[*it].begin(); itt != aL[*it].end(); itt++) {
					if (levels[*itt] == levels[*it] - 1 && levels[*itt] && *itt != u) {
						int lca = LCA(aL, u, *itt);
						done = ((levels[*it] - levels[lca]) % 3 != 0);
					}
				}

			}
			else if (!levels[*it]) {
				levels[*it] = levels[u] + 1;
				q.push(*it);
			}
		}
	}
	return !done;
}

int main()
{
	int V, E;
	scanf("%d %d", &V, &E);

	levels.assign(V, 0);
	adjList aL(V);

	int u, v;
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &u, &v);
		aL[u].push_back(v);
		aL[v].push_back(u);
	}

	// assign levels
	bool done = false;
	for (int i = 0; i < V && !done; i++) {
		if (!levels[i]) {
			done = !BFS(aL, i);
		}
	}
	string result = done ? "no" : "yes";
	cout << result << endl;
	return 0;
}