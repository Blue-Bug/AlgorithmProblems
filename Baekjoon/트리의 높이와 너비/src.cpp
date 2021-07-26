#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct treeCnt {
	int parent,left,right,level,idx;
};

int n,idx = 1;
pair<int, int> answer = { 1,1 };
vector<treeCnt> binaryTree;

bool cmp(treeCnt a, treeCnt b) {
	if (a.level == b.level) {
		return a.idx < b.idx;
	}
	return a.level < b.level;
}

void findIndex(int cur,int level) {
	if (binaryTree[cur].left == -1) {
		//base condition
		binaryTree[cur].idx = idx++;
		binaryTree[cur].level = level;
		if (binaryTree[cur].right != -1) findIndex(binaryTree[cur].right,level+1);
		return;
	}
	//left
	if(binaryTree[cur].left != -1) findIndex(binaryTree[cur].left,level+1);
	//mid
	binaryTree[cur].idx = idx++;
	binaryTree[cur].level = level;
	//right
	if(binaryTree[cur].right != -1) findIndex(binaryTree[cur].right,level+1);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;

	//크기 10000*20byte = 200kbyte
	binaryTree = vector<treeCnt>(n + 1, { -1,-1,-1 });

	int cur, left, right;

	//n번
	int maxLevel = 0;
	for (int i = 1; i <= n; i++) {
		cin >> cur >> left >> right;
		if (right != -1) {
			binaryTree[cur].right = right;
			binaryTree[right].parent =  cur;
		}
		if (left != -1) {
			binaryTree[cur].left = left;
			binaryTree[left].parent = cur;
		}
	}
	if (n == 1) {
		cout << 1 << ' ' << 1;
		return 0;
	}

	//루트 찾기 최대 레벨만큼
	int root = n/2;
	while(1) {
		if (binaryTree[root].parent == -1) {
			break;
		}
		root = binaryTree[root].parent;
	}
	binaryTree[root].level = 1;
	//인덱스랑 레벨 정하기
	findIndex(root,1);
	
	std::sort(binaryTree.begin(), binaryTree.end(),cmp);

	int first = 0,last = 0,tmpLevel = 2;
	//n번
	for (int i = 2; i < binaryTree.size() - 1;) {
		tmpLevel = binaryTree[i].level;
		first = binaryTree[i].idx;
		for (int j = i + 1; j <= binaryTree.size(); j++) {
			if (binaryTree[j].level != tmpLevel || j == binaryTree.size() - 1) {
				if (j == binaryTree.size() - 1) {
					if (binaryTree[j].level != tmpLevel) {
						i = j;
						break;
					}
					last = binaryTree[j].idx;

				}
				else if (binaryTree[j].level != tmpLevel) {
					last = binaryTree[j - 1].idx;
				}
				int tmp = last - first + 1;
				if (answer.second < tmp) {
					answer.second = tmp;
					answer.first = tmpLevel;
				}
				i = j;
				break;
			}
		}
	}
	cout << answer.first << ' ' << answer.second;
}