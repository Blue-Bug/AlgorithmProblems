#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//ó�� ���� -> ������ ���ķ� Heap ����ϰ� ���� Ž��(y�켱 ��x ����) 
// -> �ܼ��ϰ� �Ϸ��� �ߴµ� ������ �ʹ� �������� 
//�״��� ���� -> ���� ����Ʈ���� ���鵵�� �־��������Ƿ� �׳� Ʈ���� ����(x�� �����ϰ� Ʈ�� ���鶧 y���� ���� ��(��Ʈ)�� ����ø�)

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

//�Ķ���Ϳ� &�߿� -> �Ƚᰡ���� �ð��ʰ� ��
Tree* make_Tree(vector<vector<Node*>>& tmp, int first, int last) {
	//Ʈ�� ����� ������
	if (first > last) {
		//����Ʈ ó�� ��踦 ����� �� ���� ���� �����Ƿ� NULL ����
		return NULL;
	}
	//��ȯ�� Ʈ��
	Tree* mTree = new Tree();

	//��Ʈ ��� ã�Ƴ�(y���� ���� ū�� ��Ʈ�� ��)
	int max = tmp[first].front()->y;
	int cut = first;
	for (int i = first + 1; i <= last; i++) {
		if (max < tmp[i][0]->y) {
			cut = i;
			max = tmp[i][0]->y;
		}
	}
	mTree->cur = tmp[cut][0];
	//x���� �̹� ���ĵǾ� �����Ƿ� ���� ��� ��Ʈ��带 �������� ���� �������� ����������
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
	//x���� ���� ���� �������� ���ϰ� y������ ������ ���Ѵ�
	vector<vector<int>> answer;

	vector<vector<Node*>> tmp;
	Tree* answer_Tree = new Tree;
	vector<int> pre;
	vector<int> post;

	//�� ��� ������ ��� ���ο� ���� ����
	for (int i = 0; i < nodeinfo.size(); i++) {
		Node* n = new Node();
		n->node_num = i + 1;
		n->x = nodeinfo[i][0];
		n->y = nodeinfo[i][1];
		tmp.push_back({ n });
	}
	//x���� �켱���� ���� 
	sort(tmp.begin(), tmp.end(), compare);

	//Ʈ���� ���� �޾ƿ�
	answer_Tree = make_Tree(tmp, 0, tmp.size() - 1);

	//������� Ʈ���� ������ ����,���� ��ȸ
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
