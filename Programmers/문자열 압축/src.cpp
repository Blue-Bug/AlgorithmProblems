#include <string>
#include <vector>
using namespace std;

int check_matchCount(int matchCount) {
	if (matchCount < 10) {
		return 1;
	}
	else if (matchCount < 100) {
		return 2;
	}
	else if (matchCount < 1000) {
		return 3;
	}
	return -1;
}

int solution(string s) {
	int answer = 0;
	int strSize = s.size();
	//문자열은 무조건 앞에서부터 잘라야됨 -> 입출력 예 5 참고
	int cutSize = strSize / 2 + 1;
	int minLen = strSize;

	while (cutSize > 0) {
		int match_Size = 0;
		int remain_Size = strSize;
		int cur_Size = 0;
		int matchCount = 1;
		string tmp = "";
		string matchString = s.substr(0, cutSize);
		for (int i = cutSize; i < strSize; i += cutSize) {
			tmp = s.substr(i, cutSize);
			if (matchString != tmp) {
				if (matchCount != 1) {
					//중복된 문자열이 있었으면 추가
					match_Size += cutSize + check_matchCount(matchCount);
					remain_Size -= (matchCount * cutSize);
				}
				matchString = tmp;
				matchCount = 1;
			}
			else if (matchString == tmp) {
				//중복되는 문자열이었을 경우 Count 증가
				matchCount += 1;
				if (i == strSize - cutSize) {
					if (matchCount != 1) {
						//문자열 마지막에서도 중복된 문자열 체크
						match_Size += cutSize + check_matchCount(matchCount);
						remain_Size -= (matchCount * cutSize);
					}
				}
			}
		}
		cur_Size = match_Size + remain_Size;
		if (minLen > cur_Size) {
			minLen = cur_Size;
		}
		cutSize--;
	}
	answer = minLen;
	return answer;
}