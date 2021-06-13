#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node {
	int dest, cost;
};

int n, m;
int startNode, endNode;
int last = 0;
vector<vector<node>> edges;

bool bfs(int val) {
	queue<int> q;
	vector<bool> check(n + 1, false);
	q.push(startNode);
	check[startNode] = true;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (cur == endNode) {
			return true;
		}
		for (int i = 0; i < edges[cur].size(); i++) {
			if (check[edges[cur][i].dest]) continue;
			if (edges[cur][i].cost < val) continue;

			check[edges[cur][i].dest] = true;
			q.push(edges[cur][i].dest);
		}
	}
	return false;
}

void binary_search() {
	int first = 0;
	while (first <= last) {
		int mid = (first + last) / 2;
		if (bfs(mid)) {
			first = mid + 1;
		}
		else {
			last = mid - 1;
		}
	}

	cout << last;
}

int main() {
	cin >> n >> m;
	edges = vector<vector<node>>(n + 1);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (c > last) {
			last = c;
		}
		edges[a].push_back({ b, c });
		edges[b].push_back({ a, c });
	}

	cin >> startNode >> endNode;

	binary_search();
}