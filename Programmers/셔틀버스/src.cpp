#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iomanip> 
#include <algorithm>
using namespace std;

string solution(int n, int t, int m, vector<string> timetable) {
	string answer = "";

	//n은 셔틀 운행 횟수
	//t는 운행 간격
	//m은 셔틀에 탈 수 있는 크루 수
	//timetable은 크루들이 대기열에 서는 시간
	sort(timetable.begin(), timetable.end());
	unordered_map <string, vector<string>> shuttle;
	string shuttle_time = "09:00";
	string end_time = shuttle_time;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (timetable.empty()) {
				break;
			}
			if (timetable.front() <= shuttle_time) {
				shuttle[shuttle_time].push_back(timetable.front());
				timetable.erase(timetable.begin());
			}			
		}
		stringstream ss;
		stringstream ss2;
		ss.str(shuttle_time);
		int hour;
		char tmp;
		int minutes;
		ss >> hour >> tmp >> minutes;
		minutes += t;
		if (minutes >= 60) {
			minutes -= 60;
			hour += 1;
		}

		ss2 << setw(2) << setfill('0') << hour << ":";
		ss2 << setw(2) << setfill('0') << minutes;
		end_time = shuttle_time;
		shuttle_time = ss2.str();
	}

	if (shuttle[end_time].size() == m) {
		//마지막 버스에 사람이 꽉찼다면
		stringstream ss;
		stringstream ss2;
		ss.str(shuttle[end_time].back());
		int hour;
		char tmp;
		int minutes;
		ss >> hour >> tmp >> minutes;
		minutes -= 1;
		if (minutes < 0) {
			minutes += 60;
			hour -= 1;
		}
		ss2 << setw(2) << setfill('0') << hour << ":";
		ss2 << setw(2) << setfill('0') << minutes;
		answer = ss2.str();
	}
	else {
		answer = end_time;
	}

	return answer;
}

int main() {
	solution(2, 10, 2, { "09:10", "09:09", "08:00" });
}