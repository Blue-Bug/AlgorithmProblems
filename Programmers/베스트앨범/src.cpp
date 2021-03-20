#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	return a.second > b.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
	vector<int> answer;
	unordered_map<string, vector<int>> genres_num;
	unordered_map<int, int> num_plays;
	map<int, string,greater<int>> playCount;
	for (int i = 0; i < genres.size(); i++) {
		genres_num[genres[i]].push_back(i);
	}
	for (int i = 0; i < plays.size(); i++) {
		num_plays[i] = plays[i];
	}
	for (auto genre : genres_num) {
		int count = 0;
		for (auto music_num : genre.second) {
			count += plays[music_num];
		}
		playCount[count] = genre.first;
	}
	
	for (auto genre : playCount) {
		vector<pair<int, int>> tmp;
		for (auto extract : genres_num[genre.second]) {
			tmp.push_back({ extract,plays[extract] });
		}
		sort(tmp.begin(), tmp.end(), compare);
		for (int i = 0; i < 2; i++) {
			if (tmp.empty()) {
				break;
			}
			answer.push_back(tmp.front().first);
			tmp.erase(tmp.begin());
		}
	}
	return answer;
}