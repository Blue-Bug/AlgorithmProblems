#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
int answer = 0;
vector<vector<int>> papers;
int bitCheck[4]{ 0 };

void countPaper(int row) {
	if (row >= n) {
		vector<vector<bool>>check(n, vector<bool>(m, false));
		int result = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (check[i][j]) continue;
				int tmp = 1 << j;
				if ((bitCheck[i] & tmp) == tmp) {
					//1이면 오른쪽을 체크
					check[i][j] = true;
					int paperVal = papers[i][j];					
					for (int k = j + 1; k < m; k++) {
						tmp = 1 << k;
						if ((bitCheck[i] & tmp) == tmp) {
							check[i][k] = true;
							paperVal *= 10;
							paperVal += papers[i][k];
						}
						else {
							j = k;
							break;
						}
					}
					result += paperVal;
				}
				else if((bitCheck[i] & tmp) != tmp) {
					//0이면 아래를 체크
					check[i][j] = true;
					int paperVal = papers[i][j];
					for (int k = i + 1; k < n; k++) {
						if ((bitCheck[k] & tmp) != tmp) {
							check[k][j] = true;
							paperVal *= 10;
							paperVal += papers[k][j];							
						}
						else {
							break;
						}
					}
					result += paperVal;
				}
			}
			
		}
		answer = max(answer, result);
		return;
	}
	bitCheck[row] = 0;
	for (int i = 0; i < pow(2, m); i++) {
		//000 001 010 011 100 101 110 111
		countPaper(row + 1);
		bitCheck[row] += 1;
	}
}

int main() {	
	cin >> n >> m;
	papers = vector<vector<int>>(n,vector<int>(m));
	string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		for (int j = 0; j < str.size(); j++) {
			papers[i][j] = str[j] - 48;
		}
	}
	int row = 0;//레벨
	for (int i = 0; i < pow(2,m); i++) {
		//000 001 010 011 100 101 110 111
		countPaper(row + 1);
		bitCheck[row] += 1;
	}
	cout << answer;
}