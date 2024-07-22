/*
    思路： 动态规划，时间On，空间On
    1. 对于每个数字，只需要考虑本位最低为是否是1
    2. 然后求除以2的情况，即右移一位，得到的就是前n-1位的1的个数
    3. 相加即是这个数的1的个数
*/

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1, 0);
        for(int i = 0; i <= n; i ++) {
            dp[i] = dp[i >> 1] + (i & 1);
        }
        return dp;
    }
};