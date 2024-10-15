/*
    思路： 数论，时间On，空间O1
    直接从小的子问题，往上推，根据公式(m+x)%n，这里的代表每一级子问题的长度。
*/

class Solution {
public:
    int LastRemaining_Solution(int n, int m) {
        //没有小朋友的情况
        if (n == 0 || m == 0) {
            return -1;
        }
        int x = 0;
        //从小到大，更新x
        for (int i = 2; i <= n; ++ i) {
            x = (m + x) % i;
        }
        return x;
    }
};
