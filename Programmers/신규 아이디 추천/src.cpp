#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string new_id) {
    string answer = "";
    int str_len = new_id.size();

    //이 FOR문에서 1,2,3단계 수행
    for (int i = 0; i < str_len; i++) {
        if (str_len <= 0) {
            break;
        }
        if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
            //대문자를 소문자로 치환
            new_id[i] = tolower(new_id[i]);
            continue;
        }
        else if (!((new_id[i] >= '0' && new_id[i] <= '9') || (new_id[i] >= 'a' && new_id[i] <= 'z') ||
            new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')) {
            //알파벳 소문자, 숫자, 빼기, 밑줄, 마침표가 아니라면
            if (i == 0) {
                new_id = new_id.substr(1);
            }
            else if (i == str_len - 1) {
                new_id.resize(str_len - 1);
            }
            else {
                new_id = new_id.substr(0, i) + new_id.substr(i + 1);
            }
            //해당 문자를 제외한다.
            str_len--;
            i--;
            continue;
        }
        else if (new_id[i] == '.') {
            //마침표가 2번 이상 연속된다면 하나로 치환(하나를 제거)
            if (i > 0 && new_id[i - 1] == '.') {
                new_id = new_id.substr(0, i) + new_id.substr(i + 1);
                i--;
                str_len--;
                continue;
            }
        }
    }

    //4단계 앞이나 뒤의 마침표를 제거
    if (new_id[0] == '.') {
        new_id = new_id.substr(1);
        str_len = new_id.size();
    }

    if (str_len) {
        if (new_id.back() == '.') {
            new_id.resize(new_id.size() - 1);
            str_len = new_id.size();
        }
    }

    //5단계 빈 문자열이 되면 "a"를 대입
    if (str_len <= 0) {
        new_id = "a";
        str_len = 1;
    }

    //6단계
    if (str_len >= 16) {
        //16자 이상이라면 첫 15개 문자까지 문자열을 자른다
        new_id.resize(15);
        if (new_id[new_id.size() - 1] == '.') {
            //만약 자른 후 맨뒤 문자가 마침표이면 문자열 사이즈를 14로 변경
            new_id.resize(14);
            str_len = 14;
        }
        else {
            str_len = 15;
        }
    }

    //7단계
    if (str_len <= 2) {
        //문자열이 길이가 2 이하라면 길이가 3이 될때까지 마지막 문자를 더한다.
        char lastWord = new_id.back();
        for (int i = str_len; i < 3; i++) {
            new_id += lastWord;
        }
    }

    answer = new_id;
    return answer;
}