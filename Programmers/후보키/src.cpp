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
	//unordered_set에다가 각 칼럼들의 값들을 합쳐서 넣음
	for (auto it : relation) {
		string tmp = "";
		for (int i = 0; i < columns.size(); i++) {
			//atoi 쓰면 segmentation fault 발생함
			tmp += it[(columns[i] - 48)] + ",";
		}
		res.insert(tmp);
	}
	return res;
}


bool minimality_Check(string schemaNum) {
	//최소성 체크
	//key : 23 - string : 123
	//key : 13 - string : 123
	//set에서 꺼내서 체크
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
	//유일성 체크
	if (tmp.size() == rowSize) {
		//로우 길이와 같으면 True
		return true;
	}
	return false;
}

void combination(vector<string>& comb_list, bool Check[], int n, int r, int schemaSize) {
	if (r == 0) {
		string res = "";
		for (int i = 0; i < schemaSize; i++) {
			//ascii코드 숫자로 변환
			//1이 48
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

	//키가 여러개로 이뤄진 경우
	while (checkSize <= schemaSize) {
		//칼럼이 최대 8개 이므로 크기를 8로 초기화
		bool Check[MAX]{ false };
		vector<string> comb_list;
		//조합을 구함
		combination(comb_list, Check, 0, checkSize, schemaSize);
		for (auto it : comb_list) {
			//릴레이션 인스턴스를 보면서 해당 칼럼들만 합쳐 set을 만든다
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