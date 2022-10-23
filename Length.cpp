#include<bits/stdc++.h>
#define vi vector<int>
#define vii vector<vector<int>>
using namespace std;

void dfs(vii& adj_list, vii& p, vi& dep, int n) {
	for (auto& it : adj_list[n]) {
		if (dep[it] != -1)
			continue;
		dep[it] = dep[n] + 1;
		p[it][0] = n;
		dfs(adj_list, p, dep, it);
	}
}

int lca(vi& dep, vii& p, int a, int b) {
	int res = dep[a] + dep[b];
	if (dep[a] > dep[b])
		swap(a, b);
	if (dep[a] != dep[b]) {
		int diff = dep[b] - dep[a];
		for (int i = 0; diff; i++) {
			if (diff & 1)
				b = p[b][i];
			diff >>= 1;
		}
	}
	if (a == b)
		return res - dep[a] * 2;
	for (int i = 19; i >= 0; i--) {
		if (p[a][i] != p[b][i]) {
			a = p[a][i];
			b = p[b][i];
		}
	}
	return res - dep[p[a][0]] * 2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q, u, v, x, y;
	cin >> n;
	vi dep(n + 1, -1);
	vii p(n + 1, vector<int>(20, 0)), adj_list(n + 1);
	adj_list[1].emplace_back(0);
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y;
		adj_list[x].emplace_back(y);
		adj_list[y].emplace_back(x);
	}
	dep[0] = 0;
	dep[1] = 1;
	dfs(adj_list, p, dep, 1);
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++)
			p[j][i] = p[p[j][i - 1]][i - 1];
	}
	cin >> q;
	for (; q > 0; q--) {
		cin >> u >> v;
		cout << lca(dep, p, u, v) << "\n";
	}
}