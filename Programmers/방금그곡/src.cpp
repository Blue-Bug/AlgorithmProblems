#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, string> infoMap;

void processInfo(string musicInfo) {
	//',' 문자를 기준으로 파싱하며 map에 정보를 담는다.
	//인덱스 0은 시작시간, 1은 종료시간, 2는 제목, 3은 악보
	infoMap[0] = "";
	infoMap[1] = "";
	infoMap[2] = "";
	infoMap[3] = "";
	string tmp = "";
	int idx = 0;
	for (int i = 0; i < musicInfo.size() + 1; i++) {
		if (musicInfo[i] == ',' || i == musicInfo.size()) {
			infoMap[idx++] = tmp;
			tmp = "";
		}
		else {
			tmp += musicInfo[i];
		}
	}
}

int processTime() {
	//시간 처리 함수
	//시작 시간 처리
	int start_hour = ((infoMap[0].substr(0, 1)[0] - 48) * 10)
		+ ((infoMap[0].substr(1, 1).c_str()[0] - 48) * 1);
	int start_minute = ((infoMap[0].substr(3, 1)[0] - 48) * 10)
		+ ((infoMap[0].substr(4, 1)[0] - 48) * 1);
	//종료 시간 처리
	int end_hour = ((infoMap[1].substr(0, 1)[0] - 48) * 10)
		+ ((infoMap[1].substr(1, 1)[0] - 48) * 1);
	int end_minute = ((infoMap[1].substr(3, 1)[0] - 48) * 10)
		+ ((infoMap[1].substr(4, 1)[0] - 48) * 1);

	//재생 시간 처리
	//10:14 12:02 -> 2 :-12 ->  1 : 48 
	//13:50 14:00 -> 1 :-50 -> 0 : 10
	int play_hour = end_hour - start_hour;
	int play_minute = end_minute - start_minute;
	if (play_minute < 0) {
		play_minute = 60 + play_minute;
		play_hour -= 1;
	}

	//총 재생시간을 분으로 변환해서 반환
	return play_minute + (play_hour * 60);
}

string processChords() {
	//재생시간에 따라 악보를 완성
	string chords = "";

	//재생 시간을 받아옴
	int countTime = processTime();
	int idx = 0;
	//C, C#, D, D#, E, F, F#, G, G#, A, A#, B 
	//#같은게 있으니 전부 봐야됨
	while (countTime-- > 0) {
		//idx가 마지막 위치를 넘어가면 맨 앞으로 초기화
		if (idx >= infoMap[3].size()) {
			idx = 0;
		}
		//코드 뒤에 #이 있으면 추가하고 idx 증가
		if (idx != (infoMap[3].size() - 1) && (infoMap[3][idx] == 'C' || infoMap[3][idx] == 'D'
			|| infoMap[3][idx] == 'F' || infoMap[3][idx] == 'G' || infoMap[3][idx] == 'A')
			&& infoMap[3][idx + 1] == '#') {
			chords += infoMap[3][idx];
			chords += infoMap[3][idx + 1];
			idx = idx + 2;
		}
		else {
			chords += infoMap[3][idx++];
		}
	}

	//완성된 악보를 반환
	return chords;
}

string compareChords(string m, string chords) {
	string cutMelody = "";
	string answer = "";
	int melodyCnt = 0;
	int chordsCnt = 0;
	//기억한 멜로디의 코드개수를 세어서 저장
	for (int i = 0; i < m.size(); i++) {
		if (i != (m.size() - 1) && (m[i] == 'C' || m[i] == 'D'
			|| m[i] == 'F' || m[i] == 'G' || m[i] == 'A')
			&& m[i + 1] == '#') {
			i = i + 1;
		}
		melodyCnt++;
	}
	//기억한 멜로디와 재생된 노래의 코드길이가 같다면 바로 비교
	if (m.size() == chords.size() && m == chords) {
		answer = infoMap[2];
		return answer;
	}
	else if (m.size() < chords.size()) {
		for (int i = 0; i < chords.size(); i++) {
			//재생된 노래의 코드를 기억한 멜로디 코드개수와 같을때까지 잘라냄
			if (i != (chords.size() - 1) && (chords[i] == 'C' || chords[i] == 'D' ||
				chords[i] == 'F' || chords[i] == 'G' || chords[i] == 'A')
				&& chords[i + 1] == '#') {
				cutMelody += chords[i];
				cutMelody += chords[i + 1];
				i = i + 1;
			}
			else {
				cutMelody += chords[i];
			}
			//C#BBC#
			//C#BBB
			//사이즈로 비교하면 #때문에 조건문을 지나쳐버림
			//잘라낸 코드의 개수가 기억한 멜로디 코드개수와 같다면 비교한다.
			if (++chordsCnt == melodyCnt) {
				if (cutMelody == m) {
					answer = infoMap[2];
					return answer;
				}
				else {
					//같지 않다면 앞에서 코드하나를 잘라냄
					if ((cutMelody[0] == 'C' || cutMelody[0] == 'D' || cutMelody[0] == 'F'
						|| cutMelody[0] == 'G' || cutMelody[0] == 'A')
						&& cutMelody[1] == '#') {
						cutMelody = cutMelody.substr(2);
					}
					else {
						cutMelody = cutMelody.substr(1);
					}
					chordsCnt--;
				}
			}
		}
	}
	return "(None)";
}

string solution(string m, vector<string> musicinfos) {
	string answer = "";
	int max = 0;

	//m은 네오가 기억한 멜로디
	//음은 1분에 1개씩 재생된다
	for (auto musicInfo : musicinfos) {
		//infoMap에 정보담기
		processInfo(musicInfo);

		//악보처리
		string chords = processChords();

		//멜로디와 악보비교
		string result = compareChords(m, chords);

		if (result != "(None)") {
			int res_time = processTime();
			if (max < res_time) {
				//큰 것만 넣으므로 재생된 시간이 같을 경우 먼저 체크된 음악이 반환
				max = res_time;
				answer = result;
			}
		}
	}
	if (answer == "") {
		return "(None)";
	}
	return answer;
}
