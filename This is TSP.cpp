#include<bits/stdc++.h>
using namespace std;

int n, full, distances[20][20];
vector<vector<int>> dp, path;

inline int overlap(string& a, string& b) {
	for (int i = 0; i < a.size(); i++) {
		if (b.find(a.substr(i)) == 0)
			return b.size() - (a.size() - i);
	}
	return b.size();
}

int tsp(vector<vector<int>>& dp, int now, int at) {
	if (now == full)
		return 0;
	if (dp[now][at] < 1e9)
		return dp[now][at];
	int buff;
	for (int i = 0; i < n; i++) {
		if (!(now & (1 << i))) {
			buff = distances[at][i] + tsp(dp, now + (1 << i), i);
			if (dp[now][at] > buff) {
				dp[now][at] = buff;
				path[now][at] = i;
			}
		}
	}
	return dp[now][at];
}

string backtrack(vector<string>& str, int start) {
	int at = start, now = (1 << at), neighbor = path[now][at];
	string res = str[at];
	while (neighbor != -1) {
		res += str[neighbor].substr(str[neighbor].size() - distances[at][neighbor]);
		now += (1 << neighbor);
		at = neighbor;
		neighbor = path[now][at];
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int cnt = 0;
	cin >> n;
	vector<string> str;
	str.reserve(n);
	string shortest, temp;
	shortest.resize(6000);
	for (int i = 0; i < n; i++) {
		bool flag = 1;
		cin >> temp;
		for (int j = 0; j < str.size(); j++) {
			if (str[j].size() > temp.size()) {
				if (str[j].find(temp) != string::npos) {
					cnt++;
					flag = 0;
					break;
				}
			}
			else {
				if (temp.find(str[j]) != string::npos) {
					cnt++;
					str.erase(str.begin() + j);
					j--;
				}
			}
		}
		if (flag)
			str.emplace_back(temp);
	}
	sort(str.begin(), str.end());
	n -= cnt;
	full = (1 << n) - 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			distances[i][j] = overlap(str[i], str[j]);
	}
	for (int i = 0; i < n; i++) {
		dp.assign((1 << n), vector<int>(n, 1e9));
		path.assign((1 << n), vector < int >(n, -1));
		tsp(dp, 1 << i, i);
		string super = backtrack(str, i);
		if (shortest.size() > super.size())
			shortest = super;
		else if (shortest.size() == super.size() && shortest > super)
			shortest = super;
	}
	cout << shortest;
}