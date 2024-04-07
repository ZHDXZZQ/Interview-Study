// 思路： 动态规划，时间Omn，空间Omn
// dp[i][j]表示，对于第i，j这个格子，以该格子为右下角的格子的所能构成的最大的正方形的边长
// 1. 首先，对于第一行和第一列进行初始化，如果该格子为'1'，那么直接置对应格子在dp中的值为1
// 2. 然后开始遍历剩下的格子，每次取左、上、左上格子的最小值 + 1，就是以当前格子为右下角的构成的最大正方形的边长，具体的大家可以画图来看，文字不好描述

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int res = 0;
        for (int i = 0; i < m; ++ i) {  //初始化第一列
            if (matrix[i][0] == '1') {
                dp[i][0] = 1;
                res = 1;
            }
        }
        for (int j = 0; j < n; ++ j) {  //初始化第一行
            if (matrix[0][j] == '1') {
                dp[0][j] = 1;
                res = 1;
            }
        }
        for (int i = 1; i < m; ++ i) {  //遍历剩下的格子
            for (int j = 1; j < n; ++ j) {
                if (matrix[i][j] == '1') {  //如果该格子为1，则判断其是否能构成更大的正方形，否则不用管是0就好了
                    dp[i][j] = min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1])) + 1;  
                    //以该格子为右下角的最大正方形的边长为左、上、左上三个格子以其为右下角所能构成的最大正方形的边长的最小值+1
                    res = max(res, dp[i][j]);   //更新res
                }
            }
        }
        return res * res;   //返回面积
    }
};