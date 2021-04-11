#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[101][1001];
//i��° ��� �ִ밪�� ����
int solution(int idx,int curVolume, int M, int N, vector<int>& V) {
	if (curVolume < 0 || curVolume > M) {
		//���ǿ� ���������� -2����
		return -2;
	}
	if (idx == N) {
		//���� ��忡 �����ϸ� �� ����
		dp[idx][curVolume] = curVolume;
		return curVolume;
	}
	if (dp[idx][curVolume] != -1) {
		//�̹� ����� ���� �ִٸ� ���
		return dp[idx][curVolume];
	}
	//���� ������ ���� �Ųٷ� �ö���鼭 �ִ밪�� ������
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