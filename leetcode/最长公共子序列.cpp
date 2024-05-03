// 思路： 动态规划，时间Omn，空间Omn
// dp[i][j]表示text1从第1个字符到第i个字符，text2从第1个字符到第j个字符，二者的最长公共子序列
// 1. 第一种情况，i和j对应的字符相等，此时这两个字符作为公共子序列的一员加入。即dp[i-1][j-1]+1
// 2. 否则的话，i或j假设有一个不是公共子序列的一员或者都不是公共子序列的一员，则取其少一个的最大值
// 3. 即dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]的最大值，但是前两者包含了第三者，所以只需要计算前两者的最大值即可
// 4. 如果此题是计算有公共子序列的数量，则需要将前三个相加，减去两次的最后一个

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // 先判断不包含任一个的最大值
                if (text1[i - 1] == text2[j - 1]) { // 如果当前所指字符相等
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1); // 把这个字符加入
                }
            }
        }
        return dp[m][n];
    }
};