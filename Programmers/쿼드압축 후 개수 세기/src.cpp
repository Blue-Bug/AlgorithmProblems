#include <string>
#include <vector>

using namespace std;

vector<vector<int>> qt;

bool is_zero(int a, int b, int h) {
	for (int i = a; i < a + h; i++) {
		for (int j = b; j < b + h; j++) {
			if (qt[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

bool is_one(int a, int b, int h) {
	for (int i = a; i < a + h; i++) {
		for (int j = b; j < b + h; j++) {
			if (qt[i][j] != 1) {
				return false;
			}
		}
	}
	return true;
}
string quadtree(int row, int col,int n) {
	if (is_zero(row, col, n)) {
		return "0";
	}
	if (is_one(row, col, n)) {
		return "1";
	}
	
	n /= 2;
	return quadtree(row, col, n) + quadtree(row, col + n, n) + quadtree(row + n, col, n) + quadtree(row + n, col + n, n);
}

vector<int> solution(vector<vector<int>> arr) {
	vector<int> answer;
	
	qt = arr;

	int n = arr.size();
	string res = quadtree(0, 0, n);
	n = res.size();
	for (auto str : res) {
		if (str == '1') {
			n -= 1;
		}
	}
	answer.push_back(n);
	answer.push_back(res.size() - n);
	return answer;
}