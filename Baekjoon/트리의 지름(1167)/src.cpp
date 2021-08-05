#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct nodeStruct {
	int node, cost;
};
int n, answer = 0,nextRoot = 0;
vector<nodeStruct>edges[100001];
vector<bool> check;

void dfs(int node, int result) {
	//이진 트리가 아닐수도 있으므로 모든 노드를 검사해야함
	for (int i = 0; i < edges[node].size(); i++) {
		int nextNode = edges[node][i].node;
		int nextCost = edges[node][i].cost;
		if (check[nextNode]) continue;
		check[nextNode] = true;
		if (answer <= result + nextCost) {
			answer = result + nextCost;
			nextRoot = nextNode;
		}
		dfs(nextNode, result + nextCost);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	int node1, node2, cost;
	for (int i = 0; i < n; i++) {
		cin >> node1;
		while (1) {
			cin >> node2;
			if (node2 == -1) {
				break;
			}
			cin >> cost;
			edges[node1].push_back({ node2,cost });
			edges[node2].push_back({ node1,cost });
		}
	}
	check = vector<bool>(n + 1);
	check[1] = true;
	dfs(1, 0);

	check = vector<bool>(n + 1);
	check[nextRoot] = true;
	dfs(nextRoot, 0);

	cout << answer;
}