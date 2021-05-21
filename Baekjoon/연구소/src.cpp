#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, mmax = 0;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
queue<pair<int, int>> q;
vector<vector<int>> graph;
vector<pair<int, int>> comb;
int cnt = 0;

int cnt_area(vector<vector<int>> &graph) {
	queue<pair<int, int>> copy = q;
	int copy_cnt = cnt;
	bool check[8][8]{ false };
	while (!copy.empty()) {
		int row = copy.front().first;
		int col = copy.front().second;
		copy.pop();

		for (int i = 0; i < 4; i++) {
			int nrow = row + dir[i][0];
			int ncol = col + dir[i][1];
			if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m
				&& graph[nrow][ncol]==0 && !check[nrow][ncol]) {
				check[nrow][ncol] = true;
				copy.push({ nrow,ncol });
				copy_cnt--;
			}
		}
	}
	return copy_cnt;
}

void make_wall(int start, int pick,vector<vector<int>> &graph) {
	if (pick == 3) {
		int res = cnt_area(graph);
		if (mmax < res) {
			mmax = res;
		}
		return;
	}
	for (int i = start; i < n*m; i++) {
		if (graph[comb[i].first][comb[i].second] == 0) {
			graph[comb[i].first][comb[i].second] = 1;
			make_wall(i, pick + 1, graph);
			graph[comb[i].first][comb[i].second] = 0;
		}
	}
}

int main() {
	cin >> n >> m;
	graph = vector<vector<int>>(8,vector<int>(8,0));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			comb.push_back({ i,j });
			cin >> graph[i][j];
			if (graph[i][j] == 0) {
				cnt++;
			}
			if (graph[i][j] == 2) {
				q.push({ i,j });
			}
		}
	}
	
	cnt -= 3;
	make_wall(0,0,graph);
	cout << mmax;
}