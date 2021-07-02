#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, Q;
vector<vector<pair<int, int>>> edges;
int bfs(int start, int k) {
	queue<int> q;
	q.push(start);
	int cnt = -1;
	vector<bool> check(N + 1, false);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (check[cur]) continue;
		check[cur] = true;
		cnt++;
		for (int i = 0; i < edges[cur].size(); i++) {
			if (edges[cur][i].second >= k) {
				q.push(edges[cur][i].first);
			}
		}
	}
	return cnt;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> N >> Q;
	int n, q, r;
	edges = vector<vector<pair<int, int>>>(N + 1);
	for (int i = 0; i < N - 1; i++) {
		cin >> n >> q >> r;
		edges[n].push_back({ q,r });
		edges[q].push_back({ n,r });
	}
	int k, v;
	for (int i = 0; i < Q; i++) {
		cin >> k >> v;
		cout << bfs(v, k) << '\n';
	}
}