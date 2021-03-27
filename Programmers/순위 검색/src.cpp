#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

//info안에 있는 조건을 그대로 해쉬 키로 만들어서 
//쿼리마다 한번만 필터로 계산해 낼 수 있도록 만듬
//ex) 키로 cpp,backend,junior,pizza를 주고 값으로 점수를 준다면

unordered_map<int, vector<int>> applicants;
//key : 111 11 11 11 value: score
int mScore;
int queryKey = 0;

void inline processInfo(string &infoString) {
	string tmp;
	int idx = 0;
	int hashKey = 0;
	for (int i = 0; i < infoString.size()+1; i++) {
		if (infoString[i] == ' ' || i == infoString.size()) {
			if (idx == 0) {
				if (tmp == "cpp") {
					hashKey = 1 << 2;
				}
				else if (tmp == "java") {
					hashKey = 1 << 1;
				}
				else if (tmp == "python") {
					hashKey = 1;
				}
			}
			else if (idx == 1) {
				hashKey = hashKey << 1;
				if (tmp == "backend") {
					hashKey += 1;
					hashKey = hashKey << 1;
				}
				else if(tmp == "frontend") {
					hashKey = hashKey << 1;
					hashKey += 1;
				}
			}
			else if (idx == 2) {
				hashKey = hashKey << 1;
				if (tmp == "junior") {
					hashKey += 1;
					hashKey = hashKey << 1;
				}
				else if (tmp == "senior") {
					hashKey = hashKey << 1;
					hashKey += 1;
				}
			}
			else if (idx == 3) {
				hashKey = hashKey << 1;
				if (tmp == "chicken") {
					hashKey += 1;
					hashKey = hashKey << 1;
				}
				else if (tmp == "pizza") {
					hashKey = hashKey << 1;
					hashKey += 1;
				}
			}
			else if (idx == 4) {
				mScore = stoi(tmp);
			}
			idx++;
			tmp = "";
		}
		else {
			tmp += infoString[i];
		}
	}
	applicants[hashKey].push_back(mScore);
}

void inline processQuery(string &queryString) {
	string tmp;
	int idx = 0;
	queryKey = 0;
	for (int i = 0; i < queryString.size()+1; i++) {
		if (queryString[i] == ' ' || i == queryString.size()){
			if (tmp == "and") {
				tmp = "";
				continue;
			}
			if (idx == 0) {
				if (tmp == "cpp") {
					queryKey = 1 << 2;
				}
				else if (tmp == "java") {
					queryKey = 1 << 1;
				}
				else if (tmp == "python") {
					queryKey = 1;
				}
			}
			else if (idx == 1) {
				queryKey = queryKey << 1;
				if (tmp == "backend") {
					queryKey += 1;
					queryKey = queryKey << 1;
				}
				else if (tmp == "frontend") {
					queryKey = queryKey << 1;
					queryKey += 1;
				}
				else {
					queryKey = queryKey << 1;
				}
			}
			else if (idx == 2) {
				queryKey = queryKey << 1;
				if (tmp == "junior") {
					queryKey += 1;
					queryKey = queryKey << 1;
				}
				else if (tmp == "senior") {
					queryKey = queryKey << 1;
					queryKey += 1;
				}
				else {
					queryKey = queryKey << 1;
				}
			}
			else if (idx == 3) {
				queryKey = queryKey << 1;
				if (tmp == "chicken") {
					queryKey += 1;
					queryKey = queryKey << 1;
				}
				else if (tmp == "pizza") {
					queryKey = queryKey << 1;
					queryKey += 1;
				}
				else {
					queryKey = queryKey << 1;
				}
			}
			else if (idx == 4) {
				mScore = stoi(tmp);
			}
			idx++;
			tmp = "";
		}
		else {
			tmp += queryString[i];
		}
	}
}

vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;
	for(int i = 0; i<info.size(); i++){		
		processInfo(info[i]);
	}
	
	for (auto q : query) {
		processQuery(q);

		int count_applicant = 0;

		//쿼리 조건 체크
		for (auto applicant : applicants) {
			//쿼리에서 추출한 키와 해쉬 키를 & 연산
			//원하는 조건이 다 들어있는 지원자들만 체크한다
			if ((applicant.first & queryKey) == queryKey) {
				for (auto applicantScore : applicant.second) {
					if (applicantScore >= mScore) {
						count_applicant++;
					}
				}
			}
		}

		answer.push_back(count_applicant);
	}
	return answer;
}