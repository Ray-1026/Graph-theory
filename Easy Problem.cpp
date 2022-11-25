#include<bits/stdc++.h>
#define vi vector<int>
using namespace std;

void dfs(vector<vi>& adj, vi& visit, vi& p, vi& h, int at) {
	for (int i : adj[at]) {
		if (!visit[i]) {
			p[i] = at;
			visit[i] = 1;
			dfs(adj, visit, p, h, i);
			h[at] = max(h[i] + 1, h[at]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie();
	int n;
	cin >> n;
	vector<vi> adj;
	adj.resize(n + 1, vi());
	vi visit(n + 1, 0), p(n + 1, -1), h(n + 1, 0);
	for (int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	visit[1] = 1;
	dfs(adj, visit, p, h, 1);
	for (int i = 1; i <= n; i++)
		cout << h[i] << " " << p[i] << "\n";
}