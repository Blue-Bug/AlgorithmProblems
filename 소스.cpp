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
			//�����ϴ� ���ڰ� ������ �ٸ��Ƿ� 0�� ����ϸ� �ȴ�.
			answer[alpha[(str[i] - 97)]].push_back(0);
		}
		else {
			//suffixVector�� ���� �ִٸ� ��� �������� ��
			//�ð� �ʹ� ���� �ɸ� (�̺� Ž������ �ٲٰų� �ٸ�������� �ٲ�� �ɵ�)
			int prevCnt = 0;
			for (int j = 0; j < suffixVector[alpha[(str[i] - 97)]].size(); j++) {
				bool flag = false;
				//p�� ������ ���� suffix int��(�� ������ ���ڿ��� ���ϸ�ȴ�)
				//l�� ���� suffix int��
				int p = suffixVector[alpha[(str[i] - 97)]][j];
				int l = i;
				int curCnt = 0;
				//�� �� ���ڴ� ���� ������ �� �������ں��� ���Ѵ�.
				for (int k = p; k < str.size(); k++) {
					l++;
					if (str[k] > str[l]) {
						//���� ���� suffix�� �� �۴ٸ� �տ� �����ִ´�.
						suffixVector[alpha[(str[i] - 97)]].emplace(suffixVector[alpha[(str[i] - 97)]].begin() + j, i + 1);
						answer[alpha[(str[i] - 97)]].emplace(answer[alpha[(str[i] - 97)]].begin() + j, prevCnt);
						answer[alpha[(str[i] - 97)]][j + 1] = curCnt;
						flag = true;
						break;
					}
					//���� ������ ��� ���� ���ڸ� ����.
					else if (str[k] == str[l]) {
						curCnt++;
						continue;
					}
					//���� ���� suffix�� �� Ŭ ��� break
					else {
						break;
					}
				}
				prevCnt = curCnt;
				//�����־��ٸ� �񱳸� ��ģ��.
				if (flag) break;
				//���� suffix�� ���� Ŭ ��� �׳� �� �ڿ� �ִ´�.
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