#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

struct pos {
	int row, col;
};
struct groupSt {
	int row, col, part;
};
struct partsInfo {
	int row, col, rainbow, cnt, part;
};
int n, m, score = 0;
int graph[20][20];
vector<vector<int>> check;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };


bool compare(partsInfo a, partsInfo b) {
	//(ũ�� > ������ ��� �� > ���� ��� ���� ū�� > ���� ��� ���� ū��)
	if (a.cnt == b.cnt) {
		if (a.rainbow == b.rainbow) {
			if (a.row == b.row) {
				return a.col > b.col;
			}
			return a.row > b.row;
		}
		return a.rainbow > b.rainbow;
	}
	return a.cnt > b.cnt;
}

void groupingBlock(int row, int col,int part,
	unordered_map<int, partsInfo>& partsInfos,
	unordered_map<int, vector<pos>>& partsPos) {
	queue<groupSt> q;
	q.push({ row, col, part });

	int rainbow = 0;
	int cnt = 0;
	int curBlock = graph[row][col];
	vector<vector<int>> check_copy;
	check_copy = check;

	while(!q.empty()){
		int curRow = q.front().row;
		int curCol = q.front().col;
		int curPart = q.front().part;
		q.pop();
		if (check_copy[curRow][curCol] != 0) {
			if (!(check_copy[curRow][curCol] != curPart && graph[curRow][curCol] == 0)) {
				continue;
			}
		}
		partsPos[curPart].push_back({ curRow,curCol });
		if (graph[curRow][curCol] == 0) {
			rainbow++;
		}
		check_copy[curRow][curCol] = curPart;
		cnt++;

		for (int i = 0; i < 4; i++) {
			int nextRow = curRow + dir[i][0];
			int nextCol = curCol + dir[i][1];
			if (nextRow < 0 || nextRow >= n) continue;
			if (nextCol < 0 || nextCol >= n) continue;
			if (graph[nextRow][nextCol] > -1 &&
				(graph[nextRow][nextCol] == curBlock
				|| graph[nextRow][nextCol] == 0)) {
				q.push({ nextRow,nextCol,curPart });
			}
		}
	}
	//������ 2 �̻��̾�� ��
	if (cnt >= 2) {
		partsInfos[part].row = row;
		partsInfos[part].col = col;
		partsInfos[part].rainbow = rainbow;
		partsInfos[part].cnt = cnt;
		partsInfos[part].part = part;
		check = check_copy;
	}
	return;
}

void applyGravity(int startRow,int endRow,int startCol, int endCol) {
	for (int j = startCol; j <= endCol; j++) {
		vector<int> tmp;
		int startIdx = startRow;
		int endIdx = endRow;
		for (int i = startRow; i >= endRow; i--) {
			if (graph[i][j] == -1) {
				applyGravity(i - 1, endRow, j,j);
				endIdx = i + 1;
				break;
			}
			if (graph[i][j] == -2) continue;
			tmp.push_back(graph[i][j]);
		}
		
		for (auto it : tmp) {
			graph[startIdx--][j] = it;
		}
		for (int i = startIdx; i >= endIdx; i--) {
			graph[i][j] = -2;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}
	while (1) {
		//part��ȣ�� Ű��, part �������� ������ ����
		unordered_map<int, partsInfo> partsInfos;
		//part��ȣ�� ��ġ�� ����
		unordered_map<int, vector<pos>> partsPos;
		//���� ū part�� ã�� ���� ����
		vector<partsInfo> partsSort;
		check = vector<vector<int>>(20, vector<int>(20, 0));

		//��� �׷�ȭ
		int part = 1;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][j] > 0) {
					groupingBlock(i, j, part++, partsInfos, partsPos);
				}
			}
		}

		if (partsInfos.empty()) {
			cout << score;
			return 0;
		}

		//���� ū ��� ã��
		for (auto it : partsInfos) {
			partsSort.push_back(it.second);
		}
		sort(partsSort.begin(), partsSort.end(), compare);
		int biggestPart = partsSort.front().part;

		//���� ū ��� �׷� ���� �� ���� ȹ��
		for (auto it : partsPos[biggestPart]) {
			graph[it.row][it.col] = -2;
		}
		score += pow(partsPos[biggestPart].size(), 2);

		//�߷� �ۿ�
		applyGravity(n-1, 0,0,n-1);

		//�ݽð� ȸ��
		vector<int> tmp;
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < n; i++) {
				tmp.push_back(graph[i][j]);
			}
		}
		int idx = 0;
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				graph[i][j] = tmp[idx++];
			}
		}
		//�߷� �ۿ�
		applyGravity(n - 1, 0, 0, n - 1);
	}
}