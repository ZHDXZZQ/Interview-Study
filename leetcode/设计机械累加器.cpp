/*
    思路： 脑筋急转弯，不利用if语句实现递归。时间Otarget，空间Otarget
    1. 利用且语句左边为false则不执行右边的特性
    2. 也可以利用三目运算符
*/

class Solution {
public:
    int mechanicalAccumulator(int target) {
        target > 1 && (target += mechanicalAccumulator(target - 1));
        return target;
    }
};