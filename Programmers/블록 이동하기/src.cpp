#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<vector<vector<int>>> visit;
struct mBlock{
	int y1,x1,y2,x2,cnt;
};

bool isPossible(mBlock mb, vector<vector<int>>& board) {
	//가능한 좌표인지 체크
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
		//상하좌우로 이동
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
			//마지막에 도착한 좌표면 cnt값 리턴
			return mb.cnt;
		}
		//(y2,x2) 기준으로 위회전, 아래회전 
		//(y1,x1) 기준으로 위회전, 아래회전
		//(회전에는 1이 더 소요되므로 cnt를 저장할때 1을 더해주자)
		if (mb.y2 == mb.y1) {
			//현재 가로 좌표라면
			if (visit[mb.y1][mb.x1][0] == 1 && visit[mb.y2][mb.x2][0] == 1) {
				//가로일때 방문한 배열체크
				continue;
			}
			visit[mb.y1][mb.x1][0] = 1;
			visit[mb.y2][mb.x2][0] = 1;

			//현재 가로방향임
			//y2,x2 기준으로 먼저 회전
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
					//회전이 가능한지 체크
					q.push(next_mb);
				}
			}
			//y1,x1 기준으로 회전
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
					//회전이 가능한지 체크
					q.push(next_mb);
				}
			}
		}
		else {
			//현재 세로 좌표라면
			if (visit[mb.y1][mb.x1][1] == 1 && visit[mb.y2][mb.x2][1] == 1) {
				//세로일때 방문한 배열체크
				continue;
			}
			visit[mb.y1][mb.x1][1] = 1;
			visit[mb.y2][mb.x2][1] = 1;

			//현재 세로방향임
			//y2,x2 먼저
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
					//회전이 가능한지 체크
					q.push(next_mb);
				}
			}
			//y1,x1 기준
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
					//회전이 가능한지 체크
					q.push(next_mb);
				}
			}
		}
		//상하좌우 이동
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