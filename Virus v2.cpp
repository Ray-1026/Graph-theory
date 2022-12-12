#include<bits/stdc++.h>
using namespace std;

struct Status {
	int time, status;
	Status() :time(-1), status(0) {};
};

struct Edge {
	int to, weight;
};

void dfs(vector<vector<Edge>>& edge, vector<Status>& stat, int point, int T, bool virus) {
	if (stat[point].time > T)
		return;
	for (Edge i : edge[point]) {
		int w = 1;
		if (virus)
			w = i.weight;
		if (stat[i.to].time == -1) {
			stat[i.to].status = stat[point].status;
			stat[i.to].time = w + stat[point].time;
			dfs(edge, stat, i.to, T, virus);
		}
		else {
			if (stat[i.to].time > i.weight + stat[point].time) {
				stat[i.to].status = stat[point].status;
				stat[i.to].time = w + stat[point].time;
				dfs(edge, stat, i.to, T, virus);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, p, q, t, T, count = 0;
	cin >> n >> m >> p >> q >> t >> T;
	vector<Status> stat(n + 1);
	vector<vector<Edge>> edge(n + 1);
	for (int i = 0; i < m; i++) {
		Edge temp;
		int from;
		cin >> from >> temp.to >> temp.weight;
		edge[from].emplace_back(temp);
	}
	for (int i = 0; i < p; i++) {
		int num;
		cin >> num;
		stat[num].status = -1;
		stat[num].time = 0;
		dfs(edge, stat, num, T, 1);
	}
	for (int i = 0; i < q; i++) {
		int num;
		cin >> num;
		if (stat[num].time == -1 || stat[num].time >= t) {
			stat[num].status = 1;
			stat[num].time = t;
			dfs(edge, stat, num, T, 0);
		}
	}
	for (Status i : stat) {
		if (i.status == -1)
			count++;
	}
	cout << count << "\n";
}