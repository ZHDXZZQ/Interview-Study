/*
    思路： 位运算，判断最低位是否相同，时间Ologn，空间O1
*/

class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = 0;
        while (x || y) {    // 当两个都不为0时，才判断
            if ((x & 1) != (y & 1)) {       // 必须加括号，因为!=运算符优先级高，这里也可以利用异或^来判断
                ++ res; // 如果当前两个数字的最低位不同，则记一次
            }
            x >>= 1;    // 各右移一位
            y >>= 1;
        }
        return res;
    }
};