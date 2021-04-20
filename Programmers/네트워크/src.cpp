#include <string>
#include <vector>

using namespace std;

vector<vector<int>> computercopy;
vector<bool> visited;
int cnt = 0;

void dfs(int node) {
	if (visited[node]) {
		return;
	}
	visited[node] = true;
	for (int j = 0; j < computercopy.size(); j++) {
		if (computercopy[node][j] == 1 && !visited[j]) {
			cnt--;
			dfs(j);
		}
	}
	return;
}

int solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	computercopy = computers;
	visited = vector<bool>(computers.size(), false);
	cnt = computers.size();
	for (int i = 0; i < computers.size(); i++) {
		dfs(i);
	}
	return cnt;
}