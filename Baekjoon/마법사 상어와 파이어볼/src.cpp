#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;
struct fireball {
	int row, col, mass, spd, dir;
};
struct sumball {
	int mass, spd, dir;
};
int dir[8][2] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
int n, m, k;
int main() {
	cin >> n >> m >> k;
	queue<fireball> prev;
	for (int i = 0; i < m; i++) {
		fireball tmp;
		cin >> tmp.row >> tmp.col >> tmp.mass >> tmp.spd >> tmp.dir;
		tmp.row -= 1;
		tmp.col -= 1;
		prev.push(tmp);
	}
	while (k-- > 0) {
		unordered_map<int, vector<sumball>> check;
		while (!prev.empty()) {
			fireball cur = prev.front();
			prev.pop();
			cur.row = (cur.row + (cur.spd * dir[cur.dir][0])) % n;
			cur.col = (cur.col + (cur.spd * dir[cur.dir][1])) % n;
			if (cur.row < 0) {
				cur.row += n;
			}
			if (cur.col < 0) {
				cur.col += n;
			}
			check[(cur.row * 100 + cur.col)].push_back({ cur.mass,cur.spd,cur.dir });
		}
		for (auto it : check) {
			int row = (it.first / 1000) * 10 + (it.first % 1000) / 100;
			int col = it.first % 100;
			sumball tmp2 = it.second.front();
			if (it.second.size() > 1) {
				int checkDir = (it.second.front().dir % 2);
				int checkDircnt = 1;
				for (int i = 1; i < it.second.size(); i++) {
					if (checkDir == (it.second[i].dir % 2)) {
						checkDircnt++;
					}
					tmp2.mass += it.second[i].mass;
					tmp2.spd += it.second[i].spd;
				}
				//4개로 나눈다.
				int new_mass = tmp2.mass / 5;
				int new_spd = tmp2.spd / it.second.size();
				if (new_mass == 0) {
					continue;
				}
				if (checkDircnt == it.second.size()) {
					//방향은 0,2,4,6
					prev.push({ row,col,new_mass,new_spd,0 });
					prev.push({ row,col,new_mass,new_spd,2 });
					prev.push({ row,col,new_mass,new_spd,4 });
					prev.push({ row,col,new_mass,new_spd,6 });
				}
				else {
					//방향은 1,3,5,7
					prev.push({ row,col,new_mass,new_spd, 1 });
					prev.push({ row,col,new_mass,new_spd, 3 });
					prev.push({ row,col,new_mass,new_spd, 5 });
					prev.push({ row,col,new_mass,new_spd, 7 });
				}
			}
			else {
				prev.push({ row,col,tmp2.mass,tmp2.spd,tmp2.dir });
			}
		}
	}
	int answer = 0;
	while (!prev.empty()) {
		answer += prev.front().mass;
		prev.pop();
	}
	cout << answer;
}