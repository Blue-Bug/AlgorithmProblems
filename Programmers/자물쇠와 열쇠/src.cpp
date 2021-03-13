#include <string>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string hole_str = "";

void rotateKey(vector<vector<int>> &key) {
	//key�� ȸ����Ű��
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

	//key���� rowSize, colSize ũ�⸸ŭ �߶󳻸� string�� �߰�
	for (int i = init_row; i <= row; i++) {
		for (int j = init_col; j <= col; j++) {
			cmpStr += (key[i][j]+48);
		}
	}
	//lock���� ���� ũ��� �����ϰ� Ȩ ���� �κ��� ������Ų ���ڿ��� ��
	if (cmpStr == hole_str) {
		return true;
	}
	return false;
}
	
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	int lockSize = lock.size();
	int keySize = key.size();

	int rowfirst = -1;
	int rowlast = 0;
	int colfirst = lockSize;
	int collast = 0;

	//LOCK���� Ȩ ���� �κ��� ��ġ�� ����
	//Ȩ���κκ� => ���� �κ�
	vector<pair<int, int>> holes_pos;
	for (int i = 0; i < lockSize; i++) {
		for (int j = 0; j < lockSize; j++) {
			if (lock[i][j] == 0) {
				holes_pos.push_back({ i,j });
				if (rowfirst == -1) {
					rowfirst = i;
				}
				if (colfirst >= j) {
					colfirst = j;
				}
				if (collast <= j) {
					collast = j;
				}
				rowlast = i;
			}
		}
	}

	//segmentfault�� ���� ���� ���ٽ� ���� �߻� -> ���� Ȯ���� ����� 0�϶� �����ؼ� �����ϰ�
	if (holes_pos.size() == 0) {
		return true;
	}

	//Ȩ ���� �κ��� �ִ� ���� ���� �����ϵ��� �߶󳻸� ���ϱ� ���� Size �ʱ�ȭ
	int rowSize = (rowlast - rowfirst) + 1;
	int colSize = (collast - colfirst) + 1;

	//key�� ��ġ�ϵ��� ���� ���̹Ƿ� ���� �ݴ�� �ؼ� string�� ����
	for (int i = rowfirst; i <= rowlast; i++) {
		for (int j = colfirst; j <= collast; j++) {
			if (lock[i][j] == 1) {
				hole_str += (lock[i][j] + 47);
			}
			else{
				hole_str += (lock[i][j] + 49);
			}
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