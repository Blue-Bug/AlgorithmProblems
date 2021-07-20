#include <iostream>
#include <queue>
using namespace std;

int n, m;
char graph[501][501];
int dir[8][2] =
{ {1,1},{-1,1},{1,-1},{-1,-1}, 
	{0,1},{1,0},{0,-1},{-1,0} };

struct node {
	int row, col, rotate;
	char curDir;
};

struct cmp {
	bool operator()(node a, node b) {
		return a.rotate > b.rotate;
	}
};

int bfs() {
	priority_queue<node,vector<node>,cmp> q;
	if (graph[0][0] == '/') {
		q.push({ 0,0,1,'\\'});
	}
	else {
		q.push({ 0,0,0,'\\'});
	}
	bool check[501][501]{ false };
	check[0][0] = true;
	while (!q.empty()) {
		node cur = q.top();
		q.pop();

		if (cur.row == n - 1 && cur.col == m - 1) {
			if (cur.curDir != '\\') {
				return -1;
			}
			return cur.rotate;
		}

		for (int i = 0; i < 8; i++) {
			int nextRow = cur.row + dir[i][0];
			int nextCol = cur.col + dir[i][1];

			if (nextRow < 0 || nextRow >= n) continue;
			if (nextCol < 0 || nextCol >= m) continue;
			if (check[nextRow][nextCol]) continue;

			
			char nextDir = graph[nextRow][nextCol];

			if (cur.curDir == '\\') {
				if ((nextDir == '/' && i == 4) ||
					(nextDir == '/' && i == 5) ||
					(nextDir == '\\' && i == 0) ||
					(nextDir == '\\' && i == 3) || 
					(nextDir == '/' && i == 7) || 
					(nextDir == '/' && i == 6)) {
					//그냥 갈 수 있다.
					q.push({ nextRow,nextCol,cur.rotate,nextDir });
					check[nextRow][nextCol] = true;
				}
				else if (i >= 4) {
					q.push({ nextRow,nextCol,cur.rotate + 1,'/' });
					check[nextRow][nextCol] = true;
				}
				else if (i == 0 || i == 3) {
					q.push({ nextRow,nextCol,cur.rotate + 1,'\\' });
					check[nextRow][nextCol] = true;
				}
				
			}
			else if (cur.curDir == '/') {
				if ((nextDir == '\\' && i == 5) ||
					(nextDir == '\\' && i == 6) ||
					(nextDir == '\\' && i == 7) ||
					(nextDir == '\\' && i == 4) ||
					(nextDir == '/' && i == 2) ||
					(nextDir == '/' && i == 1)) {
					//그냥 갈 수 있다.
					q.push({ nextRow,nextCol,cur.rotate,nextDir });
					check[nextRow][nextCol] = true;
				}
				else if (i >= 4) {
					q.push({ nextRow,nextCol,cur.rotate + 1,'\\' });
					check[nextRow][nextCol] = true;
				}
				else if (i == 1 || i == 2) {
					q.push({ nextRow,nextCol,cur.rotate + 1,'/' });
					check[nextRow][nextCol] = true;
				}
			}
		}
	}
	return -1;
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
		}
	}
	int res = bfs();
	if (res == -1) {
		cout << "NO SOLUTION";
		return 0;
	}
	cout << res;
}