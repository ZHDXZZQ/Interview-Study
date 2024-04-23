// 思路： 区间dp，时间On^2，空间On^2，可以利用滚动数组优化到On
// 1. dp[i][j]代表，在i-j这个区间内，你先手所能获得的最优得分-对方所能获得的得分
// 2. 因此我们在取数字时，可以取两端的任一个，就可以得到剩下的序列中，对方得到的最优分-我所能在剩余方案的得分
// 3. 在这个分数上求相反数，可以得到在剩余序列中，我所能获得的分-对方所能得到的最优分
// 4. 每次取最大值即可

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n));  //可以利用滚动数组降维
        for (int len = 1; len <= n; ++ len) {       //构建dp数组，len表示当前最大序列的长度，从1到n
            for (int i = 0; i + len - 1 < n; ++ i) {    //i表示左端点，j表示右端点，对于每种长度，遍历所有可能的的系列
                int j = i + len - 1;
                if (len == 1) {         //如果长度为1，当前我们先手所能获得的最优分即为当前位置爹分
                    dp[i][j] = nums[i];
                } else {        //否则的话，当前我们先手的最优分，即为取某一端点，然后加上我们在剩余序列中所能获得的最优分，因为dp[i][j]表示的是先手方所能获得的最优分-后手方
                    dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]); //因此在我们取完端点后，所得到的dp是对方在剩余序列得到的最优分-我方的分，因此是减去
                }
            }
        }
        return dp[0][n - 1] >= 0;   //判断全序列我方最优分是否为非负数，如果为非负数，说明我方得分可能优于对方得分
    }
};