/*
    思路： 模拟，时间On，空间On
    1. 模拟栈的计算，数字和符号各开一个栈
    2. 计算规则为，如果将要放入的符号优先级不比上一个高，则要计算完优先级不低于当前符号的计算
    3. 对于括号的优先级是最高，右括号仅仅是一个触发计算的作用
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

stack<char> ops;
stack<int> nums;

void calc() {   // 拿出两个栈的栈顶进行计算
    auto b = nums.top(); nums.pop();
    auto a = nums.top(); nums.pop();
    auto c = ops.top(); ops.pop();
    int x;
    if (c == '+') x = a + b;
    else if (c == '-') x = a - b;
    else if (c == '*') x = a * b;
    else x = a / b;
    nums.push(x);   // 计算结果插回
}

bool is_op(char& c) {   // 判断是否是符号
    if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    return false;
}

unordered_map<char, int> op_priority = {{'*', 2}, {'/', 2}, {'+', 1}, {'-', 1}};    // 记录符号优先级

int main() {
    string str;
    cin >> str;
    int pos = 0;
    int n = str.size();
    while (pos < n) {
        if (is_op(str[pos])) {  // 判断当前是否是符号
            char op = str[pos];
            ++ pos;
            if (op == ')') {    // 如果是右括号
                while (ops.top() != '(') {  // 要计算到左括号，把括号内的都算完
                    calc();
                }
                ops.pop();  // 左括号出栈
            } else if (op == '(') { // 左括号的时候直接入栈
                ops.push(op);
            } else {
                while (ops.size() && ops.top() != '(' && op_priority[ops.top()] >= op_priority[op]) {   // 如果当前运算符优先级不高于前面的，则要计算
                    calc();
                }
                ops.push(op);   // 插入当前运算符，比如+要把前面的/*-都算完，再放进来
            }
        } else {    // 如果是数字
            int end = pos;
            while (end < n && !is_op(str[end])) {
                ++ end;
            }
            int num = stoi(str.substr(pos, end - pos)); // 找到数字并插入
            pos = end;
            nums.push(num);
        }
    }
    while (ops.size()) {    // 如果都完成之后栈中还有未计算的符号，则要计算完，一般就是按优先级排序剩余的符号了
        calc();
    }
    cout << nums.top();
    return 0;
}