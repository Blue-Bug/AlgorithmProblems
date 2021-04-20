#include <string>
#include <vector>

using namespace std;

string conv_bin(int next_s) {
	if (next_s < 1) return "";
	string tmp = conv_bin(next_s / 2);
	return tmp + to_string(next_s % 2);
}

vector<int> solution(string s) {
	vector<int> answer;

	int round = 0;
	int zeroCnt = 0;
	while(s != "1"){
		string tmp = "";
		for (auto str : s) {
			if (str == '0') {
				zeroCnt++;
				continue;
			}
			tmp += str;
		}
		int next_s = tmp.size();
		s = conv_bin(next_s);
		round++;
	}
	answer.push_back(round);
	answer.push_back(zeroCnt);
	return answer;
}