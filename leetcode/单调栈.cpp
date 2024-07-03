/*
    思路： 单调栈，时间On，空间On
    1. 单调递增栈，因为碰到一个更小的，我们就把大于它的全部出栈，因为后续的数字如果大于这个小数，
    那么它不一定比前面的大数大，但由于是找最近的小数，那后面的数字一定不会用到前面的数字
    2. 而且这样做也有利于这个小数每次找到自己前面比自己小的数，符合题目要求
*/

#include <iostream>
#include <stack>

using namespace std;

int main() {
    int n;
    cin >> n;
    stack<int> sta;
    while (n--) {
        int num;
        cin >> num;
        if (sta.empty()) {  // 如果当前栈空，直接返回-1
            cout << -1 << " ";
            sta.push(num);
            continue;
        }
        if (sta.top() < num) {  // 如果当前栈顶数字小于新数字
            cout << sta.top() << " ";   // 那么栈顶数字就是离这个数字最近的比它小的数，输出栈顶
            sta.push(num);  // 将这个数字入栈
        } else {    // 如果栈顶数字大
            while (sta.size() && sta.top() >= num) {    // 那么要一直出栈栈顶，直到找到第一个比现在数字小的数
                sta.pop(); 
            } 
            if (sta.empty()) {  // 如果出栈完之后栈空了，那说明前面都是大数
                cout << -1 << " ";  // 返回-1，并把这个数字插入
                sta.push(num);
                continue;
            } else {    // 否则的话找到了最近的小于当前数的数
                cout << sta.top() << " ";   // 输出这个数
                sta.push(num);  // 将这个小一些的数字插入
            }
        }
    }
    return 0;
}