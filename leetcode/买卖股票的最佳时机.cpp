// 思路： 记录最大利润，同时更新最小买入价。时间On，空间O1
// 1. 首先记录最低的买入价
// 2. 每天查看是否当天买入会更便宜，并更新
// 3. 同时计算是否当天卖出利润更高，并更新

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = prices[0];  //最低的买入价
        int res = 0;    //最大利润
        for(auto& money : prices) {
            int profit = money - buy;  //当前利润
            res = max(res, profit);   //利润取最大值
            buy = min(buy, money);      //买入价取最小值
        }
        return res;
    }
};