#include <iostream>
#include <vector>
using namespace std;

struct rotateOrder {
	int row, col, offset;
};
int n, m, k;
int answer = 1000000;

vector<vector<int>> graph;
vector<rotateOrder> permVector;
vector<bool> check;
void rotateGraph(int startRow,int startCol, int endRow, int endCol,
	vector<vector<int>>& graph) {
	vector<int> tmp;
	for (int j = startCol; j <= endCol; j++) {
		tmp.push_back(graph[startRow][j]);
	}
	for (int i = startRow + 1; i <= endRow; i++) {
		tmp.push_back(graph[i][endCol]);
	}
	for (int j = endCol - 1; j >= startCol; j--) {
		tmp.push_back(graph[endRow][j]);
	}
	for (int i = endRow - 1; i >= startRow; i--) {
		tmp.push_back(graph[i][startCol]);
	}
	int idx = 0;
	for (int j = startCol + 1; j <= endCol; j++) {
		graph[startRow][j] = tmp[idx++];
	}
	for (int i = startRow + 1; i <= endRow; i++) {
		graph[i][endCol] = tmp[idx++];
	}
	for (int j = endCol - 1; j >= startCol; j--) {
		graph[endRow][j] = tmp[idx++];
	}
	for (int i = endRow - 1; i >= startRow; i--) {
		graph[i][startCol] = tmp[idx++];
	}
}

void permutation(int p, int l,vector<rotateOrder> &pick) {
	if (l == p) {
		vector<vector<int>> graph_copy = graph;

		for (int i = 0; i < l; i++) {
			int startRow = pick[i].row - pick[i].offset;
			int startCol = pick[i].col - pick[i].offset;
			int endRow = pick[i].row + pick[i].offset;
			int endCol = pick[i].col + pick[i].offset;
			while (1) {
				rotateGraph(startRow,startCol,endRow,endCol,graph_copy);
				startRow++;
				startCol++;
				if (startRow == pick[i].row && startCol == pick[i].col) {
					break;
				}
				endRow--;
				endCol--;
			}
		}

		for (int i = 1; i <= n; i++) {
			int res = 0;
			for (int j = 1; j <= m; j++) {
				res += graph_copy[i][j];
			}
			if (res < answer) {
				answer = res;
			}
		}
	}

	for (int i = 0; i < k; i++) {
		if (check[i]) continue;
		check[i] = true;
		pick.push_back(permVector[i]);
		permutation(p, l + 1, pick);
		pick.pop_back();
		check[i] = false;
	}
	return;
}
int main() {
	cin >> n >> m >> k;
	graph = vector<vector<int>>(n+1, vector<int>(m+1));
	check = vector<bool>(k, false);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> graph[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int row, col, offset;
		cin >> row >> col >> offset;
		permVector.push_back({ row,col,offset });
	}
	vector<rotateOrder> pick;
	permutation(k,0,pick);

	
	cout << answer;
}