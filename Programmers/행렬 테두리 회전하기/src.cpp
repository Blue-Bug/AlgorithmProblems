#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    int mat[100][100]{ 0 };
    int val = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            mat[i][j] = val++;
        }
    }
    for (auto q : queries) {
        int row1 = q[0] - 1;
        int col1 = q[1] - 1;
        int row2 = q[2] - 1;
        int col2 = q[3] - 1;
        vector<int> change;
        change.push_back(mat[row1 + 1][col1]);
        //복사
        for (int j = col1; j < col2; j++) {
            change.push_back(mat[row1][j]);
        }
        for (int i = row1; i <= row2; i++) {
            change.push_back(mat[i][col2]);
        }
        for (int j = col2 - 1; j > col1; j--) {
            change.push_back(mat[row2][j]);
        }
        for (int i = row2; i > row1 + 1; i--) {
            change.push_back(mat[i][col1]);
        }
        //붙여넣기
        int idx = 0;
        for (int j = col1; j < col2; j++) {
            mat[row1][j] = change[idx++];
        }
        for (int i = row1; i <= row2; i++) {
            mat[i][col2] = change[idx++];
        }
        for (int j = col2 - 1; j > col1; j--) {
            mat[row2][j] = change[idx++];
        }
        for (int i = row2; i > row1; i--) {
            mat[i][col1] = change[idx++];
        }
        sort(change.begin(), change.end());
        answer.push_back(change[0]);
    }
    return answer;
}
