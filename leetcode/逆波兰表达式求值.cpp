// 思路： 栈，时间On，空间On
// 1. 模拟求值即可

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> sta;
        for (auto& str : tokens) {
            if (str == "+") {               //如果当前是加号，将两个值取出相加再放回即可
                int num1 = stoi(sta.top()); //stoi，即string to int，会自动识别正负，这里就不重写函数了
                sta.pop();
                int num2 = stoi(sta.top());
                sta.pop();
                num1 += num2;
                sta.push(to_string(num1));  //将任意内容转化成string，这里不重写
            } else if (str == "-") {        //如果是减号，则取出相减再存回
                int num1 = stoi(sta.top());
                sta.pop();
                int num2 = stoi(sta.top());
                sta.pop();
                num2 -= num1;
                sta.push(to_string(num2));
            } else if (str == "*") {        //乘号
                int num1 = stoi(sta.top());
                sta.pop();
                int num2 = stoi(sta.top());
                sta.pop();
                num1 *= num2;
                sta.push(to_string(num1));
            } else if (str == "/") {        //除号
                int num1 = stoi(sta.top());
                cout << num1 << endl;
                sta.pop();
                int num2 = stoi(sta.top());
                sta.pop();
                num2 /= num1;
                sta.push(to_string(num2));
            } else {
                sta.push(str);              //如果不是运算符，则数字直接存入
            }
        }
        return stoi(sta.top());             //最后栈顶只有一个数，就是结果，因为题目不会给出计算不了的情况
    }
};