#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

vector<string> wordcopy;

int bfs(string str,string tar) {
	unordered_map<string,bool>visited;
	queue<pair<string, int>>q;
	q.push({ str, 0 });
	while (!q.empty()) {
		string cur = q.front().first;
		int cnt = q.front().second;
		q.pop();
		if (cur == tar) {
			return cnt;
		}
		if (visited.find(cur) != visited.end()) {
			continue;
		}
		visited[cur] = true;
		int comp = 0;
		for (int i = 0; i < wordcopy.size(); i++) {
			for (int j = 0; j < cur.size(); j++) {
				if (cur[j] != wordcopy[i][j]) {
					comp++;
				}
			}
			if (comp <= 1 && visited.find(wordcopy[i]) == visited.end()) {
				q.push({ wordcopy[i], cnt+1 });
			}
			comp = 0;
		}
	}
	return 0;
}
int solution(string begin, string target, vector<string> words) {
	wordcopy = words;
	int answer = bfs(begin, target);
	return answer;
}