#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> solution(string msg) {
	vector<int> answer;
	//�������� ����� unordered_map
	unordered_map<string, int> dict;
	char tmp = 'A';

	//������ ���� �߰��Ѵ�.
	for (int i = 1; i <= 26; i++) {
		string key = "";
		key += tmp;
		dict[key] = i;
		tmp += 1;
	}

	int idx = 27;
	while (msg!="") {
		//ó������ ������ ���ڿ��� ������ ������� ��츦 üũ
		if (dict.find(msg) != dict.end()) {
			answer.push_back(dict[msg]);
			break;
		}
		else {
			for (int i = msg.size()-1; i >= 0; i--) {
				//���ڿ��� �ڿ������� �ڸ��� ������ �ִ����� üũ
				string tmp = msg.substr(0, i);

				if (dict.find(tmp) != dict.end()) {
					//���� ������ �ִٸ� �� ���� answer���Ϳ� �߰��ϰ�
					answer.push_back(dict[tmp]);
					if (i != msg.size()) {
						//���� �ڸ� ���ڿ��� �ٷ� �޹��ڸ� ���ؼ� ������ ���� �߰��Ѵ�.
						tmp = tmp + msg[i];
						dict[tmp] = idx++;
					}
					//�߶� �ٷ� �޹��ں��� ������ �߶� �ݺ��Ѵ�.
					msg = msg.substr(i);
					break;
				}
			}
		}
	}
	return answer;
}