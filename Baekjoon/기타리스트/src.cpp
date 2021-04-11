#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[101][1001];
//i번째 곡에서 최대값을 저장
int solution(int idx,int curVolume, int M, int N, vector<int>& V) {
	if (curVolume < 0 || curVolume > M) {
		//조건에 맞지않으면 -2리턴
		return -2;
	}
	if (idx == N) {
		//리프 노드에 도달하면 값 저장
		dp[idx][curVolume] = curVolume;
		return curVolume;
	}
	if (dp[idx][curVolume] != -1) {
		//이미 계산한 값이 있다면 사용
		return dp[idx][curVolume];
	}
	//리프 노드까지 가서 거꾸로 올라오면서 최대값을 저장함
	dp[idx][curVolume] = max(solution(idx + 1, curVolume + V[idx], M, N, V), solution(idx + 1, curVolume - V[idx], M, N, V));
	return dp[idx][curVolume];
}


int main() {
	int N, S, M;
	cin >> N >> S >> M;
	vector<int> V;
	memset(dp, -1, sizeof(dp));
	int tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		V.push_back(tmp);
	}
	tmp = solution(0, S, M, N, V);
	if(tmp != -2) cout << tmp;
	else cout << -1;
}