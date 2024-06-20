/*
    思路： 模拟栈，时间On，空间O1
    1. 队尾存放当前的最后一颗行星
    2. 每次来到新行星，先判断是否栈顶的向右，新来的向左
    3. 只有这种情况下，需要判断谁存活，以及是否有后续碰撞
*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> res;
        for (auto& num : asteroids) {
            bool is_inserted = false;   // 用于记录这个行星是否存活
            while (res.size() && num < 0 && res.back() > 0) {   // 如果当前还有行星且原来的为右，新来的为左，则判断存活
                is_inserted = true; // 默认爆炸
                int cur = -num;     // 取负数的相反数，方便判断大小
                if (cur == res.back()) {    // 如果当前大小相同，则都爆炸，栈顶弹出，无需插入
                    res.pop_back();
                    break;
                } else {    // 否则的话判断谁大
                    if (cur > res.back()) { // 新来的大，则栈顶弹出，继续判断
                        res.pop_back();
                        is_inserted = false;    // 如果没有下次判断了，则说明当前栈空，把该行星插入
                    } else {
                        break;  // 如果原来的大，新来的直接爆炸
                    }
                }
            }
            if (!is_inserted) { // 判断是否需要把新来的行星插入，其实就两种情况插入
                res.push_back(num); // 一是原来的也向左，而是原来的都向右且都更小
            }
        }
        return res;
    }
};