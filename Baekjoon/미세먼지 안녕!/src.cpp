#include <iostream>
#include <vector>
using namespace std;

int r, c, t;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
vector<vector<int>> graph;
vector<vector<int>> graph_copy;
int ap_pos[2][2];

void upperSide(int upper_row,int upper_col) {
	vector<int> tmp;

	for (int j = upper_col + 1; j < c; j++) {
		tmp.push_back(graph[upper_row][j]);
		graph[upper_row][j] = 0;
	}
	for (int i = upper_row - 1; i >= 0; i--) {
		tmp.push_back(graph[i][c - 1]);
		graph[i][c - 1] = 0;
	}
	for (int j = c - 2; j >= 0; j--) {
		tmp.push_back(graph[0][j]);
		graph[0][j] = 0;
	}
	for (int i = 1; i < upper_row - 1; i++) {
		tmp.push_back(graph[i][0]);
		graph[i][0] = 0;
	}

	int idx = 0;
	for (int j = upper_col + 2; j < c; j++) {
		graph[upper_row][j] = tmp[idx++];
	}
	for (int i = upper_row - 1; i >= 0; i--) {
		graph[i][c - 1] = tmp[idx++];
	}
	for (int j = c - 2; j >= 0; j--) {
		graph[0][j] = tmp[idx++];
	}
	for (int i = 1; i <= upper_row - 1; i++) {
		graph[i][0] = tmp[idx++];
	}
}

void lowerSide(int lower_row,int lower_col) {
	vector<int> tmp;

	for (int j = lower_col + 1; j < c; j++) {
		tmp.push_back(graph[lower_row][j]);
		graph[lower_row][j] = 0;
	}
	for (int i = lower_row + 1; i < r; i++) {
		tmp.push_back(graph[i][c - 1]);
		graph[i][c - 1] = 0;
	}
	for (int j = c - 2; j >= 0; j--) {
		tmp.push_back(graph[r-1][j]);
		graph[r-1][j] = 0;
	}
	for (int i = r - 2; i >= lower_row + 2; i--) {
		tmp.push_back(graph[i][0]);
		graph[i][0] = 0;
	}

	int idx = 0;
	for (int j = lower_col + 2; j < c; j++) {
		graph[lower_row][j] = tmp[idx++];
	}
	for (int i = lower_row + 1; i < r; i++) {
		graph[i][c - 1] = tmp[idx++];
	}
	for (int j = c - 2; j >= 0; j--) {
		graph[r-1][j] = tmp[idx++];
	}
	for (int i = r - 2; i >= lower_row + 1; i--) {
		graph[i][0] = tmp[idx++];
	}
}

void activateAirPurifier() {
	int upper_row = ap_pos[0][0];
	int upper_col = ap_pos[0][1];
	int lower_row = ap_pos[1][0];
	int lower_col = ap_pos[1][1];

	upperSide(upper_row, upper_col);
	lowerSide(lower_row, lower_col);
}

void spreadDust(int row, int col) {
	int cnt = 0;
	int val = graph[row][col] / 5;

	for (int i = 0; i < 4; i++) {
		int nextRow = row + dir[i][0];
		int nextCol = col + dir[i][1];
		if (nextRow < 0 || nextRow >= r) continue;
		if (nextCol < 0 || nextCol >= c) continue;
		if (graph[nextRow][nextCol] != -1) {
			cnt += val;
			graph_copy[nextRow][nextCol] += val;
		}
	}

	graph_copy[row][col] -= cnt;
}

int main() {
	cin >> r >> c >> t;
	graph = vector<vector<int>>(r, vector<int>(c));
	int idx = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == -1) {
				ap_pos[idx][0] = i;
				ap_pos[idx++][1] = j;
			}
		}
	}
	
	while (t--) {
		graph_copy = graph;
		//미세먼지 확산
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (graph[i][j] > 0) {
					spreadDust(i, j);
				}
			}
		}
		graph = graph_copy;
		//공기청정기 작동
		activateAirPurifier();
	}

	int answer = 0;
	//미세먼지 체크
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (graph[i][j] != -1) {
				answer += graph[i][j];
			}
		}
	}
	cout << answer;
}