#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n,answer = 987654321;
vector<int> sector;
vector<vector<int>> edges;

bool bfs(int first,vector<int>&team) {
	queue<int> q;
	q.push(first);
	vector<bool> check(n+1,false);
	int cnt = 0;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (check[cur]) continue;
		check[cur] = true;
		cnt++;
		for (int i = 0; i < edges[cur].size(); i++) {
			int next = edges[cur][i];
			for (int j = 0; j < team.size(); j++) {
				if (next == team[j]) {
					q.push(next);
				}
			}
		}
	}
	if (cnt == team.size()) {
		return true;
	}
	return false;
}

int comb(vector<bool>&check,int k,int r,int idx) {
	if (k == r) {
		vector<int> teamA;
		vector<int> teamB;
		int teamA_Sum = 0;
		int teamB_Sum = 0;
		for (int i = 1; i <= n; i++) {
			if (check[i]) {
				teamA.push_back(i);
				teamA_Sum += sector[i];
			}
			else {
				teamB.push_back(i);
				teamB_Sum += sector[i];
			}
		}
		//bfs를 돌아서 각 팀구성원을 다 포함한다면 true
		if (bfs(teamA.front(),teamA) && bfs(teamB.front(),teamB)) {
			return abs(teamA_Sum-teamB_Sum);
		}
		return 987654321;
	}
	for (int i = idx; i <= n; i++) {
		//idx의 중요성
		if (check[i]) continue;
		check[i] = true;
		answer = min(answer,comb(check, k, r + 1,i+1));
		check[i] = false;
	}
	return 987654321;
}
int main() {
	cin >> n;
	int tmp,cnt;
	sector.push_back(0);
	edges = vector<vector<int>>(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		sector.push_back(tmp);
	}

	for (int i = 1; i <= n; i++) {
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> tmp;
			edges[i].push_back(tmp);
		}
	}
	
	//a를 고른다 (b는 나머지를 자동으로)
	for (int i = 1; i < n; i++) {
		vector<bool> check(n + 1, false);
		comb(check,i,0,1);
	}
	if (answer == 987654321) {
		cout << -1;
	}
	else {
		cout << answer;
	}
}