#include <string>
#include <vector>

using namespace std;

int res = 0;
bool isPossible(vector<vector<int>> &board,int col,int row,int n) {
	for (int i = 0; i < n; i++) {
		//가로줄 체크
		if (board[row][i] == 1) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		//세로줄 체크
		if (board[i][col] == 1) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		//대각선 체크
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
		//ROW 당 있을 수 있는 Queen의 개수는 하나
		//모든 ROW에 Queen이 있다면 정답
		res++;
		return;
	}
	for (int col = 0; col < board.size(); col++) {
		if (isPossible(board, col, row, board.size())) {
			board[row][col] = 1;
			//해당 위치에서 갈수 있는 모든 위치에 퀸이 있는지 체크
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