#include <string>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string hole_str = "";

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}
bool compare2(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second < b.second;
}

void rotateKey(vector<vector<int>> &key) {
	//ȸ����Ű��
	vector<int> init_tmp(key.size());
	vector<vector<int>> tmp;
	for (int t = 0; t < key.size(); t++) {
		tmp.push_back(init_tmp);
	}
	//�ӽ� �迭 �ʱ�ȭ

	//�������� 90�� ȸ���ؼ� �� �������� �ִ´�.
	int put_col = key.size()-1;
	for (int i = 0; i < key.size(); i++) {
		for (int j = 0; j < key.size(); j++) {
			tmp[j][put_col] = key[i][j];
		}
		put_col--;
	}
	key = tmp;
}
bool findHoles(vector<vector<int>> &key, int row,int col,int rowSize, int colSize) {
	int init_row = (row - rowSize) + 1;
	int init_col = (col - colSize) + 1;
	string cmpStr = "";

	for (int i = init_row; i <= row; i++) {
		for (int j = init_col; j <= col; j++) {
			cmpStr += (key[i][j]+48);
		}
	}
	if (cmpStr == hole_str) {
		return true;
	}
	return false;
}
	
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	int lockSize = lock.size();
	int keySize = key.size();
	int cutSize = 0;
	//LOCK���� �ڸ���
	//Ȩ���κκ�=> ���� �κ�
	vector<pair<int, int>> holes_pos;
	for (int i = 0; i < lockSize; i++) {
		for (int j = 0; j < lockSize; j++) {
			if (lock[i][j] == 0) {
				holes_pos.push_back({ i,j });
			}
		}
	}
	//segmentfault�� ���� ���� ���ٽ� ���� �߻� -> ���� Ȯ���� ����� 0�϶� �����ؼ� �����ϰ�
	if (holes_pos.size() == 0) {
		return false;
	}

	//�ڸ� �κ� 0,0���� �ø���
	if (holes_pos.size() > 1) {
		sort(holes_pos.begin(), holes_pos.end(), compare);
		for (int i = 1; i < holes_pos.size(); i++) {
			holes_pos[i].first -= holes_pos.front().first;
		}
	}
	holes_pos.front().first = 0;
	int rowSize = holes_pos.back().first + 1;
	//row�� ���� ������� ���� �� �� ���� row�� ��ŭ ���� ����

	if (holes_pos.size() > 1) {
		sort(holes_pos.begin(), holes_pos.end(), compare2);
		for (int i = 1; i < holes_pos.size(); i++) {
			holes_pos[i].second -= holes_pos.front().second;
		}
	}
	holes_pos.front().second = 0;
	int colSize = holes_pos.back().second + 1;
	//col�� ���� ������� ���� �� �Ǿ��� col�� ��ŭ ���� ����
	//LOCK�� Ȩ���� �κ��� KEY�� ���ϱ����� ����� �籸��

	vector<vector<int>> hole;
	for (int i = 0; i < rowSize; i++) {
		vector<int> tmp(colSize, 0);
		hole.push_back(tmp);
	}
	for (auto pos : holes_pos) {
		hole[pos.first][pos.second] = 1;
	}
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			hole_str += (hole[i][j]+48);
		}
	}

	//ȸ���ϸ� �߶󰡸� ��
	int remainCnt = 4;
	while (remainCnt-- > 0) {
		//rowSize = 2, colSize = 3;
		for (int i = rowSize - 1; i < keySize; i++) {
			for (int j = colSize - 1; j < keySize; j++) {
				if (findHoles(key, i, j, rowSize, colSize)) {
					return true;
				}
			}
		}
		//���� �´� Ű�� �����ٸ� ȸ���Ѵ�.
		rotateKey(key);
	}
	return false;
}

int main() {
	solution({ {1,0,0},{0,1,0},{1,0,1} }, { {1,1,1},{0,1,0},{1,0,1} });
	//solution({ {0,0,0},{1,0,1},{0,1,0} }, { {1,1,1},{0,1,0},{1,0,1} });
}