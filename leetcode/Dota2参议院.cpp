/*
    思路： 贪心+队列，时间On，空间On
    1. 靠前的议员先执行权力，越靠前的议员权力越大
    2. 如果后面还有对方议员，则禁止其说话；否则宣布胜利
    3. 优先禁止靠前的对方议员说话，自己则等待下一轮，过程中可能被尾部的对方议员禁言
    4. 无限循环，直到有一方议员全部被禁言为止。
    注：同一阵营越靠后的议员越有可能先被对方议员干掉，且越靠前的议员能禁言的人越多，所以优先灭掉对方靠前的议员
*/

class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> r, d;    // 两个队列存储双方议员位置
        int n = senate.size();
        for (int i = 0; i < n; ++ i) {
            if (senate[i] == 'R') { // 记录初始状态
                r.push(i);
            } else {
                d.push(i);
            }
        }
        while (r.size() && d.size()) {  // 只要两边的议员还有存在的就继续
            if (r.front() < d.front()) {    // 靠前一方的议员先行使权力
                r.push(r.front() + n);  // 行使权力后重新入队继续参加后续评议
            } else {
                d.push(d.front() + n);  // +n是因为避免序号错乱，算是下一轮比拼，位次靠后
            }
            r.pop();    // 没回都会让双方队头离开，离开更小的一方刚才已经重新入队
            d.pop();
        }
        if (r.empty()) {    // 先没的那家就输了
            return "Dire";
        }
        return "Radiant";
    }
};