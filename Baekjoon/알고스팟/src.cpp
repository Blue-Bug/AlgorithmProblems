#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
vector<vector<char>> graph;

struct node {
	int row, col, cnt;
};

int bfs() {
	vector<vector<int>> check(m, vector<int>(n, 987654321));
	queue<node> q;
	q.push({ 0,0,0 });
	while (!q.empty()) {
		node cur = q.front();
		q.pop();

		if (check[cur.row][cur.col] <= cur.cnt) continue;
		check[cur.row][cur.col] = cur.cnt;

		for (int i = 0; i < 4; i++) {
			int nextRow = dir[i][0] + cur.row;
			int nextCol = dir[i][1] + cur.col;
			int nextCnt = cur.cnt;
			if (nextRow < 0 || nextRow >= m) continue;
			if (nextCol < 0 || nextCol >= n) continue;
			if (graph[nextRow][nextCol] == '1') {
				nextCnt++;
			}
			q.push({ nextRow,nextCol,nextCnt });
		}
	}
	return check[m - 1][n - 1];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	graph = vector<vector<char>>(m, vector<char>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}
	cout << bfs();
}