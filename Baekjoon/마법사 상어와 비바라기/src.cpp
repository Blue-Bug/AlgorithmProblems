#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<vector<int>> graph;
unordered_map<int, bool> changedCell;
unordered_map<int, bool> prevCloud;
int n, m, direction, speed, answer = 0;
int dir[8][2] = { {0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} };

void copyWater() {
	vector<tuple<int, int, int>> plusVec;
	for (auto it : changedCell) {
		//대각선은 1,3,5,7
		int cnt = 0;
		for (int j = 1; j < 8; j += 2) {
			int curRow = (it.first / 100) + dir[j][0];
			int curCol = (it.first % 100) + dir[j][1];

			if (curRow < 0 || curRow >= n) continue;
			if (curCol < 0 || curCol >= n) continue;
			if (graph[curRow][curCol] > 0) cnt++;
		}
		if (cnt > 0) {
			plusVec.push_back({ it.first / 100 ,it.first % 100, cnt });
		}
	}
	for (auto it : plusVec) {
		graph[get<0>(it)][get<1>(it)] += get<2>(it);
	}
}

void vanishWater() {
	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int key = (i * 100) + j;
			if (graph[i][j] >= 2 && (changedCell.find(key) == changedCell.end())) {
				graph[i][j] -= 2;
				prevCloud[key] = true;
			}
			result += graph[i][j];
		}
	}
	answer = result;
	changedCell.clear();
}

void makeRainCloud() {
	for (auto it : prevCloud) {
		int cloudRow = ((it.first / 100) + (speed * dir[direction][0])) % n;
		int cloudCol = ((it.first % 100) + (speed * dir[direction][1])) % n;

		if (cloudRow < 0) {
			cloudRow += n;
		}
		if (cloudCol < 0) {
			cloudCol += n;
		}

		graph[cloudRow][cloudCol]++;
		int key = (cloudRow * 100) + cloudCol;
		changedCell[key] = true;
	}
	prevCloud.clear();
}

void rainDance() {
	makeRainCloud();
	copyWater();
	vanishWater();
}


int main() {
	cin >> n >> m;
	graph = vector<vector<int>>(n, vector<int>(n));

	int cloudCell[4][2] = { {n - 2,0},{n - 2,1},{n - 1,0},{n - 1,1} };
	for (int i = 0; i < 4; i++) {
		int key = (cloudCell[i][0] * 100) + cloudCell[i][1];
		prevCloud[key] = true;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> direction >> speed;
		direction -= 1;
		rainDance();
	}

	cout << answer;
}