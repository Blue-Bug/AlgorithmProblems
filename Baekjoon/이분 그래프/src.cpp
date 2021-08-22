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
			//�̹� �湮�ߴ� ���ε� �׷쵵 ���ٸ� ����Ŭ
			return false;
		}
		if (check[next] != -1) {
			//�̹� �湮�߾��ٸ� �Ѿ
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
				//�׷����� ���鼭 0�� 1�� �׷��� ����
				if (!dfs(i, 0, 1)) {
					//����Ŭ�� ����� �̺� �׷����� ������� ����
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