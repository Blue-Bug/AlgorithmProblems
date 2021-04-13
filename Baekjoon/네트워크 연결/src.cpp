#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct node {
	int node_num;
	int cost;
};

struct cmp {
	bool operator()(node a, node b) {
		return a.cost > b.cost;
	}
};

vector<node> graph[10001];

int solution() {
	bool check[10001]{ false };
	priority_queue<node, vector<node>, cmp> pq;
	pq.push(node{ 1,0 });
	int sum = 0;

	while (!pq.empty()) {
		node curnode = pq.top();
		pq.pop();
		if (check[curnode.node_num]) continue;
		check[curnode.node_num] = true;

		sum += curnode.cost;
		for (int i = 0; i < graph[curnode.node_num].size(); i++) {
			int next_node = graph[curnode.node_num][i].node_num;
			int next_cost = graph[curnode.node_num][i].cost;
			if (!check[next_node]) {
				pq.push(node{ next_node,next_cost });
			}
		}
	}
	return sum;
}

int main() {
	int V, E;
	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		int num1, num2, cost;
		cin >> num1 >> num2 >> cost;
		graph[num1].push_back(node{ num2,cost });
		graph[num2].push_back(node{ num1,cost });
	}
	cout << solution();
}