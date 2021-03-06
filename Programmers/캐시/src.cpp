#include <string>
#include <vector>
#include <locale>
#include <algorithm>
using namespace std;

vector<pair<string, int>> citiesCache;

bool compare(pair<string, int> p1, pair<string, int> p2) {
	return p1.second > p2.second;
}
//���̰� ū ������� ����

bool find_Cache(string key) {
	bool found_it = false;
	for (int i = 0; i < citiesCache.size(); i++) {
		if (citiesCache[i].first == key) {
			//ã������ ��ȸ������ ���̸� �ʱ�ȭ�ϰ� ã������ üũ
			citiesCache[i].second = 0;
			found_it = true;
			//�� �κп��� �ٷ� ������ �ع����� �ٸ� ĳ�ð����� ���̸� ���Ծ Ʋ����
		}
		else {
			//ã�°� �ƴҰ�� �Ⱦ����ٴ� �ǹ̷� ���̸� ������Ŵ
			citiesCache[i].second++;
		}
	}
	return found_it;
}

void replaceCache() {
	if (citiesCache.empty()) {
		return;
	}
	//���̰� ���ٸ� ���� ������� ������ �ȴ�(�������� ���� �Ǿ�)
	stable_sort(citiesCache.begin(), citiesCache.end(), compare);
	citiesCache.erase(citiesCache.begin());
}

int solution(int cacheSize, vector<string> cities) {
	int answer = 0;
	int is_Full = 0;
	if (cacheSize == 0) {
		//ĳ�û���� 0�̸� ���� ĳ�ù̽���
		return cities.size() * 5;
	}
	for (auto it : cities) {
		//��ҹ��� ������ ���Ѵ�
		transform(it.begin(), it.end(), it.begin(), ::toupper);
		if (citiesCache.empty()) {
			//����ִٸ� ���� ���ø� ĳ�ÿ� �ְ� ĳ�ù̽��̹Ƿ� 5����
			answer += 5;
			citiesCache.push_back({ it,0 });
			is_Full += 1;
		}
		else {
			if (!find_Cache(it)) {
				if (is_Full == cacheSize) {
					//��ã�Ҵµ� ĳ�û���� ��á���� LRU�� ĳ�ÿ��� �ϳ��� ���i�Ƴ�
					replaceCache();
					citiesCache.push_back({ it,0 });
				}
				else {
					//ĳ�� ����� ������ ������ �ְ� ������ 1����
					is_Full += 1;
					citiesCache.push_back({ it,0 });
				}
				//ĳ�ù̽��̹Ƿ� 5 ����
				answer += 5;
			}
			else {
				//ĳ����Ʈ �����Ƿ� 1����
				answer += 1;
			}
		}
	}
	return answer;
}