#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string new_id) {
    string answer = "";
    int str_len = new_id.size();

    //�� FOR������ 1,2,3�ܰ� ����
    for (int i = 0; i < str_len; i++) {
        if (str_len <= 0) {
            break;
        }
        if (new_id[i] >= 'A' && new_id[i] <= 'Z') {
            //�빮�ڸ� �ҹ��ڷ� ġȯ
            new_id[i] = tolower(new_id[i]);
            continue;
        }
        else if (!((new_id[i] >= '0' && new_id[i] <= '9') || (new_id[i] >= 'a' && new_id[i] <= 'z') ||
            new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')) {
            //���ĺ� �ҹ���, ����, ����, ����, ��ħǥ�� �ƴ϶��
            if (i == 0) {
                new_id = new_id.substr(1);
            }
            else if (i == str_len - 1) {
                new_id.resize(str_len - 1);
            }
            else {
                new_id = new_id.substr(0, i) + new_id.substr(i + 1);
            }
            //�ش� ���ڸ� �����Ѵ�.
            str_len--;
            i--;
            continue;
        }
        else if (new_id[i] == '.') {
            //��ħǥ�� 2�� �̻� ���ӵȴٸ� �ϳ��� ġȯ(�ϳ��� ����)
            if (i > 0 && new_id[i - 1] == '.') {
                new_id = new_id.substr(0, i) + new_id.substr(i + 1);
                i--;
                str_len--;
                continue;
            }
        }
    }

    //4�ܰ� ���̳� ���� ��ħǥ�� ����
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

    //5�ܰ� �� ���ڿ��� �Ǹ� "a"�� ����
    if (str_len <= 0) {
        new_id = "a";
        str_len = 1;
    }

    //6�ܰ�
    if (str_len >= 16) {
        //16�� �̻��̶�� ù 15�� ���ڱ��� ���ڿ��� �ڸ���
        new_id.resize(15);
        if (new_id[new_id.size() - 1] == '.') {
            //���� �ڸ� �� �ǵ� ���ڰ� ��ħǥ�̸� ���ڿ� ����� 14�� ����
            new_id.resize(14);
            str_len = 14;
        }
        else {
            str_len = 15;
        }
    }

    //7�ܰ�
    if (str_len <= 2) {
        //���ڿ��� ���̰� 2 ���϶�� ���̰� 3�� �ɶ����� ������ ���ڸ� ���Ѵ�.
        char lastWord = new_id.back();
        for (int i = str_len; i < 3; i++) {
            new_id += lastWord;
        }
    }

    answer = new_id;
    return answer;
}