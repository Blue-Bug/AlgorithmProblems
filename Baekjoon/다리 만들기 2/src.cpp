#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node {
	int num, cost;
};

struct cmp {
	bool operator()(node a, node b) {
		return a.cost > b.cost;
	}
};
int n, m;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
vector<vector<node>> bridge(7);
int board[10][10];
vector<vector<bool>> check;

void bfs(int row, int col, int idx) {
	queue<pair<int, int>> q;
	q.push({ row,col });
	int color = board[row][col];
	check[row][col] = true;
	board[row][col] = idx;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int nextRow = cur.first + dir[i][0];
			int nextCol = cur.second + dir[i][1];
			if (nextRow < 0 || nextRow >= n) continue;
			if (nextCol < 0 || nextCol >= m) continue;
			if (board[nextRow][nextCol] == color && !check[nextRow][nextCol]) {
				check[nextRow][nextCol] = true;
				board[nextRow][nextCol] = idx;
				q.push({ nextRow,nextCol });
			}
		}
	}
}

void find_bridge(int row,int col) {
	int color = board[row][col];
	for (int i = 0; i < 4; i++) {
		//경계선이나 다른 섬을 만날때까지
		int nextRow = row, nextCol = col;
		int cost = 0;
		while (1) {
			nextRow += dir[i][0];
			nextCol += dir[i][1];
			if (nextRow < 0 || nextRow >= n) break;
			if (nextCol < 0 || nextCol >= m) break;
			if (board[nextRow][nextCol] == color) break;
			if (board[nextRow][nextCol] > 0) {
				if (cost >= 2) {
					bridge[board[nextRow][nextCol]].push_back({ color,cost });
					bridge[color].push_back({ board[nextRow][nextCol], cost });
				}
				break;
				// 다리 조건에서 벗어남
			}
			cost++;
		}
	}
}

int primMST(int start,int idx) {
	priority_queue<node, vector<node>, cmp> pq;
	pq.push({ start, 0 });
	bool check[7]{ false };
	int result = 0;
	while (!pq.empty()) {
		node cur = pq.top();
		pq.pop();
		if (check[cur.num]) continue;
		check[cur.num] = true;
		result += cur.cost;
		for (int i = 0; i < bridge[cur.num].size(); i++) {
			node next = bridge[cur.num][i];
			pq.push({ next.num,next.cost });
		}
	}
	for (int i = 1; i < idx; i++) {
		//연결이 안됐다면
		if (!check[i]) return -1;
	}
	return result;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}
	//bfs로 영역화
	check = vector<vector<bool>>(n, vector<bool>(m));
	int idx = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 1 && !check[i][j]) {
				bfs(i, j, idx++);
			}
		}
	}
	//다리찾기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] >= 1) {
				find_bridge(i,j);
			}
		}
	}
	//MST를 만들수 없다면 -1
	for (int i = 1; i < idx; i++) {
		if (bridge[i].empty()) {
			cout << -1;
			return 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] >= 1) {
				cout << primMST(board[i][j],idx);
				return 0;
			}
		}
	}
}