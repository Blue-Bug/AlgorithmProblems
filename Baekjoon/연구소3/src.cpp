#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
	int row, col, cnt;
};

int n, m;
int answer = 987654321;
int graph[50][50];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<pair<int,int>> comb_list;
queue<node> q;
vector<bool> comb_check;

int cell = 0;
int bfs() {
	int check[50][50];
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			check[i][j] = -1;
		}
	}
	int result = 0;
	int cell_copy = cell;
	while (!q.empty()) {
		int row = q.front().row;
		int col = q.front().col;
		int cnt = q.front().cnt;
		q.pop();

		
		if (check[row][col] != -1) continue;
		check[row][col] = cnt;
		if (result < cnt && graph[row][col] != 2) {
			result = cnt;
		}
		cell_copy--;
		for (int i = 0; i < 4; i++) {
			int nrow = row + dir[i][0];
			int ncol = col + dir[i][1];
			if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < n
				&&check[nrow][ncol]==-1 && graph[nrow][ncol] != 1) {				
					q.push({ nrow,ncol,cnt + 1 });
			}
		}
	}
	if (cell_copy == 0) {
		return result;
	}
	return 987654321;
}

void comb(int start,int n) {
	if (n == m) {
		for (int i = 0; i < comb_check.size(); i++) {
			if (comb_check[i]) {
				q.push({ comb_list[i].first,comb_list[i].second,0 });
			}
		}
		int result = bfs();
		if (result < answer) {
			answer = result;
		}
		return;
	}
	for (int i = start; i < comb_list.size(); i++) {
		comb_check[i] = true;
		comb(i + 1, n + 1);
		comb_check[i] = false;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 2) {
				comb_list.push_back({ i,j });
			}
			if (graph[i][j] != 1) {
				cell++;
			}
		}
	}
	comb_check = vector<bool>(comb_list.size(), false);
	comb(0,0);
	if (answer == 987654321) {
		cout << -1;
		return 0;
	}
	cout << answer;
}