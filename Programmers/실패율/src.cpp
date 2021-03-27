#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, double> a, pair<int, double> b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second > b.second;
}

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	vector<pair<int, double>> res(N, { 0,0 });
	vector<double> user_stage(N+2,0);
	vector<double> user_challenge(N + 1, 0);

	for (auto stage : stages) {
		user_stage[stage]++;
	}
	for (int i = N; i >= 1; i--) {
		if (i < N) {
			//i번째 스테이지 시도 = i + 1번째 스테이지 시도 유저 + i번째 시도 중 유저
			user_challenge[i] = user_challenge[i + 1] + user_stage[i];
		}
		else {
			//N번째 스테이지 시도 = 다 깬 유저 + N번째 시도 중 유저
			user_challenge[i] = user_stage[N + 1] + user_stage[i];
		}
	}
	int idx = 0;
	for (int i = 1; i <= N; i++) {
		//{스테이지 번호, 실패율}
		res[idx++] = { i,(double)(user_stage[i] / user_challenge[i]) };
	}
	
	stable_sort(res.begin(), res.end(),compare);
	for (auto ext : res) {
		answer.push_back(ext.first);
	}
	return answer;
}