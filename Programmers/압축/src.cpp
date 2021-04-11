#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> solution(string msg) {
	vector<int> answer;
	unordered_map<string, int> dict;
	char tmp = 'A';
	for (int i = 1; i <= 26; i++) {
		string key = "";
		key += tmp;
		dict[key] = i;
		tmp += 1;
	}

	int idx = 27;
	while (msg!="") {
		//가장 긴 문자열
		if (dict.find(msg) != dict.end()) {
			answer.push_back(dict[msg]);
			break;
		}
		else {
			for (int i = msg.size()-1; i >= 0; i--) {
				string tmp = msg.substr(0, i);
				if (dict.find(tmp) != dict.end()) {
					answer.push_back(dict[tmp]);
					if (i != msg.size()) {
						tmp = tmp + msg[i];
						dict[tmp] = idx++;
					}
					msg = msg.substr(i);
					break;
				}
			}
		}
	}
	return answer;
}

int main() {
	solution("TOBEORNOTTOBEORTOBEORNOT");
}