// 思路： 动态规划，时间On，空间On
// 1. 求2、3、5三个数各种组合相乘的结果，每次取最小。可以用堆实现
// 2. 动态规划的方法，利用三个遍历记录三个值乘到哪里了，每次令对应位置的值乘上对应的值

class Solution {
public:
    int nthUglyNumber(int n) {
        int p2 = 0, p3 = 0, p5 = 0; //记录对应的2、3、5各自乘了几次
        vector<int> dp(n);  //dp[i]表示位置i的丑数
        dp[0] = 1;      //初始化第一个丑数为1
        for (int i = 1; i < n; ++ i) {
            int num2 = dp[p2] * 2;  //每次将3个位置对应的数乘上这三个数
            int num3 = dp[p3] * 3;
            int num5 = dp[p5] * 5;
            dp[i] = min(min(num2, num3), num5); //选出最小的数作为当前的丑数
            if (dp[i] == num2) {    //选择是哪个数对应的值成为了当前的丑数最小值
                ++ p2;              //就对这个值+1，后续就不会重复计算
            }
            if (dp[i] == num3) {    //不能用else，因为可能同时match，比如6
                ++ p3;
            }
            if (dp[i] == num5) {
                ++ p5;
            }
        }
        return dp[n - 1];   //返回n位的丑数
    }
};