#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
vector<vector<int>> notebook;

void attachSticker(vector<vector<int>>& sticker,int row,int col) {
	for (int i = row, i2 = 0; i2 < sticker.size(); i++, i2++) {
		for (int j = col, j2 = 0; j2 < sticker[0].size(); j++, j2++) {
			notebook[i][j] += sticker[i2][j2];
		}
	}
}

void rotateSticker(vector<vector<int>>& sticker,int row,int col) {
	vector<int> tmp;
	for (int i = row - 1; i >= 0; i--) {
		for (int j = 0; j < col; j++) {
			tmp.push_back(sticker[i][j]);
		}
	}
	int idx = 0;
	sticker.clear();
	sticker = vector<vector<int>>(col, vector<int>(row));
	for (int j = 0; j < row; j++) {
		for (int i = 0; i < col; i++) {
			sticker[i][j] = tmp[idx++];
		}
	}
}

bool checkSpace(vector<vector<int>> &sticker,int row, int col) {
	//이부분에 문제 있음
	if (row + (sticker.size() - 1) > n|| col + (sticker[0].size() - 1) > m) {
		return false;
	}
	for (int i = row,i2 = 0; i2 < sticker.size(); i++,i2++) {
		for (int j = col,j2 = 0; j2 < sticker[0].size(); j++,j2++) {
			if ((notebook[i][j] == 1) && (sticker[i2][j2] == 1)) {
				return false;
			}
		}
	}
	return true;
}

int stickerInput(int row, int col) {
	vector<vector<int>> sticker(row, vector<int>(col));
	int cnt = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> sticker[i][j];
			if (sticker[i][j] == 1) {
				cnt++;
			}
		}
	}
	//스티커 붙이기
	for (int k = 0; k < 4; k++) {
		int rowEnd = n - sticker.size();
		int colEnd = m - sticker[0].size();
		for (int i = 0; i <= rowEnd; i++) {
			for (int j = 0; j <= colEnd; j++) {
				if (checkSpace(sticker, i,j)) {
					attachSticker(sticker,i,j);
					return cnt;
				}
			}
		}
		rotateSticker(sticker,sticker.size(),sticker[0].size());
	}
	return 0;
}

int main() {
	cin >> n >> m >> k;
	
	notebook = vector<vector<int>>(n, vector<int>(m,0));

	int a, b, answer = 0;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		answer += stickerInput(a,b);
	}
	cout << answer;
}