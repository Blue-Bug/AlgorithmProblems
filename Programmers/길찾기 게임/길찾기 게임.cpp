#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//처음 생각 -> 간단한 정렬로 Heap 비슷하게 만들어서 탐색(y우선 후x 정렬) 
// -> 단순하게 하려고 했는데 오히려 너무 복잡해짐 
//그다음 생각 -> 값이 이진트리를 만들도록 주어져있으므로 그냥 트리로 구현(x만 정렬하고 트리 만들때 y값을 보고 위(루트)로 끌어올림)

struct Node {
	int x,
		y,
		node_num;
};

struct Tree {
	Tree* left;
	Tree* right;
	Node* cur;
};

bool compare(vector<Node*> a, vector<Node*> b) {
	return a.front()->x < b.front()->x;
}

//파라미터에 &중요 -> 안써가지고 시간초과 됨
Tree* make_Tree(vector<vector<Node*>>& tmp, int first, int last) {
	//트리 만들어 버리기
	if (first > last) {
		//퀵소트 처럼 경계를 벗어나면 더 넣을 것이 없으므로 NULL 리턴
		return NULL;
	}
	//반환할 트리
	Tree* mTree = new Tree();

	//루트 노드 찾아냄(y값이 가장 큰게 루트가 됨)
	int max = tmp[first].front()->y;
	int cut = first;
	for (int i = first + 1; i <= last; i++) {
		if (max < tmp[i][0]->y) {
			cut = i;
			max = tmp[i][0]->y;
		}
	}
	mTree->cur = tmp[cut][0];
	//x값이 이미 정렬되어 있으므로 현재 골라낸 루트노드를 기준으로 왼쪽 오른쪽을 나눠버린다
	mTree->left = make_Tree(tmp, first, cut - 1);
	mTree->right = make_Tree(tmp, cut + 1, last);
	return mTree;
}

void preorder(vector<int>& pre, Tree* tree) {
	if (tree == NULL) {
		return;
	}
	pre.push_back(tree->cur->node_num);
	preorder(pre, tree->left);
	preorder(pre, tree->right);
}
void postorder(vector<int>& post, Tree* tree) {
	if (tree == NULL) {
		return;
	}
	postorder(post, tree->left);
	postorder(post, tree->right);
	post.push_back(tree->cur->node_num);
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	//x값에 따라 왼쪽 오른쪽을 정하고 y값으로 레벨을 정한다
	vector<vector<int>> answer;

	vector<vector<Node*>> tmp;
	Tree* answer_Tree = new Tree;
	vector<int> pre;
	vector<int> post;

	//각 노드 정보를 담아 새로운 벡터 생성
	for (int i = 0; i < nodeinfo.size(); i++) {
		Node* n = new Node();
		n->node_num = i + 1;
		n->x = nodeinfo[i][0];
		n->y = nodeinfo[i][1];
		tmp.push_back({ n });
	}
	//x값을 우선으로 정렬 
	sort(tmp.begin(), tmp.end(), compare);

	//트리를 만들어서 받아옴
	answer_Tree = make_Tree(tmp, 0, tmp.size() - 1);

	//만들어진 트리를 가지고 전위,후위 순회
	preorder(pre, answer_Tree);
	postorder(post, answer_Tree);
	answer.push_back(pre);
	answer.push_back(post);
	return answer;
}

int main() {
	vector<vector<int>> nodeinfo = { {5,3} ,{11,5},{13,3},{3,5},{6,1},{1,3}, {8, 6}, {7, 2},{2, 2} };
	vector<vector<int>> sol = solution(nodeinfo);
	for (int i = 0; i < sol[0].size(); i++) {
		cout << sol[0][i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < sol[1].size(); i++) {
		cout << sol[1][i] << ' ';
	}
}
