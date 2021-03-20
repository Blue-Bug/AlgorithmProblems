#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct buildStructure {
	bool existPillar;
	bool existBeam;
	buildStructure(bool a, bool b) {
		existPillar = a; existBeam = b;
	}
};

bool compare(vector<int> a, vector<int> b) {
	//x,y,a
	if (a[0] == b[0]) {
		if (a[1] == b[1]) {
			return a[2] < b[2];
		}
		return a[1] < b[1];
	}
	return a[0] < b[0];
}

bool isRightPosition(int x, int y, int n) {
	if (x > -1 && x < n && y > -1 && y < n) {
		return true;
	}
	return false;
}
bool checkBeamCondition(vector<vector<buildStructure>> &building, int y) {
	//해당 y 좌표의 x좌표 0번부터 n까지 보가 있는지 스캔
	vector<pair<int, int>> Beams;
	for (int i = 0; i < building.size(); i++) {
		for (int j = 0; j < building.size(); j++) {
			if (building[i][j].existBeam) {
				Beams.push_back({ j,i });
			}
		}
	}
	if (Beams.empty()) {
		return true;
	}
	for (auto beam : Beams) {
		bool flag = false;
		//양쪽이 연결되어 있는가
		if (isRightPosition(beam.first - 1, beam.second, building.size()) && building[beam.second][beam.first - 1].existBeam
			&& isRightPosition(beam.first + 1, beam.second, building.size()) && building[beam.second][beam.first + 1].existBeam) {
			flag = true;
		}
		//양쪽 아래에 기둥이 하나라도 있는가
		else if ((isRightPosition(beam.first, beam.second - 1, building.size()) && building[beam.second - 1][beam.first].existPillar)
			|| (isRightPosition(beam.first + 1, beam.second - 1, building.size()) && building[beam.second - 1][beam.first + 1].existPillar)) {
			flag = true;
		}
		if (!flag) {
			return false;
		}
	}
	return true;
}

bool checkPillarCondition(vector<vector<buildStructure>> &building, int y) {
	//해당 y와 y+1 좌표 0번부터 n번까지 기둥이 있는지 스캔
	vector<pair<int, int>> Pillars;
	for (int i = 0; i < building.size(); i++) {
		for (int j = 0; j < building.size(); j++) {
			if (building[i][j].existPillar) {
				Pillars.push_back({ j,i });
			}
		}
	}
	if (Pillars.empty()) {
		return true;
	}
	for (auto pillar : Pillars) {
		bool flag = false;
		if (pillar.second == 0) {
			//기둥 아래가 바닥인가
			flag = true;
		}
		else if (isRightPosition(pillar.first, pillar.second - 1, building.size()) 
			&& building[pillar.second - 1][pillar.first].existPillar) {
			//기둥 아래에 기둥이 있는가
			flag = true;
		}
		else if (building[pillar.second][pillar.first].existBeam
				|| (isRightPosition(pillar.first - 1, pillar.second, building.size()) 
				&& building[pillar.second][pillar.first - 1].existBeam)) {
			//기둥 아래에 보가 있는가
			flag = true;
		}
		if (!flag) {
			return false;
		}
	}
	return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	vector<vector<int>> answer;
	vector<vector<buildStructure>> building(n+1, vector<buildStructure>(n+1, buildStructure(false, false)));
	for (auto build_order : build_frame) {
		int x = build_order[0];
		int y = build_order[1];
		int a = build_order[2];
		//0은 기둥 1은 보
		int b = build_order[3];
		//0은 삭제 1이 설치
		
		if (b == 0) {
			//삭제 명령
			if (a == 0) {
				//기둥을 삭제한다면
				building[y][x].existPillar = false;
				if (checkBeamCondition(building, y) && checkPillarCondition(building, y)) {
					continue;
				}
				building[y][x].existPillar = true;
			}
			else if (a == 1) {
				//보를 삭제한다면
				building[y][x].existBeam = false;
				if (checkBeamCondition(building, y) && checkPillarCondition(building, y)) {
					continue;
				}
				building[y][x].existBeam = true;
			}
		}
		else if (b == 1) {
			//설치 명령
			if (a == 0) {
				//기둥을 설치한다면
				building[y][x].existPillar = true;
				if (checkBeamCondition(building, y) && checkPillarCondition(building, y)) {
					continue;
				}
				building[y][x].existPillar = false;
			}
			else if (a == 1) {
				//보를 설치한다면
				building[y][x].existBeam = true;
				if (checkBeamCondition(building, y) && checkPillarCondition(building, y)) {
					continue;
				}
				building[y][x].existBeam = false;
			}
		}
	}
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (building[i][j].existBeam) {
				answer.push_back({ j,i,1 });
			}
			if (building[i][j].existPillar) {
				answer.push_back({ j,i,0 });
			}
		}
	}
	sort(answer.begin(), answer.end(), compare);
	return answer;
}

int main() {
	solution(5, { {1, 0, 0, 1},{1, 1, 1, 1},{2, 1, 0, 1},{2, 2, 1, 1},{5, 0, 0, 1},{5, 1, 0, 1},{4, 2, 1, 1},{3, 2, 1, 1} });
}