// 思路： 状态机DP，时间
// f[i, j]表示当前在第i天，已经完成了j笔交易，目前处于无股票在手的状态的最大收益
// g[i, j]表示当前在第i天，已经完成了j-1笔交易，目前手里握有一支股票的状态的最大收益
// 在第i天，对于f来说，可以选择不买入股票，也可以选择买入股票转移到g，也可能从g卖出该股票转移过来
// 即f[i, j] = max(f[i - 1][j], g[i - 1][j] + price[i])
// 在第i天，对于g来说，可以选择卖出股票转移到f，也可以选择不卖出股票，也可能从f买入该股票转移过来
// g[i, j] = max(g[i - 1][j], f[i - 1][j - 1] - price[i])
// 具体看下面的流程

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        int INF = 1e8;
        if (k >= n / 2) {   //n天最多买卖n/2次，如果k大于该数字，表明这n天内我们可以买卖任意多次，即转变为了II中的问题，我们算买卖任意次的最大价值即可
            int res = 0;
            for (int i = 1; i < n; ++ i) {
                if (prices[i] > prices[i - 1]) {
                    res += prices[i] - prices[i - 1];   //只要今天价格比昨天高，就赚一部分
                }
            }
            return res;
        }
        vector<vector<int>> f(n, vector<int>(k + 1, -INF)); //定义状态数组，可以利用滚动数组优化，暂时先不写优化版本了
        vector<vector<int>> g(n, vector<int>(k + 1, -INF)); //这里建议手动定义成-INF，因为INT_MIN无法再减去一个数字
        int res = 0;
        for (int i = 0; i < n; ++ i) {  //遍历n天
            for (int j = 0; j <= k; ++ j) { //遍历k次交易
                if (i == 0) {       //如果是第一天
                    f[0][0] = 0;    //对于f来说初始化为0
                    g[0][1] = -prices[0];   //对于g来说初始化第一次交易的最大价值，g[0][0]没意义
                    break;          //初始化完成
                } else {            //后面的每一天按约定的状态转移方程计算
                    f[i][j] = max(f[i - 1][j], g[i - 1][j] + prices[i]);    //更新第i天完成j笔交易的最大价值
                    g[i][j] = g[i - 1][j];      //这里因为j可能等于0，因此多加了一重判断，实际上酸的还是第i天正在进行第j笔交易的最大价值
                    if (j != 0) {
                        g[i][j] = max(g[i][j], f[i - 1][j - 1] - prices[i]);
                    }
                    res = max(res, f[i][j]);    //更新结果，看看几笔交易最赚
                }
            }
        }
        return res;
    }
};