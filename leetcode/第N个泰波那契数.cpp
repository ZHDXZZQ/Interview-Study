/*
    思路： 优化动规，时间On，空间O1
    1. 每个数只需要前3个数的和，因此只需要滚动更新这三个数即可
*/

class Solution {
public:
    int tribonacci(int n) {
        int t0 = 0, t1 = 1, t2 = 1; // 初始化头3个数
        if (n == 0) { return 0; }   // 如果是0，直接返回0
        else if (n <= 2) { return 1; }  // 1和2返回1
        n -= 2; // 减去前3个数的计算，n表示需要计算几次
        while (n --) {
            int temp = t0 + t1 + t2;    // 计算新的数的和
            t0 = t1;    // 滚动更新
            t1 = t2;
            t2 = temp;
        }
        return t2;
    }
};