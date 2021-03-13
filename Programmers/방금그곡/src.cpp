#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<int, string> infoMap;

void processInfo(string musicInfo) {
	//',' ���ڸ� �������� �Ľ��ϸ� map�� ������ ��´�.
	//�ε��� 0�� ���۽ð�, 1�� ����ð�, 2�� ����, 3�� �Ǻ�
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
	//�ð� ó�� �Լ�
	//���� �ð� ó��
	int start_hour = ((infoMap[0].substr(0, 1)[0] - 48) * 10)
		+ ((infoMap[0].substr(1, 1).c_str()[0] - 48) * 1);
	int start_minute = ((infoMap[0].substr(3, 1)[0] - 48) * 10)
		+ ((infoMap[0].substr(4, 1)[0] - 48) * 1);
	//���� �ð� ó��
	int end_hour = ((infoMap[1].substr(0, 1)[0] - 48) * 10)
		+ ((infoMap[1].substr(1, 1)[0] - 48) * 1);
	int end_minute = ((infoMap[1].substr(3, 1)[0] - 48) * 10)
		+ ((infoMap[1].substr(4, 1)[0] - 48) * 1);

	//��� �ð� ó��
	//10:14 12:02 -> 2 :-12 ->  1 : 48 
	//13:50 14:00 -> 1 :-50 -> 0 : 10
	int play_hour = end_hour - start_hour;
	int play_minute = end_minute - start_minute;
	if (play_minute < 0) {
		play_minute = 60 + play_minute;
		play_hour -= 1;
	}

	//�� ����ð��� ������ ��ȯ�ؼ� ��ȯ
	return play_minute + (play_hour * 60);
}

string processChords() {
	//����ð��� ���� �Ǻ��� �ϼ�
	string chords = "";

	//��� �ð��� �޾ƿ�
	int countTime = processTime();
	int idx = 0;
	//C, C#, D, D#, E, F, F#, G, G#, A, A#, B 
	//#������ ������ ���� ���ߵ�
	while (countTime-- > 0) {
		//idx�� ������ ��ġ�� �Ѿ�� �� ������ �ʱ�ȭ
		if (idx >= infoMap[3].size()) {
			idx = 0;
		}
		//�ڵ� �ڿ� #�� ������ �߰��ϰ� idx ����
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

	//�ϼ��� �Ǻ��� ��ȯ
	return chords;
}

string compareChords(string m, string chords) {
	string cutMelody = "";
	string answer = "";
	int melodyCnt = 0;
	int chordsCnt = 0;
	//����� ��ε��� �ڵ尳���� ��� ����
	for (int i = 0; i < m.size(); i++) {
		if (i != (m.size() - 1) && (m[i] == 'C' || m[i] == 'D'
			|| m[i] == 'F' || m[i] == 'G' || m[i] == 'A')
			&& m[i + 1] == '#') {
			i = i + 1;
		}
		melodyCnt++;
	}
	//����� ��ε�� ����� �뷡�� �ڵ���̰� ���ٸ� �ٷ� ��
	if (m.size() == chords.size() && m == chords) {
		answer = infoMap[2];
		return answer;
	}
	else if (m.size() < chords.size()) {
		for (int i = 0; i < chords.size(); i++) {
			//����� �뷡�� �ڵ带 ����� ��ε� �ڵ尳���� ���������� �߶�
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
			//������� ���ϸ� #������ ���ǹ��� �����Ĺ���
			//�߶� �ڵ��� ������ ����� ��ε� �ڵ尳���� ���ٸ� ���Ѵ�.
			if (++chordsCnt == melodyCnt) {
				if (cutMelody == m) {
					answer = infoMap[2];
					return answer;
				}
				else {
					//���� �ʴٸ� �տ��� �ڵ��ϳ��� �߶�
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

	//m�� �׿��� ����� ��ε�
	//���� 1�п� 1���� ����ȴ�
	for (auto musicInfo : musicinfos) {
		//infoMap�� �������
		processInfo(musicInfo);

		//�Ǻ�ó��
		string chords = processChords();

		//��ε�� �Ǻ���
		string result = compareChords(m, chords);

		if (result != "(None)") {
			int res_time = processTime();
			if (max < res_time) {
				//ū �͸� �����Ƿ� ����� �ð��� ���� ��� ���� üũ�� ������ ��ȯ
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
