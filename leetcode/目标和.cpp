/*
    思路： dfs，时间O2^n，空间On
    1. 每次都对当前数字进行加和减进行深度搜索
    2. 当到达结尾时判断和是否为目标
    3. 否则的话继续进行加减深搜
*/

class Solution {
public:
    int n;
    int res;

    void dfs(vector<int>& nums, int& target, int pos, int sum) {
        if (pos >= n) {
            if (sum == target) {
                ++ res;
            }
            return ;
        }
        dfs(nums, target, pos + 1, sum + nums[pos]);
        dfs(nums, target, pos + 1, sum - nums[pos]);
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        n = nums.size();
        res = 0;
        dfs(nums, target, 0, 0);
        return res;
    }
};