#include <iostream>
#include <vector>
using namespace std;

int n, l;
int graph[101][101]{ 0 };

bool checkColumn(int col) {
    int start = graph[0][col];
    vector<bool> check(n);

    for (int i = 1; i < n;) {
        if (i == n - 1) {
            if (abs(graph[i][col] - start) == 1) {
                if (graph[i][col] > start) {
                    for (int j = i - 1; j >= i - l; j--) {
                        if (j < 0) return false;
                        if (check[j]) return false;
                        if (graph[j][col] != start) return false;
                        check[j] = true;
                    }
                    return true;
                }
                else if (l == 1) {
                    return true;
                }
                return false;
            }
            else if (graph[i][col] == start) {
                return true;
            }
            else {
                return false;
            }
        }
        if (abs(graph[i][col] - start) > 1) {
            return false;
        }
        if (graph[i][col] == start) {
            i++;
            continue;
        }
        else {
            int cur = graph[i][col];
            //���̰� cur�� �� ũ�ٸ� cur �޺κ��� üũ�ؾߵ�
            if (cur > start) {
                for (int j = i - 1; j >= i - l; j--) {
                    if (j < 0) return false;
                    if (check[j]) return false;
                    if (graph[j][col] != start) return false;
                    check[j] = true;
                }
                i++;
                start = cur;
            }
            else {
                for (int j = i + 1; j < i + l; j++) {
                    //���� ���������� üũ
                    if (j >= n) return false;
                    if (check[j]) return false;
                    if (graph[j][col] != cur) return false;
                    check[j] = true;
                }
                check[i] = true;
                //���⼭ i�� n-1�� �������� ����
                i += l;
                start = cur;
            }
        }
    }
    return true;
}

bool checkRow(int row) {
    int start = graph[row][0];
    vector<bool> check(n);

    for (int i = 1; i < n;) {
        if (i == n - 1) {
            if (abs(graph[row][i] - start) == 1) {
                if (graph[row][i] > start) {
                    for (int j = i - 1; j >= i - l; j--) {
                        if (j < 0) return false;
                        if (check[j]) return false;
                        if (graph[row][j] != start) return false;
                        check[j] = true;
                    }
                    return true;
                }
                else if (l == 1) {
                    return true;
                }
                return false;
            }
            else if(graph[row][i] == start){
                return true;
            }
            else {
                return false;
            }
        }
        if (abs(graph[row][i] - start) > 1) {
            return false;
        }
        if (graph[row][i] == start) {
            i++;
            continue;
        }
        else {
            int cur = graph[row][i];
            //���̰� cur�� �� �۴ٸ� cur �޺κ��� üũ�ؾߵ�
            if (cur > start) {
                for (int j = i - 1; j >= i - l; j--) {
                    if (j < 0) return false;
                    if (check[j]) return false;
                    if (graph[row][j] != start) return false;
                    check[j] = true;
                }
                i++;
                start = cur;
            }
            else {
                for (int j = i + 1; j < i + l; j++) {
                    //���� ���������� üũ
                    if (j >= n) return false;
                    if (check[j]) return false;
                    if (graph[row][j] != cur) return false;
                    check[j] = true;
                }
                check[i] = true;
                i += l;
                start = cur;
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    int answer = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        //���� üũ
        if (checkColumn(i)) cnt++;
        //���� üũ
        if (checkRow(i)) cnt++;
        answer += cnt;
    }
    cout << answer;
    return 0;
}