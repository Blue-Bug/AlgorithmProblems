#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<vector<char>> field(12, vector<char>(6));
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };

vector<pair<int, int>> find_puyo(int i, int j) {
	//bfs�� ���� �ѿ並 ã�´�.
	bool check[12][6]{ false };
	char puyo = field[i][j];
	queue<pair<int, int>> q;
	vector<pair<int, int>> result;
	q.push({ i, j });
	result.push_back({ i,j });

	while (!q.empty()) {
		int cur_i = q.front().first;
		int cur_j = q.front().second;
		q.pop();
		check[cur_i][cur_j] = true;
		for (int i = 0; i < 4; i++) {
			int next_i = cur_i + dir[i][0];
			int next_j = cur_j + dir[i][1];
			if (next_i >= 0 && next_i < 12 && next_j >= 0 && next_j < 6) {
				if (field[next_i][next_j] == puyo && !check[next_i][next_j]) {
					q.push({ next_i,next_j });
					result.push_back({ next_i,next_j });
				}
			}
		}
	}
	return result;
}

int solution() {
	int answer = 0;
	bool flag = true;
	while (flag) {
		unordered_map<int, unordered_set<int>> puyopuyo;
		flag = false;
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				//�����¿�� ������ 4�� �̻��̸� ��������
				char puyo = field[i][j];
				if (puyo == '.') continue;
				vector<pair<int, int>> result = find_puyo(i, j);

				if (result.size() > 3) {
					//�ѿ�ѿ信 �־������.
					flag = true;
					for (auto insert_puyo : result) {
						puyopuyo[insert_puyo.first].insert(insert_puyo.second);
					}
				}
			}
		}

		//�����
		vector<vector<char>> new_field(12);

		for (int j = 0; j < 6; j++) {
			int idx = 11;
			for (int i = 11; i >= 0; i--) {
				if (puyopuyo[i].find(j) == puyopuyo[i].end()) {
					//�ѿ䰡 �������� �ʾҴٸ� �״�� �߰�
					new_field[idx--].push_back(field[i][j]);
				}
			}
			for (int i = idx; i >= 0; i--) {
				new_field[i].push_back('.');
			}
		}
		field = new_field;
		if (flag) {
			answer++;
		}
	}
	return answer;
}

int main() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> field[i][j];
		}
	}
	cout << solution();
}