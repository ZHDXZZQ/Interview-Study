/*
    思路： 模拟辅助栈，时间On，空间On，有空间O1的解法
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        // write code here
        int m = pushV.size();
        int l = 0, r = 0;
        stack<int> sta;
        while (l < m || r < m) {    // 有一边没走完就继续
            while (l < m && (sta.empty() || popV[r] != sta.top())) {    // 左边还可以放，并且栈为空或者右边和栈顶不同
                sta.push(pushV[l]); // 则插入左边的元素
                ++ l;
            }   // 如果右边的元素和栈顶相同，说明这个元素该出栈了，因为元素不重复
            if (popV[r] == sta.top()) {
                sta.pop();  // 出栈并继续比较下一个元素
                ++ r;
            } else {
                return false;   // 只要有一个不匹配，代表左边放满了，则输出false
            }
        }
        return true;    // 都能匹配输出true
    }
};