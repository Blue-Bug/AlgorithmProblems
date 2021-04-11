#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int solution(int m, int n, vector<string> board) {
	int answer = 0;
	bool flag = true;

	vector<vector<char>> copy(n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			copy[i].push_back(board[i][j]);
		}
	}
	while (flag) {
		unordered_map<int, unordered_set<int>> mm;
		flag = false;

		//2x2씩 보면서 일단 지우기
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				char str = copy[i][j];
				if (str == 'x') { continue; }
				if (copy[i][j + 1] == str && copy[i + 1][j] == str && copy[i + 1][j + 1] == str) {
					mm[i].insert(j + 1);
					mm[i].insert(j);
					mm[i + 1].insert(j);
					mm[i + 1].insert(j + 1);
					flag = true;
				}
			}
		}
		vector<vector<char>> copy2(n);
		int idx = m - 1;
		//블록 내리기
		for (int j = 0; j < n; j++) {
			for (int i = m - 1; i >= 0; i--) {
				if (mm[i].find(j) == mm[i].end()) {
					//지워지지 않았다면
					copy2[idx--].push_back(copy[i][j]);
				}
			}
			for (int k = idx; k >= 0; k--) {
				copy2[k].push_back('x');
			}
			idx = m - 1;
		}
		copy = copy2;
		for (auto tmp : mm) {
			answer += tmp.second.size();
		}
	}
	

	return answer;
}
int main() {
	solution(6, 6, { "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ" });
}