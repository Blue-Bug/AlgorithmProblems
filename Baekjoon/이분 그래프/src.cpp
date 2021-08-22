#include <iostream>
#include <vector>
using namespace std;

vector<int> check;
vector<vector<int>> edges;

bool dfs(int cur,int parent,bool idx) {
	for (int i = 0; i < edges[cur].size(); i++) {
		int next = edges[cur][i];
		if (next == parent) continue;
		if (check[next] == check[cur]) {
			//이미 방문했던 곳인데 그룹도 같다면 사이클
			return false;
		}
		if (check[next] != -1) {
			//이미 방문했었다면 넘어감
			continue;
		}
		check[next] = idx;
		if (!dfs(next, cur, !idx)) {
			return false;
		}
		
	}
	return true;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int v, e;
		cin >> v >> e;
		edges = vector<vector<int>> (v + 1);
		
		for (int i = 0; i < e; i++) {
			int a, b;
			cin >> a >> b;
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		check = vector<int>(v + 1, -1);
		
		for (int i = 1; i <= v; i++) {
			if (check[i] == -1) {
				check[i] = 0;
				//그래프를 돌면서 0과 1로 그룹을 나눔
				if (!dfs(i, 0, 1)) {
					//사이클이 생기면 이분 그래프를 만들수가 없다
					cout << "NO" << '\n';
					break;
				}
			}
			if (i == v) {
				cout << "YES" << '\n';
			}
		}
		
	}
}