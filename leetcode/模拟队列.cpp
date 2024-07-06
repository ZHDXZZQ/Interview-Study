#include <iostream>

using namespace std;

const int N = 1e6 + 10;

int nums[N];
int head = 0, tail = 0; // 用循环队列取模更好，这里直接开辟了足够大的空间满足M个操作

void push(int v) {
    nums[tail] = v;
    ++ tail;
}

void pop() {
    ++ head;
}

void query() {
    cout << nums[head] << endl;
}

void empty() {
    if (tail == head) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    int m;
    cin >> m;

    while (m--) {
        string cmd;
        cin >> cmd;
        if (cmd == "push") {
            string num_str;
            cin >> num_str;
            int num = stoi(num_str);
            push(num);
        } else if (cmd == "pop") {
            pop();
        } else if (cmd == "query") {
            query();
        } else if (cmd == "empty") {
            empty();
        }
    }
    return 0;
}