#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

#define	MAX 8

struct set_type {
	unordered_set<string> s;
};

vector<set_type> candidate_Key(MAX);

unordered_set<string> make_RelSet(vector<vector<string>>& relation, string columns) {
	unordered_set<string> res;
	//unordered_set���ٰ� �� Į������ ������ ���ļ� ����
	for (auto it : relation) {
		string tmp = "";
		for (int i = 0; i < columns.size(); i++) {
			//atoi ���� segmentation fault �߻���
			tmp += it[(columns[i] - 48)] + ",";
		}
		res.insert(tmp);
	}
	return res;
}


bool minimality_Check(string schemaNum) {
	//�ּҼ� üũ
	//key : 23 - string : 123
	//key : 13 - string : 123
	//set���� ������ üũ
	for (auto it : candidate_Key) {
		for (auto it2 : it.s) {
			int cnt = 0;
			if (it2 == schemaNum) {
				return false;
			}
			for (int i = 0; i < schemaNum.size(); i++) {
				for (int j = 0; j < it2.size(); j++) {
					if (schemaNum[i] == it2[j]) {
						if (++cnt == it2.size()) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool uniqueness_Check(unordered_set<string>& tmp, int rowSize) {
	//���ϼ� üũ
	if (tmp.size() == rowSize) {
		//�ο� ���̿� ������ True
		return true;
	}
	return false;
}

void combination(vector<string>& comb_list, bool Check[], int n, int r, int schemaSize) {
	if (r == 0) {
		string res = "";
		for (int i = 0; i < schemaSize; i++) {
			//ascii�ڵ� ���ڷ� ��ȯ
			//1�� 48
			if (Check[i] == true) {
				char tmp = i + 48;
				res += tmp;
			}
		}
		comb_list.push_back(res);
		return;
	}

	for (int i = n; i < schemaSize; i++) {
		if (Check[i] == true) {
			continue;
		}
		Check[i] = true;
		combination(comb_list, Check, i, r - 1, schemaSize);
		Check[i] = false;
	}
}


void find_Candidate(vector<vector<string>>& relation) {
	int rowSize = relation.size();
	int schemaSize = relation.front().size();
	int checkSize = 1;

	//Ű�� �������� �̷��� ���
	while (checkSize <= schemaSize) {
		//Į���� �ִ� 8�� �̹Ƿ� ũ�⸦ 8�� �ʱ�ȭ
		bool Check[MAX]{ false };
		vector<string> comb_list;
		//������ ����
		combination(comb_list, Check, 0, checkSize, schemaSize);
		for (auto it : comb_list) {
			//�����̼� �ν��Ͻ��� ���鼭 �ش� Į���鸸 ���� set�� �����
			unordered_set<string> res = make_RelSet(relation, it);
			if (minimality_Check(it) && uniqueness_Check(res, rowSize)) {
				candidate_Key[checkSize - 1].s.insert(it);
			}
		}
		checkSize++;
	}
}

int solution(vector<vector<string>> relation) {
	int answer = 0;
	find_Candidate(relation);
	for (auto it : candidate_Key) {
		answer += it.s.size();
	}
	return answer;
}