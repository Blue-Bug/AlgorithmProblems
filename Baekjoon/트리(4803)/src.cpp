#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<vector<int>> edges;

int n, m, t = 1;
bool dfs(int start,int parent, vector<bool> &check) {
	check[start] = true;
	for (int i = 0; i < edges[start].size(); i++) {
		int next = edges[start][i];
		if (parent == next) continue;
		if (check[next] && next != parent) return false;
		if (!dfs(next,start, check)) return false;
	}
	return true;
}

int main() {
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0) {
			break;
		}
		edges = vector<vector<int>>(n+1);

		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		int result = 0;
		vector<bool> check(n + 1, false);
		for (int i = 1; i <= n; i++) {
			if (!check[i]) {
				if (dfs(i,0, check)) {
					result++;
				}	
			}
		}
		cout << "Case " << t++ << ": ";
		if (result > 1) {
			cout << "A forest of "<< result <<  " trees.\n";
		}
		else if (result == 1) {
			cout << "There is one tree.\n";
		}
		else { 
			cout << "No trees.\n";
		}
	}
}