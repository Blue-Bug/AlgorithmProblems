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
	//first�� x , second�� y
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
		//���� �ε���
		return true;
	}
	else if (Board[s.location.back().second][s.location.back().first] == 2 ||
		(s.location.back().first == s.location.front().first &&
			s.location.back().second == s.location.front().second)) {
		//�ڱ� ���� �ε���
		return true;
	}
	return false;
}

bool goTodirection(Snake& s, int cnt, string direction) {
	if (cnt == -1) cnt = 987654321;
	while (cnt-- > 0) {
		//�Ӹ� ��ǥ�� �����ؼ� push
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
			//�浹 üũ
			return false;
		}
		if (Board[s.location.back().second][s.location.back().first] == 1) {
			//������ ����
			s.length += 1;
		}
		else {
			//����� �ƴϾ����Ƿ� �����̴� �þ�� ����
			//���� ���� ��ġ�� 0���� ����� pop�� �ؼ� ������ ���� ��ǥ�� ����ǵ����� 
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
	//ó��
	while (!input.empty()) {
		string next_direction = input.front().second;
		input.pop();
		bool Check;
		if (input.empty()) {
			//���� ���� �Է��� ���ٸ� ���������� ������ ��
			cnt = -1;
		}
		else {
			//���� �Է� ���� �������� �����ϸ� �� -> 12 "D" ��� 13���� ���� ��ȯ = ���� �ð����� ���� 12������ next_direction �������� �̵�
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
			//������ �������ȴٸ� ���α׷� ����
			return;
		}
	}
}


int main() {
	Snake s = Snake(1, 0, 0);
	//����� 1, ��ĭ�� 0, ���� 2
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