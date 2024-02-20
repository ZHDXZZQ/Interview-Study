// 思路： DP，时间On，空间O1
// 1. 每次记录当前和，如果当前的和为负数了，则置为0，后面直接抛弃前面即可
// 2. 每次更新答案为最大值

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;
        int cur_sum = 0;        //记录当前和，因为有可能nums中全是负数，所以需要一个变量来辅助
        for(auto& num : nums) {
            cur_sum += num;     //记录当前连续数的和
            res = max(res, cur_sum);    //更新答案
            if(cur_sum < 0) cur_sum = 0;    //如果当前和小于0，抛弃即可
        }
        return res;
    }
};