/*
    思路：前缀和，时间On，空间On
    1. 利用umap记录当前位置前面所有数字的和的个数（从头开始的）
    2. 当前和-k如果存在，则表示前面有前缀和为sum-k的前缀和，
       那么当前和的位置减去sum-k的和的位置之间的数字的和就为k，即一种答案
    3. 然后将当前前缀和记录下来
*/

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0;
        int res = 0;
        unordered_map<int, int> rec;
        ++ rec[0];  // 初始化和为0的前缀和数量为1
        for (auto& num : nums) {
            sum += num; // 记录从头到当前位置的所有数字的和
            res += rec[sum - k];    // 如果当前和-k存在前缀和，则加上其数量
            ++ rec[sum];    // 将当前前缀和记录
        }
        return res;
    }
};