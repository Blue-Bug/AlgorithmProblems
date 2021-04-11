#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> solution(string msg) {
	vector<int> answer;
	//사전으로 사용할 unordered_map
	unordered_map<string, int> dict;
	char tmp = 'A';

	//사전에 값을 추가한다.
	for (int i = 1; i <= 26; i++) {
		string key = "";
		key += tmp;
		dict[key] = i;
		tmp += 1;
	}

	int idx = 27;
	while (msg!="") {
		//처음부터 마지막 문자열이 사전에 들어있을 경우를 체크
		if (dict.find(msg) != dict.end()) {
			answer.push_back(dict[msg]);
			break;
		}
		else {
			for (int i = msg.size()-1; i >= 0; i--) {
				//문자열을 뒤에서부터 자르며 사전에 있는지를 체크
				string tmp = msg.substr(0, i);

				if (dict.find(tmp) != dict.end()) {
					//만약 사전에 있다면 그 값을 answer벡터에 추가하고
					answer.push_back(dict[tmp]);
					if (i != msg.size()) {
						//현재 자른 문자열의 바로 뒷문자를 합해서 사전에 값을 추가한다.
						tmp = tmp + msg[i];
						dict[tmp] = idx++;
					}
					//잘라낸 바로 뒷문자부터 끝까지 잘라서 반복한다.
					msg = msg.substr(i);
					break;
				}
			}
		}
	}
	return answer;
}