#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(int n, vector<int> times) {
	long long answer = 0;

	sort(times.begin(), times.end());

	long long people = n;

	if ((people % times.size()) != 0) {
		people /= times.size();
		return answer = times.back() * people;
	}
	else {
		people /= times.size();
		answer = times.back() * (people - 1);
	}
	//ó������ ��´�� �� ���� ��
	//�������� ����, ������ �Ѹ��� ��� �����Ŀ� ���� ����ð��� ����

	long long first = 0;
	long long last = times.size()-1;
	long long compareTime = times.back();
	while (first < last) {
		int mid = (first + last) / 2;
		//�� ��ٸ����� �ɻ�ð��� �� ª�Ƽ� ���� ������ �ִ°��� üũ
		long long checkTime = times[mid];
		long long waitTime = checkTime - (answer % checkTime);
		if (compareTime >= checkTime + waitTime) {
			last = mid;
			compareTime = checkTime + waitTime;
		}
		else {
			first = mid + 1;
		}
	}
	answer += compareTime;
	return answer;
}
