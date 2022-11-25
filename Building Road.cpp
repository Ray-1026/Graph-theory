#include<bits/stdc++.h>
typedef long long int ll;
#define vi vector<int>
using namespace std;

struct Edge {
	int u, v, w;
};

inline bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

inline int find(vi& p, int x) {
	if (p[x] == x)
		return x;
	else {
		p[x] = find(p, p[x]);
		return p[x];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie();
	int q;
	cin >> q;
	for (; q; q--) {
		int n, m, idx = 0;
		cin >> n >> m;
		vi cost(n, 0), p(n);
		vector<Edge> edge;
		edge.reserve(n + m);
		ll sum = 0;
		for (int i = 0; i < n; i++) {
			p[i] = i;
			cin >> cost[i];
			if (cost[idx] > cost[i])
				idx = i;
		}
		for (int i = 0; i < n; i++) {
			if (i != idx)
				edge.push_back({ idx, i, cost[idx] + cost[i] });
		}
		for (int i = 0; i < m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			edge.push_back({ --u, --v, w });
		}
		sort(edge.begin(), edge.end(), cmp);
		for (Edge i : edge) {
			int x = find(p, i.u), y = find(p, i.v);
			if (x != y) {
				p[y] = x;
				sum += i.w;
			}
		}
		cout << sum << "\n";
	}
}