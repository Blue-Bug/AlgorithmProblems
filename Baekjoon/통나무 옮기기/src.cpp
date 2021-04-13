#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct wood {
	int x, y;
	int cnt;
	bool dir;
};

int N;
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
bool visited[50][50][2];
char board[50][50];

void startSetting(wood &first_loc, wood &dest_loc) {
	int find_middle = 0;
	int find_middle2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 'B') {
				if (find_middle == 0) {
					first_loc.x = j;
					first_loc.y = i;
				}
				else if(find_middle == 1){
					if (first_loc.x == j) {
						//세로임
						first_loc.dir = 1;
					}
					else if (first_loc.y == i) {
						//가로임
						first_loc.dir = 0;
					}
					first_loc.x = j;
					first_loc.y = i;
					first_loc.cnt = 0;
				}
				find_middle++;
			}
			if (board[i][j] == 'E') {
				if (find_middle2 == 0) {
					dest_loc.x = j;
					dest_loc.y = i;
				}
				else if(find_middle2 == 1){
					if (dest_loc.x == j) {
						//세로임
						dest_loc.dir = 1;
					}
					else if (dest_loc.y == i) {
						//가로임
						dest_loc.dir = 0;
					}
					dest_loc.x = j;
					dest_loc.y = i;
					dest_loc.cnt = 0;
				}
				find_middle2++;
			}
		}
	}
}

bool isPossiblePos(int x, int y) {
	if (x >= 0 && x < N && y >= 0 && y < N && board[y][x] != '1') {
		return true;
	}
	return false;
}

int solution() {
	wood first_loc;
	wood dest_loc;
	startSetting(first_loc, dest_loc);
	queue<wood> q;
	//회전시 3*3 정사각형의 구역에 단 한 그루의 나무도 없어야만 한다고 한다.
	q.push(first_loc);

	while (!q.empty()) {
		wood cur_loc = q.front();
		q.pop();
		//bfs이기 때문에 항상 최소가 보장된다.
		if (cur_loc.dir == dest_loc.dir && cur_loc.x == dest_loc.x && cur_loc.y == dest_loc.y) {
			return cur_loc.cnt;
		}
		if (visited[cur_loc.y][cur_loc.x][cur_loc.dir] == true) {
			continue;
		}
		visited[cur_loc.y][cur_loc.x][cur_loc.dir] = true;
		//회전
		if (cur_loc.dir == 0) {
			//세로로 회전시키기
			if (isPossiblePos(cur_loc.x - 1, cur_loc.y - 1) &&
				isPossiblePos(cur_loc.x, cur_loc.y - 1) &&
				isPossiblePos(cur_loc.x + 1, cur_loc.y - 1) &&
				isPossiblePos(cur_loc.x - 1, cur_loc.y + 1) &&
				isPossiblePos(cur_loc.x, cur_loc.y + 1) && 
				isPossiblePos(cur_loc.x + 1, cur_loc.y + 1)) {
				wood next_loc = cur_loc;
				next_loc.cnt++;
				next_loc.dir = 1;
				q.push(next_loc);
			}
		}
		else {
			//가로로 회전시키기
			if (isPossiblePos(cur_loc.x - 1, cur_loc.y - 1) &&
				isPossiblePos(cur_loc.x - 1, cur_loc.y) &&
				isPossiblePos(cur_loc.x - 1, cur_loc.y + 1) &&
				isPossiblePos(cur_loc.x + 1, cur_loc.y - 1) &&
				isPossiblePos(cur_loc.x + 1, cur_loc.y) &&
				isPossiblePos(cur_loc.x + 1, cur_loc.y + 1)) {
				wood next_loc = cur_loc;
				next_loc.cnt++;
				next_loc.dir = 0;
				q.push(next_loc);
			}
		}
		//상하좌우 이동
		for (int i = 0; i < 4; i++) {
			wood next_loc = cur_loc;
			next_loc.y += dir[i][0];
			next_loc.x += dir[i][1];
			next_loc.cnt++;
			if (cur_loc.dir == 0) {
				//가로라면
				if (isPossiblePos(next_loc.x - 1, next_loc.y) &&
					isPossiblePos(next_loc.x, next_loc.y) &&
					isPossiblePos(next_loc.x + 1, next_loc.y)) {
					q.push(next_loc);
				}
			}
			else if (cur_loc.dir == 1) {
				//세로라면
				if (isPossiblePos(next_loc.x, next_loc.y - 1) &&
					isPossiblePos(next_loc.x, next_loc.y) &&
					isPossiblePos(next_loc.x, next_loc.y + 1)) {
					q.push(next_loc);
				}
			}
		}
	}
	//이동이 불가능하면 0 출력
	return 0;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	cout << solution();
	return 0;
}
