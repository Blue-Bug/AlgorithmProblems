#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

//Kruskal MST + union-find
struct OptimizedDisjointSet {
	vector<int> parent, rank; 
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; ++i) 
			parent[i] = i; 
	} 
	int find(int u) {
		if (u == parent[u])
			return u; 
		return parent[u] = find(parent[u]); 
	} 
	void merge (int u, int v) {
		u = find(u); 
		v = find(v); 
		if (u == v) return; 
		if (rank[u] > rank[v]) swap(u, v); 
		parent[u] = v; 
		if (rank[u] == rank[v]) ++rank[v]; 
	} 
};

	
struct edgeStruct {
	int u;
	int v;
	int cost;
};

struct cmp {
	bool operator()(edgeStruct a, edgeStruct b) {
		return a.cost > b.cost;
	}
};

priority_queue<edgeStruct, vector<edgeStruct>, cmp> pq;

void make_graph(vector<vector<int>> &land) {
	const int max = land.size();
	int dir[4][3] = { {0,1,1},{0,-1,-1},{1,0,max},{-1,0,-max} };
	int idx = 0;
	for (int i = 0; i < land.size(); i++) {
		for (int j = 0; j < land.size(); j++) {
			for (int k = 0; k < 4; k++) {
				int curCost = land[i][j];
				int next_i = i + dir[k][0];
				int next_j = j + dir[k][1];
				//오른쪽으로 가면 노드 1증가
				//아래쪽으로 가면 한줄(land.size)만큼 증가
				//위쪽으로 가면 한줄 만큼 감소
				//왼쪽으로 가면 노드 1 감소
				if (next_i >= 0 && next_i < land.size() && next_j >= 0 && next_j < land.size()) {
					pq.push(edgeStruct{idx, idx + dir[k][2], abs(curCost -land[next_i][next_j]) });
				}
			}
			idx++;
		}
	}
}

int MST(int height,int maxSize) {
	int result = 0;
	OptimizedDisjointSet mSet(maxSize);
	//union-set이 모든 노드를 포함할때까지
	while (!pq.empty()) {
		//union-set에 추가
		edgeStruct tmp = pq.top();
		pq.pop();
		if (mSet.find(tmp.u) != mSet.find(tmp.v)) {
			mSet.merge(tmp.u, tmp.v);
			if (tmp.cost > height) {
				//height 보다 크면 result에 추가
				result += tmp.cost;
			}
		}
	}
	return result;
}

int solution(vector<vector<int>> land, int height) {
	int answer = 0;

	make_graph(land);
	int maxSize = land.size()*land.size();
	answer = MST(height,maxSize);
	return answer;
}