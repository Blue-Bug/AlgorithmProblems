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
	//처음에는 비는대로 막 들어가면 됨
	//마지막이 문제, 마지막 한명이 어딜 들어가느냐에 따라 종료시간이 갈림

	long long first = 0;
	long long last = times.size()-1;
	long long compareTime = times.back();
	while (first < last) {
		int mid = (first + last) / 2;
		//더 기다리지만 심사시간이 더 짧아서 빨리 끝날수 있는가를 체크
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
