#include <string>
#include <vector>

using namespace std;

int res = 0;
bool isPossible(vector<vector<int>> &board,int col,int row,int n) {
	for (int i = 0; i < n; i++) {
		//������ üũ
		if (board[row][i] == 1) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		//������ üũ
		if (board[i][col] == 1) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		//�밢�� üũ
		int x1 = col + (row - i);
		int x2 = col - (row - i);
		if (x1 > -1 && x1 < n) {
			if (board[i][x1] == 1) {
				return false;
			}
		}
		if (x2 > -1 && x2 < n) {
			if (board[i][x2] == 1) {
				return false;
			}
		}
	}
	return true;
}

void checkQueen(vector<vector<int>> &board,int row) {
	if (row >= board.size()) {
		//ROW �� ���� �� �ִ� Queen�� ������ �ϳ�
		//��� ROW�� Queen�� �ִٸ� ����
		res++;
		return;
	}
	for (int col = 0; col < board.size(); col++) {
		if (isPossible(board, col, row, board.size())) {
			board[row][col] = 1;
			//�ش� ��ġ���� ���� �ִ� ��� ��ġ�� ���� �ִ��� üũ
			checkQueen(board,row+1);
			board[row][col] = 0;
		}
	}
	return;
}

int solution(int n) {
	int answer = 0;
	vector<vector<int>> board(n, vector<int>(n, 0));
	checkQueen(board,0);
	answer = res;
	return answer;
}