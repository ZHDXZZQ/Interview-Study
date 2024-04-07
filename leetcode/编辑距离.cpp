// 思路： 动态规划， 时间Omn，空间Omn
// dp[i][j]表示word1的前i个字符构成的子串变化成word2的前j个字符构成的子串所需要的步数
// 1. 变化的方法就三种，可以大致划分为两种
// 2. 第一种为增减行为，即通过加一个字符或者减一个字符可以得到
// 3. 第二种为替换行为，即替换一个字符即可得到
// 4. 直接对三种的结果取min即可

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        word1 = " " + word1;        //前面加一个空格，字符串从1开始，方便后面计算
        word2 = " " + word2;
        for (int i = 0; i <= m; ++ i) { //初始化dp数组，从i个字符变为0个字符肯定是需要删减i步
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++ j) { //从0个字符变成j个字符需要增加j步
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++ i) { //从字符串的开头开始判断
            for (int j = 1; j <= n; ++ j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1; //判断是删一个和增一个那个更快
                int tail = word1[i] != word2[j];                //判断当前对应的字符是否一致，如果一致则tail=0，不一致为1
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + tail);  //判断两个word1的前i-1个字符和word2的前j-1个字符变化到当前是否需要改变，如果tail=0表示不需要改变，tail为1则表示该位需要替换一次
                // 这样就实现了三种方案取最小值
            }
        }
        return dp[m][n];
    }
};