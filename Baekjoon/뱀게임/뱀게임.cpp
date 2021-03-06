#include <iostream>
#include <queue>
#include <string>
using namespace std;

int Board[100][100];
queue<pair<int, string>> input;
int time = 0;
int boardSize, appleCnt;

struct Snake {
	int length;
	queue<pair<int, int>> location;
	//first가 x , second가 y
	string direction;
	//UP, DOWN, LEFT, RIGHT
	Snake(int l, int x, int y) {
		length = l;
		location.push(make_pair(x, y));
		direction = "RIGHT";
	}
};

bool is_Collision(Snake& s) {
	if (s.location.back().first < 0 || s.location.back().second < 0 ||
		s.location.back().first == boardSize || s.location.back().second == boardSize) {
		//벽에 부딪힘
		return true;
	}
	else if (Board[s.location.back().second][s.location.back().first] == 2 ||
		(s.location.back().first == s.location.front().first &&
			s.location.back().second == s.location.front().second)) {
		//자기 몸과 부딪힘
		return true;
	}
	return false;
}

bool goTodirection(Snake& s, int cnt, string direction) {
	if (cnt == -1) cnt = 987654321;
	while (cnt-- > 0) {
		//머리 좌표를 갱신해서 push
		if (direction == "UP") {
			s.location.push(make_pair(s.location.back().first, s.location.back().second - 1));
		}
		else if (direction == "DOWN") {
			s.location.push(make_pair(s.location.back().first, s.location.back().second + 1));
		}
		else if (direction == "LEFT") {
			s.location.push(make_pair(s.location.back().first - 1, s.location.back().second));
		}
		else if (direction == "RIGHT") {
			s.location.push(make_pair(s.location.back().first + 1, s.location.back().second));
		}
		if (is_Collision(s)) {
			//충돌 체크
			return false;
		}
		if (Board[s.location.back().second][s.location.back().first] == 1) {
			//몸길이 증가
			s.length += 1;
		}
		else {
			//사과가 아니었으므로 몸길이는 늘어나지 않음
			//현재 꼬리 위치를 0으로 만들고 pop을 해서 꼬리가 다음 좌표로 변경되도록함 
			Board[s.location.front().second][s.location.front().first] = 0;
			s.location.pop();
		}
		Board[s.location.back().second][s.location.back().first] = 2;
		time += 1;
	}
	return true;
}

void move(Snake& s) {
	int cnt = input.front().first;
	if (!goTodirection(s, cnt, "RIGHT")) {
		return;
	}
	//처음
	while (!input.empty()) {
		string next_direction = input.front().second;
		input.pop();
		bool Check;
		if (input.empty()) {
			//다음 방향 입력이 없다면 끝날때까지 돌도록 함
			cnt = -1;
		}
		else {
			//다음 입력 수행 전까지만 수행하면 됨 -> 12 "D" 라면 13부터 방향 전환 = 현재 시간으로 부터 12까지만 next_direction 방향으로 이동
			cnt = input.front().first - time;
		}

		if (next_direction == "D") {
			if (s.direction == "UP") {
				s.direction = "RIGHT";
				Check = goTodirection(s, cnt, "RIGHT");
			}
			else if (s.direction == "DOWN") {
				s.direction = "LEFT";
				Check = goTodirection(s, cnt, "LEFT");
			}
			else if (s.direction == "LEFT") {
				s.direction = "UP";
				Check = goTodirection(s, cnt, "UP");
			}
			else if (s.direction == "RIGHT") {
				s.direction = "DOWN";
				Check = goTodirection(s, cnt, "DOWN");
			}
		}
		else {
			if (s.direction == "UP") {
				s.direction = "LEFT";
				Check = goTodirection(s, cnt, "LEFT");
			}
			else if (s.direction == "DOWN") {
				s.direction = "RIGHT";
				Check = goTodirection(s, cnt, "RIGHT");
			}
			else if (s.direction == "LEFT") {
				s.direction = "DOWN";
				Check = goTodirection(s, cnt, "DOWN");
			}
			else if (s.direction == "RIGHT") {
				s.direction = "UP";
				Check = goTodirection(s, cnt, "UP");
			}
		}
		if (!Check) {
			//게임이 끝나버렸다면 프로그램 종료
			return;
		}
	}
}


int main() {
	Snake s = Snake(1, 0, 0);
	//사과는 1, 빈칸은 0, 몸은 2
	cin >> boardSize >> appleCnt;
	for (int i = 0; i < appleCnt; i++) {
		int x, y;
		cin >> y >> x;
		Board[y - 1][x - 1] = 1;
	}
	Board[0][0] = 2;
	int l;
	cin >> l;
	for (int i = 0; i < l; i++) {
		int sec;
		string direction;
		cin >> sec >> direction;
		input.push(make_pair(sec, direction));
	}
	move(s);
	cout << time + 1;
}