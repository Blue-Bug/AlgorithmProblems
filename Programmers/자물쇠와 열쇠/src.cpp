#include <string>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string hole_str = "";

void rotateKey(vector<vector<int>> &key) {
	//key를 회전시키기
	vector<int> init_tmp(key.size());
	vector<vector<int>> tmp;
	for (int t = 0; t < key.size(); t++) {
		tmp.push_back(init_tmp);
	}
	//임시 배열 초기화

	//맨윗줄을 90도 회전해서 맨 끝열부터 넣는다.
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

	//key에서 rowSize, colSize 크기만큼 잘라내며 string에 추가
	for (int i = init_row; i <= row; i++) {
		for (int j = init_col; j <= col; j++) {
			cmpStr += (key[i][j]+48);
		}
	}
	//lock에서 같은 크기로 추출하고 홈 파인 부분을 반전시킨 문자열과 비교
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

	//LOCK에서 홈 파인 부분의 위치를 추출
	//홈파인부분 => 비교할 부분
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

	//segmentfault로 봐선 벡터 접근시 문제 발생 -> 높은 확률로 사이즈가 0일때 접근해서 문제일것
	if (holes_pos.size() == 0) {
		return true;
	}

	//홈 파인 부분이 있는 곳을 전부 포함하도록 잘라내며 비교하기 위해 Size 초기화
	int rowSize = (rowlast - rowfirst) + 1;
	int colSize = (collast - colfirst) + 1;

	//key와 일치하도록 비교할 것이므로 값을 반대로 해서 string을 구성
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
	
	//회전하며 잘라가며 비교
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
		//만약 맞는 키가 없었다면 회전한다.
		rotateKey(key);
	}
	return false;
}