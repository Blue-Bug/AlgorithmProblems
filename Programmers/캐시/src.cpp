#include <string>
#include <vector>
#include <locale>
#include <algorithm>
using namespace std;

vector<pair<string, int>> citiesCache;

bool compare(pair<string, int> p1, pair<string, int> p2) {
	return p1.second > p2.second;
}
//나이가 큰 순서대로 정렬

bool find_Cache(string key) {
	bool found_it = false;
	for (int i = 0; i < citiesCache.size(); i++) {
		if (citiesCache[i].first == key) {
			//찾았으면 조회했으니 나이를 초기화하고 찾았음을 체크
			citiesCache[i].second = 0;
			found_it = true;
			//이 부분에서 바로 리턴을 해버려서 다른 캐시값들이 나이를 못먹어서 틀렸음
		}
		else {
			//찾는게 아닐경우 안쓰였다는 의미로 나이를 증가시킴
			citiesCache[i].second++;
		}
	}
	return found_it;
}

void replaceCache() {
	if (citiesCache.empty()) {
		return;
	}
	//나이가 같다면 들어온 순서대로 정렬이 된다(먼저들어온 놈이 맨앞)
	stable_sort(citiesCache.begin(), citiesCache.end(), compare);
	citiesCache.erase(citiesCache.begin());
}

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
	int is_Full = 0;
	if (cacheSize == 0) {
		//캐시사이즈가 0이면 전부 캐시미스임
		return cities.size() * 5;
	}
	for (auto it : cities) {
		//대소문자 구분을 안한다
		transform(it.begin(), it.end(), it.begin(), ::toupper);
		if (citiesCache.empty()) {
			//비어있다면 현재 도시를 캐시에 넣고 캐시미스이므로 5증가
			answer += 5;
			citiesCache.push_back({ it,0 });
			is_Full += 1;
		}
		else {
			if (!find_Cache(it)) {
				if (is_Full == cacheSize) {
					//못찾았는데 캐시사이즈도 꽉찼으면 LRU로 캐시에서 하나를 내쫒아냄
					replaceCache();
					citiesCache.push_back({ it,0 });
				}
				else {
					//캐시 사이즈가 여유가 있으면 넣고 사이즈 1증가
					is_Full += 1;
					citiesCache.push_back({ it,0 });
				}
				//캐시미스이므로 5 증가
				answer += 5;
			}
			else {
				//캐시히트 했으므로 1증가
				answer += 1;
			}
		}
	}
	return answer;
}