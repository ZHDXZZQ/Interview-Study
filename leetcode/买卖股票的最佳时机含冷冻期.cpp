/*
    思路： 动态规划，时间On，空间O1
    具体看注释
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp0 = 0, dp1 = -prices[0], dp2 = 0;
        // dp0表示当日无操作且不持股，dp1表示当日买入或持股中，dp2表示当日卖出，三者均表示各自情况的价值
        int old_0 = dp0, old_1 = dp1, old_2 = dp2;  // 记录昨日的情况，方便更新使用

        for (int i = 1; i < n; ++ i) {
            dp0 = max(old_0, old_2);    // 昨天也没操作且未持股的情况和昨日卖出了的最大值，不能与dp1有关系，因为dp0表示当前未持股
            dp1 = max(old_0 - prices[i], old_1);   // 昨天没操作且未持股再能买入，和昨天持股情况取最大值，不能昨日卖出今天买
            dp2 = old_1 + prices[i];  // 表示卖出的情况，前提是昨天买入或持股的情况才能卖出，也可以当天买当天卖，因为当日买入的情况明天还会再计算最大价值
            old_0 = dp0;
            old_1 = dp1;
            old_2 = dp2;
        }
        return max(dp0, dp2);   // 最终的最大值一定是那天卖出或者之前卖出那天没持股的情况，持股的情况一定是小于二者任意一个的
    }
};