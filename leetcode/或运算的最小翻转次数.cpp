/*
    思路： 位运算，时间Ologn，空间O1
*/

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int res = 0;
        for (int i = 0; i < 31; ++ i) { // 遍历每一位
            int a_1 = a >> i & 1;
            int b_1 = b >> i & 1;
            int c_1 = c >> i & 1;
            if (c_1 == 0) { // 如果c的该位为0
                res += a_1 + b_1;   // 则a和b的该位是1的都要变成0
            } else {    // 如果c的该位是1
                if (a_1 == 0 && b_1 == 0) { // 如果a和b的该位都是0，则需要变一个，其余情况不需要变
                    ++ res;
                }
            }
        }
        return res;
    }
};