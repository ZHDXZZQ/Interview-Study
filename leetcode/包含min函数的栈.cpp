/*
    思路： 辅助栈，时间On，空间On
    1. 利用一个辅助栈，栈顶存当前栈中的最小值
*/

class Solution {
public:
    void push(int value) {
        data.push(value);
        if (min_sta.empty() || min_sta.top() >= value) {    // 如果最小栈为空，或者新来的值更小，则插入value
            min_sta.push(value);
        } else {    // 如果最小栈不空且新插入的值不是最小值，则插入栈顶（最小值）
            min_sta.push(min_sta.top());
        }
    }
    void pop() {
        data.pop();
        min_sta.pop();  // 同步
    }
    int top() {
        return data.top();
    }
    int min() { // 最小栈栈顶一定是当前data中的最小值
        return min_sta.top();
    }
private:
    stack<int> min_sta;
    stack<int> data;    // 正常的栈
};