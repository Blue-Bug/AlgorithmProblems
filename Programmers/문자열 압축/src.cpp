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
	//���ڿ��� ������ �տ������� �߶�ߵ� -> ����� �� 5 ����
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
					//�ߺ��� ���ڿ��� �־����� �߰�
					match_Size += cutSize + check_matchCount(matchCount);
					remain_Size -= (matchCount * cutSize);
				}
				matchString = tmp;
				matchCount = 1;
			}
			else if (matchString == tmp) {
				//�ߺ��Ǵ� ���ڿ��̾��� ��� Count ����
				matchCount += 1;
				if (i == strSize - cutSize) {
					if (matchCount != 1) {
						//���ڿ� ������������ �ߺ��� ���ڿ� üũ
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