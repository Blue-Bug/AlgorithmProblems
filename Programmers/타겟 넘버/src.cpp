#include <string>
#include <vector>

using namespace std;

int cnt = 0;
int tar = 0;
vector<int> nodes;
void dfs(int node,int res) {
	if (node == nodes.size()) {
		if(res==tar)cnt++;
		return;
	}

	dfs(node+1, res + nodes[node]);
	dfs(node+1, res - nodes[node]);
}

int solution(vector<int> numbers, int target) {
	nodes = numbers;
	tar = target;
	dfs(0,0);
	return cnt;
}
int main() {
	solution({ 1,1,1,1,1 }, 3);
}