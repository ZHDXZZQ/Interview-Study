/*
    思路： 区间dp，时间On^3，空间On^2
    1. dp[i][j]表示将i到j区间内的所有气球打爆的组合中，价值最高的打法，不包含边界i和j
    2. 最外层的两边按1算，因此两边补上1，全部长度为n + 2
    3. 选择一个长度，表示当前要打的区间的长度，长度包含了两个不被打爆的边界
    4. 遍历左右端点，使其不越界，然后选择一个目标，这个目标是每次要被打爆的最终目标，应该位于区间之内
    5. 计算目标左右被打爆的最大价值，最后打爆这个目标，因此直接拿目标和两个边界相乘，取最大值即可
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.emplace_back(1);   // 两边界扩充1
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));   // 初始化全部为0
        for (int len = 3; len <= n + 2; ++ len) {   // 遍历本次要计算的区间长度
            for (int l = 0; l + len - 1 < n + 2; ++ l) {    // 遍历左端点，要保证右端点不越界
                int r = l + len - 1;
                for (int target = l + 1; target < r; ++ target) {   // 在区间内选择最后一个被打爆的气球
                    dp[l][r] = max(dp[l][r], dp[l][target] + dp[target][r] + nums[l] * nums[r] * nums[target]); 
                    // 每次更新区间值，从小区间到大区间更新，可以画图想，比较复杂
                }
            }
        }
        return dp[0][n + 1];
    }
};