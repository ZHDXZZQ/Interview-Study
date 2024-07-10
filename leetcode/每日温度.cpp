/*
    思路： 单调栈，时间On，空间On
    1. 栈中存储天数下标，按温度递减入栈
    2. 每次取出栈顶判断，如果栈顶温度低于今天，则出栈并记录
    3. 继续出栈，直到栈顶日温度不低于今天，后续的温度更高无需判断
    4. 栈中存储的都是待出现高温的日子
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        stack<int> dec_sta; //单调递减栈
        dec_sta.push(0);
        vector<int> res(n, 0);  // 其实可以在原数组上改造
        for (int i = 1; i < n; ++ i) {  // 从第二天开始遍历
            int last_day = dec_sta.top();   // 取出前一天
             while (dec_sta.size()) {   // 取出当前栈中的每一天，直到栈顶的温度不低于今天，则需继续等待
                last_day = dec_sta.top();   // 对于循环来说，再次取出栈顶
                if (temperatures[last_day] < temperatures[i]) { // 如果这一天温度低于今天，说明今天就是栈顶这一天后最近的温度高的一天
                    dec_sta.pop();  // 将栈顶这一天出栈，并记录在那一天的信息中
                    res[last_day] = i - last_day;
                } else {    // 因为是单调递减栈，因此如果栈顶日温度都高了，那么前面的更高，无需操作
                    break;
                }
            }
            dec_sta.push(i);    // 将今天入栈
        }
        return res;
    }
};