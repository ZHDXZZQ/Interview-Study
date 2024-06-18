/*
    思路： 动态规划，时间On，空间On，可优化为O1
    1. 对于爬到每一层楼梯，只需要计算爬到上一阶的最小花费+从那一层爬的花费
    2. 以及爬到上上阶的最小花费+从那一层爬的花费，取二者min即可
    3. 因此空间只需要两个来记录上一层和上上层的即可
*/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++ i) { // 从第二阶开始计算，最高阶为n + 1，即顶层
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[n];
    }
};