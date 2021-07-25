#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int r, c, n;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
char graph[101][101];
vector<vector<int>> check;
int floatedCluster = -1;

void printMineral() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << graph[i][j];
		}
		cout << '\n';
	}
}
void dropCluster() {
	int goDown = 987654321;
	for (int j = 0; j < c; j++) {
		//��� ������ floatedCluster�� ���� ���� ���� ���� ã��
		int tmp = -1;
		int cnt = 0;
		for (int i = 0; i < r; i++) {
			if (check[i][j] == floatedCluster) {
				tmp = i;
			}
		}
		if (tmp == -1) continue;
		//�󸶳� �Ʒ��� ������ �� �ִ����� �����´�.
		for (int i = tmp + 1; i < r; i++){
			if (graph[i][j] == '.') {
				cnt++;
			}
			else {
				break;
			}
		}
		goDown = min(goDown, cnt);
	}
	//������ �� ���ٸ� �׳� ����
	if (goDown == 987654321) return;
	//������ ���� �ٲٸ� �սǵ�
	for (int i = r-1; i >= 0; i--) {
		for (int j = 0; j < c; j++) {
			if (check[i][j] == floatedCluster) {
				graph[i][j] = '.';
				graph[i + goDown][j] = 'x';
			}
		}
	}

}

bool bfs(int row,int col,int idx) {
	if (check[row][col] != 0) {
		return false;
	}
	queue<pair<int, int>> q;
	q.push({ row,col });
	check[row][col] = idx;
	bool floated = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		if (cur.first == r - 1) {
			floated = false;
		}
		for (int i = 0; i < 4; i++) {
			int nextRow = cur.first + dir[i][0];
			int nextCol = cur.second + dir[i][1];

			if (nextRow < 0 || nextRow >= r) continue;
			if (nextCol < 0 || nextCol >= c) continue;
			if (graph[nextRow][nextCol] != 'x') continue;
			
			if (check[nextRow][nextCol] != 0) continue;
			check[nextRow][nextCol] = idx;

			q.push({ nextRow,nextCol });
		}
	}
	if (floated) {
		floatedCluster = idx;
	}
	return true;
}

void breakMineral(int throwHeight,bool direction) {
	if (direction) {
		for (int j = 0; j < c; j++) {
			if (graph[r - throwHeight][j] == 'x') {
				graph[r - throwHeight][j] = '.';
				return;
			}
		}
	}
	else {
		for (int j = c-1; j >= 0 ; j--) {
			if (graph[r - throwHeight][j] == 'x') {
				graph[r - throwHeight][j] = '.';
				return;
			}
		}
	}
}

void calCluster() {
	int index = 1;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (graph[i][j] == 'x') {
				if (bfs(i, j, index)) {
					index++;
				}
				if (floatedCluster != -1) {
					//����߸�
					dropCluster();
					//�ʱ�ȭ �׻� ��������
					floatedCluster = -1;
					return;
				}
			}
		}
	}
}


int main() {
	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> graph[i][j];
		}
	}
	cin >> n;
	int throwHeight;
	bool flag = true;
	for (int i = 0; i < n; i++) {
		cin >> throwHeight;
		breakMineral(throwHeight, flag);
		//�ϳ��� Ŭ�����͸� ���������� ������ ����������
		check = vector<vector<int>>(r, vector<int>(c, 0));
		calCluster();
		flag = !flag;
	}
	printMineral();
}