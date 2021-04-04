#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iomanip> 
using namespace std;

struct Time {
	string date;
	int hours;
	int minutes;
	int seconds;
	int Millis;
};

//시간 증감 처리함수
void processTime(Time &time) {
	if (time.Millis < 0) {
		time.Millis += 1000;
		time.seconds -= 1;
	}
	if (time.seconds < 0) {
		time.seconds += 60;
		time.minutes -= 1;
	}
	if (time.minutes < 0) {
		time.minutes += 60;
		time.hours -= 1;
	}
	if (time.hours < 0) {
		time.hours += 24;
		time.date = "2016-09-14";
	}
	if (time.Millis > 1000) {
		time.Millis -= 1000;
		time.seconds += 1;
	}
	if (time.seconds > 60) {
		time.seconds -= 60;
		time.minutes += 1;
	}
	if (time.minutes > 60) {
		time.minutes -= 60;
		time.hours += 1;
	}
	if (time.hours > 24) {
		time.hours -= 24;
		time.date = "2016-09-16";
	}
}


//시간 구조체를 전달받아 stringstream에 형식을 맞춰 넣어주는 함수
void makeTimeString (stringstream& ss, Time time) {
	ss << time.date + " ";
	ss << setw(2) << setfill('0') << time.hours << ":";
	ss << setw(2) << setfill('0') << time.minutes << ":";
	ss << setw(2) << setfill('0') << time.seconds << ".";
	ss << setw(3) << setfill('0') << time.Millis;
}

int solution(vector<string> lines) {
	int answer = 0;
	stringstream ss;
	stringstream ss2;
	vector<pair<string, string>> logs;

	for (auto log : lines) {
		//전달 받은 line 벡터에서 로그를 하나씩 꺼내며 시작시간을 계산한다.
		ss.str(log);
		string date;
		string endTime;
		char tmp;
		int processSeconds;
		int processMillis;
		ss >> date >> endTime >> processSeconds >> tmp >> processMillis;

		//끝나는 시간을 구조체에 넣는다.
		ss2.str(endTime);
		Time endTimeStruct;
		endTimeStruct.date = date;
		ss2 >> endTimeStruct.hours >> tmp >> 
			endTimeStruct.minutes >> tmp >> 
			endTimeStruct.seconds >> tmp >> 
			endTimeStruct.Millis;

		//시작 시간을 계산하여 구조체에 넣는다.
		Time startTimeStruct;
		startTimeStruct.date = endTimeStruct.date;
		startTimeStruct.hours = endTimeStruct.hours;
		startTimeStruct.minutes = endTimeStruct.minutes;
		startTimeStruct.Millis = endTimeStruct.Millis - processMillis + 1;
		startTimeStruct.seconds = endTimeStruct.seconds - processSeconds;
		processTime(startTimeStruct);

		//시작 시간을 stringstream에 형식을 맞춰 넣어준다.
		stringstream startTime;
		makeTimeString(startTime,startTimeStruct);
		
		//logs 벡터에 시작시간과 끝나는 시간을 넣어준다.
		//("2016-09-15 20:59:57.071", "2016-09-15 20:59:57.421")
		logs.push_back({ startTime.str(), date + " " + endTime });
		ss.clear();
		ss2.clear();
	}

	for (int i = 0; i < logs.size(); i++) {
		//로그 시작 시간을 가져옴
		ss.str(logs[i].first);
		string date;
		string timeString;
		char tmp;
		ss >> date >> timeString;

		ss2.str(timeString);
		Time startTimeStruct1;

		//로그 시작 시간
		ss2 >> startTimeStruct1.hours >> tmp >>
			startTimeStruct1.minutes >> tmp >>
			startTimeStruct1.seconds >> tmp >>
			startTimeStruct1.Millis;
		startTimeStruct1.date = date;

		ss.clear();
		ss2.clear();

		//로그 끝 시간을 가져옴
		ss.str(logs[i].second);
		ss >> date >> timeString;

		ss2.str(timeString);
		Time startTimeStruct2;

		//로그 끝 시간
		ss2 >> startTimeStruct2.hours >> tmp >>
			startTimeStruct2.minutes >> tmp >>
			startTimeStruct2.seconds >> tmp >>
			startTimeStruct2.Millis;
		startTimeStruct2.date = date;

		Time endTimeStruct1 = startTimeStruct1;
		stringstream endCheck1;
		//간격을 1초로 늘림
		endTimeStruct1.Millis += 999;
		processTime(endTimeStruct1);
		makeTimeString(endCheck1, endTimeStruct1);

		Time endTimeStruct2 = startTimeStruct2;
		stringstream endCheck2;
		//간격을 1초로 늘림
		endTimeStruct2.Millis += 999;
		processTime(endTimeStruct2);
		makeTimeString(endCheck2, endTimeStruct2);

		int res1 = 1;
		int res2 = 1;
		for (int j = 0; j < logs.size(); j++) {
			if (j == i) continue;
			//1번 구간과 2번 구간을 동시에 비교 
			//자기 자신을 포함하면서 1초동안 얼마나 많은 로그가 포함되는지 체크
			//1번 구간은 log[i]의 시작시간부터 1초
			//2번 구간은 log[i]의 끝시간부터 1초
			if (!((logs[i].first > logs[j].second) || (endCheck1.str() < logs[j].first))) {
				//1번 구간 안에 들어오면
				res1++;
			}
			if (!((logs[i].second > logs[j].second) || (endCheck2.str() < logs[j].first))) {
				//2번 구간 안에 들어오면
				res2++;
			}
		}
		if (answer < res1) {
			answer = res1;
		}
		if (answer < res2) {
			answer = res2;
		}
		ss.clear();
		ss2.clear();
	}
	return answer;
}