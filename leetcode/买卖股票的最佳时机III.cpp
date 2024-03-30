// 思路： 前后缀分解，时间On，空间On。用dp可以优化到空间O1
// 1. 将两次交易进行划分，以第二次买入作为分界点依次判断
// 2. 利用一个dp数组记录第一次买入卖出的最高收益，dp[i]表示i天之前的最大收益
// 3. 然后从后往前计算一个后缀，表示第二次买卖的最大收益，然后加上该节点之前的最大收益，即为两次买卖的最大收益

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> dp(n + 1, 0);   //dp[i]表示i天之前进行第一次买卖的最高收益
        int min_price = INT_MAX;    //从前往后统计当前股票的最低价格
        int max_price = -1;         //从后往前统计当前股票的最高价格
        for (int i = 1; i <= n; ++ i) { //i总是表示当天的后一天，方便计算
            dp[i] = max(dp[i - 1], prices[i - 1] - min_price);  //前一天买卖的最高价和今天卖出的最高价去max
            min_price = min(min_price, prices[i - 1]);  //更新目前为止的最低价
        }
        int res = 0;
        for (int i = n; i > 0; -- i) {  //从最后一天开始，看看后续哪次买入更划算
            //同样的，i总是比实际天数大一天
            res = max(res, max_price - prices[i - 1] + dp[i - 1]);
            //计算当天买入可赚取的最高金额 + 当天之前进行交易的最高利润，即两次买卖的最高价
            //注意dp[i-1]表示的i-2天及之前进行交易一次的最高收益
            max_price = max(max_price, prices[i - 1]);  //更新目前为止的最高价
        }
        return res;
    }
};