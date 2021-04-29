#include <string>
#include <unordered_set>
using namespace std;

int solution(string dirs) {
    unordered_set<string> mSet;
    pair<int, int> mPos = { 0,0 };
    for (int i = 0; i < dirs.size(); i++) {
        int nextRow, nextCol;
        if (dirs[i] == 'U') {
            nextRow = mPos.first - 1;
            nextCol = mPos.second;
        }
        else if (dirs[i] == 'D') {
            nextRow = mPos.first + 1;
            nextCol = mPos.second;
        }
        else if (dirs[i] == 'L') {
            nextRow = mPos.first;
            nextCol = mPos.second - 1;
        }
        else if (dirs[i] == 'R') {
            nextRow = mPos.first;
            nextCol = mPos.second + 1;
        }
        if (nextRow >= -5 && nextRow <= 5 && nextCol >= -5 && nextCol <= 5) {
            mSet.insert(to_string(mPos.first) + "," + to_string(mPos.second) + "-" +
                to_string(nextRow) + "," + to_string(nextCol));
            mSet.insert(to_string(nextRow) + "," + to_string(nextCol) + "-" +
                to_string(mPos.first) + "," + to_string(mPos.second));
            mPos = { nextRow,nextCol };
        }
    }
    return mSet.size() / 2;
}