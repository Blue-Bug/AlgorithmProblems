#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(int n, vector<int> times) {
	long long answer = 0;

	long long people = n;
	sort(times.begin(), times.end());
	long long first = 1;
	long long last = times.back() * people;
	answer = last;
	
	while (first <= last) {
		long long mid = (first + last) / 2;
		long long cnt = 0;
		for (auto time : times) {
			cnt += mid / time;
		}
		if (people > cnt) {
			first = mid + 1;
		}
		else {
			if (mid < answer) {
				answer = mid;
			}
			last = mid - 1;
		}

	}
	return answer;
}
