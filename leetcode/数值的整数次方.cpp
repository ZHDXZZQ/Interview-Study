/*
    思路： 模拟，时间On，空间O1
*/

class Solution {
public:
    double Power(double base, int exponent) {
        if (exponent < 0) { // 负数的化，底数变成倒数，指数变成正数
            exponent = -exponent;
            base = 1 / base;
        }
        double res = 1.0;
        for (int i = 0; i < exponent; ++ i) {   // 计算目标次
            res *= base;
        }
        return res;
    }
};