#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>
using namespace std;

int forwardDir(deque<int> diffCnt, string name, int size) {
	int answer = 0;
	int idx = 0;
	bool flag = false;
	while (!diffCnt.empty()) {
		int pos = diffCnt.front();
		diffCnt.pop_front();
		if (!flag) {
			int move1 = abs(pos - idx);
			int move2 = abs(pos - (int)(size - 1)) + idx + 1;
			move1 < move2 ? answer += move1 : (answer += move2, flag = true);
		}
		int change1 = abs(name[pos] - 'A');
		int change2 = abs(name[pos] - 'Z') + 1;
		change1 < change2 ? answer += change1 : answer += change2;
		idx = pos;
	}
	return answer;
}
int reverseDir(deque<int> diffCnt, string name, int size) {
	int answer = 1;
	if (diffCnt.front() == 0) {
		diffCnt.pop_front();
		int change1 = abs(name[0] - 'A');
		int change2 = abs(name[0] - 'Z') + 1;
		change1 < change2 ? answer += change1 : answer += change2;
	}
	int idx = size-1;
	bool flag = false;
	while (!diffCnt.empty()) {
		int pos = diffCnt.back();
		diffCnt.pop_back();
		if (!flag) {
			int move1 = abs(pos - idx);
			int move2 = pos + abs((int)(size - 1) - idx) + 1;
			move1 < move2 ? answer += move1 : (answer += move2, flag = true);
		}
		int change1 = abs(name[pos] - 'A');
		int change2 = abs(name[pos] - 'Z') + 1;
		change1 < change2 ? answer += change1 : answer += change2;
		idx = pos;
	}
	return answer;
}

int solution(string name) {
	int answer = 0;
	string tmp = "";
	deque<int> diffCnt;
	for (int i = 0; i < name.size(); i++) {
		tmp += "A";
		if (tmp[i] != name[i]) {
			diffCnt.push_back(i);
		}
	}
	int res1 = forwardDir(diffCnt, name, name.size());
	int res2 = reverseDir(diffCnt, name, name.size());
	answer = res1 < res2 ? res1 : res2;
	
	return answer;
}

int main() {
	
	solution("BAAAAB"); // 3
}