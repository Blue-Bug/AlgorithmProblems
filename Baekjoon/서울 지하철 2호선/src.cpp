#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> check;

int dfs(int cur, int parent, int start, int cnt) {	
	for (int i = 0; i < edges[cur].size(); i++) {
		int next = edges[cur][i];
		//자신의 부모라면
		if (next == parent) continue;
		if (check[next] != -1) {
			if (next == start) {
				return 0;
			}
			return check[next];
		}
		check[next] = cnt + 1;
		int result = dfs(next, cur, start, cnt + 1);
		if (result != -1) {
			return result;
		}
	} 
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	edges = vector<vector<int>>(n + 1);

	int a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		check = vector<int>(n + 1,-1);
		check[i] = 0;
		cout << dfs(i,0,i,0) << ' ';
	}
}