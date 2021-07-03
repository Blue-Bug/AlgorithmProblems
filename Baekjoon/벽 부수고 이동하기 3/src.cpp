#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
//[n][m][¹ã³·][ºÎ¼øº®]
bool check[1001][1001][2][11]{ false };
vector<vector<char>> graph;
struct node {
	int row, col, night, cnt, remover;
};

int bfs() {
	queue<node> q;
	q.push({ 0, 0 ,0, 1, k });

	while (!q.empty()) {
		node cur = q.front();
		q.pop();

		if (cur.row == n - 1 && cur.col == m - 1) {			
			return cur.cnt;
		}

		if (check[cur.row][cur.col][cur.night][cur.remover]) continue;
		check[cur.row][cur.col][cur.night][cur.remover] = true;

		for (int i = 0; i < 4; i++) {
			int nextRow = cur.row + dir[i][0];
			int nextCol = cur.col + dir[i][1];

			if (nextRow < 0 || nextRow >= n) continue;
			if (nextCol < 0 || nextCol >= m) continue;

			if (graph[nextRow][nextCol] == '1' && cur.remover > 0 && 
				!check[nextRow][nextCol][cur.night][cur.remover]) {
				if (cur.night == 1) {
					//¹ã¿¡¼­ ³·À¸·Î¸¸ ¹Ù²ÛÃ¤·Î push
					q.push({ cur.row,cur.col,0,cur.cnt + 1,cur.remover });
				}
				else {
					q.push({ nextRow,nextCol,1,cur.cnt + 1,cur.remover - 1 });
				}
			}
			else if (graph[nextRow][nextCol] == '0' && 
				!check[nextRow][nextCol][cur.night][cur.remover]) {
				if (cur.night == 1) {
					q.push({ nextRow,nextCol,0,cur.cnt + 1,cur.remover });
				}
				else {
					q.push({ nextRow,nextCol,1,cur.cnt + 1,cur.remover });
				}
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m >> k;
	
	graph = vector<vector<char>>(n, vector<char>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
		}
	}
	cout << bfs();
}