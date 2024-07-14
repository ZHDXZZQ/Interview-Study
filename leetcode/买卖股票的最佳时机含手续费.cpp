/*
    思路： 状态机DP，时间On，空间O1
    dp[i][0]表示第i天手里没有股票情况的钱，dp[i][1]表示第i天手里有股票情况的钱
    只需要考虑前一天的有股票和没股票的状态，因此可以不用额外空间
    1. 每一天手里没股票的情况只有两种操作：不买，或者买入
    2. 每一天手里有股票的情况也只有两种操作；不卖，或者卖出
    3. 需要考虑手续费，每次计算最大值即可
*/

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int yesterday_no = 0, yesterday_have = -prices[0];  // 初始化当前状态，第一天没买和第一天买了
        int res = 0;
        for (int i = 1; i < n; ++ i) {  // 遍历后面每一天
            int tmp = yesterday_no; // 临时存储
            yesterday_no = max(yesterday_no, yesterday_have + prices[i] - fee); // 今天没股的情况为，昨天也没有且今天没买，或者昨天有但今天卖了，取最大值
            yesterday_have = max(tmp - prices[i], yesterday_have);  // 今天有股的情况为，昨天有股且今天没卖，或者昨天没股但今天买了，取最大值
            // 手续费在哪里加都行，这里加在了卖出时
            res = max(res, yesterday_no);   // 取当前没股的最大值，最后一天过后就是这段时间所有操作后手里没股的最大收益
        }
        return res;
    }
};