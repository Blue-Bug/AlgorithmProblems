#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int t, k, w, h;
unordered_map<char, int> fighters;
char rader[1000][1000];

int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };

struct node {
	int row, col,cnt;
};
struct cmp {
	bool operator()(node a, node b) {
		return a.cnt > b.cnt;
	}
};

int dijkstra(int r, int c, int ct) {
	priority_queue<node, vector<node>,cmp> pq;
	vector<vector<int>> dist(h, vector<int>(w, -1));
	pq.push({ r, c, ct });

	dist[r][c] = 0;
	while (!pq.empty()) {
		int row = pq.top().row;
		int col = pq.top().col;
		int cnt = pq.top().cnt;
		pq.pop();

		if (row == h - 1 || row == 0 || col == w - 1 || col == 0) {
			return cnt;
		}

		for (int i = 0; i < 4; i++) {
			int nextRow = row + dir[i][0];
			int nextCol = col + dir[i][1];
			
			if (nextRow >= 0 && nextRow < h && nextCol >= 0 && nextCol < w) {
				int cost = fighters[rader[nextRow][nextCol]];
				if (dist[nextRow][nextCol] == -1 || dist[nextRow][nextCol] > dist[row][col] + cost){
					dist[nextRow][nextCol] = dist[row][col] + cost;
					pq.push({ nextRow,nextCol, dist[row][col] + cost });
				}				
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> t;
	while (t-- > 0) {
		int enterprise_row = 0;
		int enterprise_col = 0;
		cin >> k >> w >> h;
		for (int i = 0; i < k; i++) {
			char tmp;
			cin >> tmp;
			cin >> fighters[tmp];
		}
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> rader[i][j];
				if (rader[i][j] == 'E') {
					enterprise_row = i;
					enterprise_col = j;
				}
			}
		}
		cout << dijkstra(enterprise_row, enterprise_col, 0) << '\n';
	}
}