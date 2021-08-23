class Stack {
    constructor() {
        this._arr = [];
    }
    push(item) {
        this._arr.push(item);
    }
    pop() {
        return this._arr.pop();
    }
    top() {
        return this._arr[this._arr.length - 1];
    }
    empty() {
        return this._arr.length == 0;
    }
}

function step2(w) {
    if (w == '') return '';
    let st = new Stack();
    let u = w[0], v = '';
    st.push(w[0]);
    for (let i = 1; i < w.length; i++) {
        if (w[i] == st.top()) {
            st.push(w[i]);
            u += w[i];
        }
        else {
            if (st.empty()) {
                for (let j = i; j < w.length; j++) {
                    v += w[j];
                }
                break;
            }
            else {
                st.pop();
                u += w[i];
            }
        }
    }

    if (u[0] == ')') {
        //올바른 괄호 문자열 아님 step 4
        let tmp = '(' + step2(v) + ')';

        for (let i = 1; i < u.length - 1; i++) {
            if (u[i] == '(') {
                tmp += ')';
            }
            else {
                tmp += '(';
            }
        }
        return tmp;
    }
    else {
        //올바른 괄호 문자열임 step 3
        return u + step2(v);
    }
}

function solution(p) {
    if (p.length == 0) {
        return '';
    }
    return step2(p);
}