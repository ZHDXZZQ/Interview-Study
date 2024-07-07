/*
    思路： 可以用固定大小的数组实现，我们这里利用弹性大小的链表实现
*/

#include <iostream>

using namespace std;

struct node {   // 链表类型作为每个栈的节点，可以动态扩充
    node* next;
    int value;
    node(int v) : next(nullptr), value(v) {}
    node(node* ptr, int v) : next(ptr), value(v) {}
} *top; // top为栈顶指针，指向栈顶节点，初始化为nullptr

void push(int val) {    // 建立一个新结点指向当前栈顶节点，并成为新的栈顶结点
    node* cur_node = new node(top, val);    
    top = cur_node;
}

void query() {  // 输出栈顶节点的值
    if (top == nullptr) {
        return;
    }
    cout << top->value << endl;
}

void pop() {    // 将栈顶结点销毁，栈顶结点更新为下一个节点
    if (top == nullptr) {
        return ;
    }
    auto tmp = top;
    top = top->next;
    delete tmp;
}

void empty() {  // 判断栈顶结点是否为空即可
    if (top == nullptr) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    top = nullptr;
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