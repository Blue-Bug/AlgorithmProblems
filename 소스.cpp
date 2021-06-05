#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	string str;
	cin >> str;

	vector<int> alpha;
	vector<vector<int>> suffixVector(27);
	vector<vector<int>> answer(27);

	for (int i = 0; i < 27; i++) {
		alpha.push_back(i + 1);
	}

	suffixVector[alpha[(str[str.size() - 1] - 97)]].push_back(str.size());
	for (int i = str.size() - 2; i >= 0; i--) {
		if (suffixVector[alpha[(str[i] - 97)]].empty()) {
			suffixVector[alpha[(str[i] - 97)]].push_back(i + 1);
			//시작하는 문자가 이전과 다르므로 0을 출력하면 된다.
			answer[alpha[(str[i] - 97)]].push_back(0);
		}
		else {
			//suffixVector에 값이 있다면 어디에 들어가야할지 비교
			//시간 너무 오래 걸림 (이분 탐색으로 바꾸거나 다른방식으로 바꿔야 될듯)
			int prevCnt = 0;
			for (int j = 0; j < suffixVector[alpha[(str[i] - 97)]].size(); j++) {
				bool flag = false;
				//p는 이전에 넣은 suffix int값(이 값부터 문자열을 비교하면된다)
				//l은 현재 suffix int값
				int p = suffixVector[alpha[(str[i] - 97)]][j];
				int l = i;
				int curCnt = 0;
				//맨 앞 문자는 같기 때문에 그 다음문자부터 비교한다.
				for (int k = p; k < str.size(); k++) {
					l++;
					if (str[k] > str[l]) {
						//만약 현재 suffix가 더 작다면 앞에 끼워넣는다.
						suffixVector[alpha[(str[i] - 97)]].emplace(suffixVector[alpha[(str[i] - 97)]].begin() + j, i + 1);
						answer[alpha[(str[i] - 97)]].emplace(answer[alpha[(str[i] - 97)]].begin() + j, prevCnt);
						answer[alpha[(str[i] - 97)]][j + 1] = curCnt;
						flag = true;
						break;
					}
					//같은 문자일 경우 다음 문자를 본다.
					else if (str[k] == str[l]) {
						curCnt++;
						continue;
					}
					//만약 현재 suffix가 더 클 경우 break
					else {
						break;
					}
				}
				prevCnt = curCnt;
				//끼워넣었다면 비교를 마친다.
				if (flag) break;
				//현재 suffix가 가장 클 경우 그냥 맨 뒤에 넣는다.
				if (!flag && j == suffixVector[alpha[(str[i] - 97)]].size() - 1) {
					suffixVector[alpha[(str[i] - 97)]].push_back(i + 1);
					answer[alpha[(str[i] - 97)]].push_back(curCnt);
					break;
				}
			}
		}
	}
	for (auto it : suffixVector) {
		for (auto val : it) {
			cout << val << ' ';
		}
	}
	cout << '\n';
	
	cout << "x ";
	for (int i = 0; i < answer.size(); i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			if (i == 0 && j == 0) continue;
			cout << answer[i][j] << ' ';
		}
	}
}