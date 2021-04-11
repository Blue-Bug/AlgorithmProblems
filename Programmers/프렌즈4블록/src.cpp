#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int solution(int m, int n, vector<string> board) {
	int answer = 0;
	bool flag = true;

	//board에 있는 정보를 그대로 copy벡터에 복사해온다.
	vector<vector<char>> copy(n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			copy[i].push_back(board[i][j]);
		}
	}

	//지워지는 것들이 없을때까지 반복한다.
	while (flag) {
		//i번째 행에 몇번째 열이 지워졌는지 저장할 unordered_map
		unordered_map<int, unordered_set<int>> mm;
		flag = false;

		//2x2씩 보면서 일단 지우기
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				//copy에서 하나를 가져와서
				char str = copy[i][j];
				//그 값이 x라면 비어있다는 의미이므로 넘어가고
				if (str == 'x') { continue; }
				//나머지 붙어있는 3개의 값이 전부 같다면 그 값들을 mm에 추가한다.
				if (copy[i][j + 1] == str && copy[i + 1][j] == str && copy[i + 1][j + 1] == str) {
					mm[i].insert(j + 1);
					mm[i].insert(j);
					mm[i + 1].insert(j);
					mm[i + 1].insert(j + 1);

					//지워진 것들이 있으므로 flag를 true로 바꾼다.
					flag = true;
				}
			}
		}

		//copy2 벡터에는 copy에서 지워진 값들을 빼고 블록들을 아래로 내린값을 저장한다.
		vector<vector<char>> copy2(n);
		//맨 아래 행부터 올라가면 체크할 것
		int idx = m - 1;

		//블록 내리기, 첫번째 열의 맨아래 행부터 맨 윗행까지 체크하면 다음 열로 넘어간다.
		for (int j = 0; j < n; j++) {
			for (int i = m - 1; i >= 0; i--) {
				//위에서 mm의 행에 저장했던 set에 해당 열이 있는지 확인한다.
				if (mm[i].find(j) == mm[i].end()) {
					//지워지지 않았다면 copy2에 추가
					copy2[idx--].push_back(copy[i][j]);
				}
			}
			for (int k = idx; k >= 0; k--) {
				//나머지는 지워진 것이므로 비어있는 행들에 x를 추가한다.
				copy2[k].push_back('x');
			}
			idx = m - 1;
		}
		//copy2를 copy로 복사하고 지워진 만큼 mm의 크기를 answer에 추가한다.
		copy = copy2;
		for (auto tmp : mm) {
			answer += tmp.second.size();
		}
	}
	
	return answer;
}