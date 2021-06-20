#include <iostream>
#include <vector>

using namespace std;
struct moveVal {
	int row, col;
	double ratio;
};
int n;
vector<vector<int>> graph;
//현재 내자리가 기준
vector<vector<moveVal>> moveVec(4);

void moveVecSet() {
	//0은 왼쪽, 1은 오른쪽, 2는 위, 3은 아래
	moveVec[0] = {{ -1,0,0.01 }, {1,0,0.01}, {-1,-1,0.07}, {-2,-1,0.02}, 
					{1,-1,0.07}, {2,-1,0.02}, {-1,-2,0.1}, {1,-2,0.1},
					{0,-3,0.05} };
	moveVec[1] = { { -1,0,0.01 }, {1,0,0.01}, {-1,1,0.07}, {-2,1,0.02},
					{1,1,0.07}, {2,1,0.02}, {-1,2,0.1}, {1,2,0.1},
					{0,3,0.05} };
	moveVec[2] = { { 0,-1,0.01 }, {0,1,0.01}, {-1,-1,0.07}, {-1,-2,0.02},
					{-1,1,0.07}, {-1,2,0.02}, {-2,-1,0.1}, {-2,1,0.1},
					{-3,0,0.05} };
	moveVec[3] = { { 0,-1,0.01 }, {0,1,0.01}, {1,-1,0.07}, {1,-2,0.02},
					{1,1,0.07}, {1,2,0.02}, {2,-1,0.1}, {2,1,0.1},
					{3,0,0.05} };
}
int moveLeft(int moveCnt,int &row, int &col) {
	int result = 0;
	while (moveCnt--) {
		int forA = graph[row][col - 1];
		for (auto it : moveVec[0]) {
			int nextRow = row + it.row;
			int nextCol = col + it.col;
			if (nextRow < 0 || nextRow >= n ||
				nextCol < 0 || nextCol >= n) {
				result += floor(graph[row][col - 1] * it.ratio);
				forA -= floor(graph[row][col - 1] * it.ratio);
			}
			else {
				graph[nextRow][nextCol] += floor(graph[row][col - 1] * it.ratio);
				forA -= floor(graph[row][col - 1] * it.ratio);
			}
		}
		if (col - 2 < 0) {
			result += forA;
		}
		else {
			graph[row][col - 2]+= forA;
		}
		graph[row][col - 1] = 0;
		col--;
	}
	return result;
}
int moveRight(int moveCnt, int &row, int &col) {
	int result = 0;
	while (moveCnt--) {
		int forA = graph[row][col + 1];
		for (auto it : moveVec[1]) {
			int nextRow = row + it.row;
			int nextCol = col + it.col;
			if (nextRow < 0 || nextRow >= n ||
				nextCol < 0 || nextCol >= n) {
				result += floor(graph[row][col + 1] * it.ratio);
				forA -= floor(graph[row][col + 1] * it.ratio);
			}
			else {
				graph[nextRow][nextCol] += floor(graph[row][col + 1] * it.ratio);
				forA -= floor(graph[row][col + 1] * it.ratio);
			}
		}
		if (col + 2 >= n) {
			result += forA;
		}
		else {
			graph[row][col + 2] += forA;
		}
		graph[row][col + 1] = 0;
		col++;
	}
	return result;
}
int moveDown(int moveCnt, int &row, int &col) {
	int result = 0;
	while (moveCnt--) {
		int forA = graph[row + 1][col];
		for (auto it : moveVec[3]) {
			int nextRow = row + it.row;
			int nextCol = col + it.col;
			if (nextRow < 0 || nextRow >= n ||
				nextCol < 0 || nextCol >= n) {
				result += floor(graph[row+1][col] * it.ratio);
				forA -= floor(graph[row+1][col] * it.ratio);
			}
			else {
				graph[nextRow][nextCol] += floor(graph[row + 1][col] * it.ratio);
				forA -= floor(graph[row + 1][col] * it.ratio);
			}
		}
		if (row + 2 >= n) {
			result += forA;
		}
		else {
			graph[row + 2][col] += forA;
		}
		graph[row + 1][col] = 0;
		row++;
	}
	return result;
}
int moveUp(int moveCnt, int &row, int &col) {
	int result = 0;
	while (moveCnt--) {
		int forA = graph[row - 1][col];
		for (auto it : moveVec[2]) {
			int nextRow = row + it.row;
			int nextCol = col + it.col;
			if (nextRow < 0 || nextRow >= n ||
				nextCol < 0 || nextCol >= n) {
				result += floor(graph[row - 1][col] * it.ratio);
			}
			else {
				graph[nextRow][nextCol] += floor(graph[row - 1][col] * it.ratio);
			}
			forA -= floor(graph[row - 1][col] * it.ratio);
		}
		if (row - 2 < 0) {
			result += forA;
		}
		else {
			graph[row - 2][col] += forA;
		}
		graph[row - 1][col] = 0;
		row--;
	}
	return result;
}

int countSand(int mid){
	int result = 0;
	int row = mid;
	int col = mid;
	int moveCnt = 1;
	while (1) {
		if (moveCnt == n) {
			moveCnt--;
		}
		//왼쪽이동(1->3->5 .. ->n-1) 마지막은 하나뺌
		result += moveLeft(moveCnt, row, col);
		
		if (moveCnt == n - 1) {
			return result;
		}

		//아래이동(1->3->5)
		result += moveDown(moveCnt, row, col);
		moveCnt++;

		//오른쪽이동(2->4->6)
		result += moveRight(moveCnt, row, col);

		//위쪽이동(2->4->6)
		result += moveUp(moveCnt, row, col);
		moveCnt++;
	}
}

int main() {
	cin >> n;
	graph = vector<vector<int>>(n, vector<int>(n));
	moveVecSet();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}
	cout << countSand(n / 2);
}