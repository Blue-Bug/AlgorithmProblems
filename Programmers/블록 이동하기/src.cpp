#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<vector<vector<int>>> visit;
struct mBlock{
	int y1,x1,y2,x2,cnt;
};

bool isPossible(mBlock mb, vector<vector<int>>& board) {
	//������ ��ǥ���� üũ
	if (mb.y1 >= 0 && mb.y1 <= board.size() - 1 && mb.x1 >= 0 && mb.x1 <= board.size() - 1 &&
		mb.y2 >= 0 && mb.y2 <= board.size() - 1 && mb.x2 >= 0 && mb.x2 <= board.size() - 1 && 
		board[mb.y1][mb.x1] == 0 && board[mb.y2][mb.x2] == 0) {
		return true;
	}
	return false;
}

int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };

void move(mBlock mb,queue<mBlock>& q, vector<vector<int>>& board) {
	for (int i = 0; i < 4; i++) {
		//�����¿�� �̵�
		mBlock next_mb;
		next_mb.y1 = mb.y1 + dir[i][0];
		next_mb.y2 = mb.y2 + dir[i][0];
		next_mb.x1 = mb.x1 + dir[i][1];
		next_mb.x2 = mb.x2 + dir[i][1];
		next_mb.cnt = mb.cnt + 1;
		if (isPossible(next_mb, board)) {
			q.push(next_mb);
		}
	}
}
int bfs(vector<vector<int>>& board) {
	queue <mBlock> q;
	mBlock tmp;
	tmp.y1 = 0;
	tmp.x1 = 0;
	tmp.y2 = 0;
	tmp.x2 = 1;
	tmp.cnt = 0;
	q.push(tmp);

	while (!q.empty()) {
		mBlock mb = q.front();
		q.pop();
		if ((mb.y1 == board.size() - 1 && mb.x1 == board.size() - 1) ||
			(mb.y2 == board.size() - 1 && mb.x2 == board.size() - 1)) {
			//�������� ������ ��ǥ�� cnt�� ����
			return mb.cnt;
		}
		//(y2,x2) �������� ��ȸ��, �Ʒ�ȸ�� 
		//(y1,x1) �������� ��ȸ��, �Ʒ�ȸ��
		//(ȸ������ 1�� �� �ҿ�ǹǷ� cnt�� �����Ҷ� 1�� ��������)
		if (mb.y2 == mb.y1) {
			//���� ���� ��ǥ���
			if (visit[mb.y1][mb.x1][0] == 1 && visit[mb.y2][mb.x2][0] == 1) {
				//�����϶� �湮�� �迭üũ
				continue;
			}
			visit[mb.y1][mb.x1][0] = 1;
			visit[mb.y2][mb.x2][0] = 1;

			//���� ���ι�����
			//y2,x2 �������� ���� ȸ��
			for (int i = 0; i < 2; i++) {
				mBlock next_mb = mb;
				if (i == 1) {
					next_mb.y1 = mb.y2 - 1;
				}
				else {
					next_mb.y1 = mb.y2 + 1;
				}
				next_mb.x1 = mb.x2;
				next_mb.cnt = mb.cnt + 1;

				if (isPossible(next_mb, board) && board[next_mb.y1][mb.x1] == 0) {
					//ȸ���� �������� üũ
					q.push(next_mb);
				}
			}
			//y1,x1 �������� ȸ��
			for (int i = 0; i < 2; i++) {
				mBlock next_mb = mb;
				if (i == 1) {
					next_mb.y2 = mb.y1 - 1;
				}
				else {
					next_mb.y2 = mb.y1 + 1;
				}
				next_mb.x2 = mb.x1;
				next_mb.cnt = mb.cnt + 1;

				if (isPossible(next_mb, board) && board[next_mb.y2][mb.x2] == 0) {
					//ȸ���� �������� üũ
					q.push(next_mb);
				}
			}
		}
		else {
			//���� ���� ��ǥ���
			if (visit[mb.y1][mb.x1][1] == 1 && visit[mb.y2][mb.x2][1] == 1) {
				//�����϶� �湮�� �迭üũ
				continue;
			}
			visit[mb.y1][mb.x1][1] = 1;
			visit[mb.y2][mb.x2][1] = 1;

			//���� ���ι�����
			//y2,x2 ����
			for (int i = 0; i < 2; i++) {
				mBlock next_mb = mb;
				if (i == 1) {
					next_mb.x1 = mb.x1 - 1;
				}
				else {
					next_mb.x1 = mb.x1 + 1;
				}
				next_mb.y1 = mb.y2;
				next_mb.cnt = mb.cnt + 1;
				if (isPossible(next_mb, board) && board[mb.y1][next_mb.x1] == 0) {
					//ȸ���� �������� üũ
					q.push(next_mb);
				}
			}
			//y1,x1 ����
			for (int i = 0; i < 2; i++) {
				mBlock next_mb = mb;
				if (i == 1) {
					next_mb.x2 = mb.x2 - 1;
				}
				else {
					next_mb.x2 = mb.x2 + 1;
				}
				next_mb.y2 = mb.y1;
				next_mb.cnt = mb.cnt + 1;
				if (isPossible(next_mb, board) && board[mb.y2][next_mb.x2] == 0) {
					//ȸ���� �������� üũ
					q.push(next_mb);
				}
			}
		}
		//�����¿� �̵�
		move(mb,q, board);
	}
}

int solution(vector<vector<int>> board) {
	int answer = 0;
	vector<vector<vector<int>>> tmp(board.size(), vector<vector<int>>(board.size(), vector<int>(2,0)));
	visit = tmp;
	answer = bfs(board);
	return answer;
}