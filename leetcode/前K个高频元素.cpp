/*
    思路： 计数器计数，时间On，空间On
    1. 利用一个umap记录每个数字出现的次数
    2. 利用一个vec，下标作为出现次数，记录每个出现次数出现的次数
    3. 利用一个变量统计前k大个出现次数的次数
    4. 再遍历umap，将出现次数大于目标值的数字插入结果中
*/

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (auto& num : nums) {    // 记录每个数字的出现次数
            ++ cnt[num];
        }
        vector<int> rec(nums.size() + 1, 0);
        for (auto& [k, v] : cnt) {  // 记录每个数字出现次数的出现次数
            ++ rec[v];
        }
        vector<int> res;
        int i = nums.size();    // 找出前k大个出现次数的次数
        while (k) {
            k -= rec[i];
            -- i;
        }
        for (auto& it : cnt) {  // 将符合要求的数字插入结果
            if (it.second > i) {
                res.emplace_back(it.first);
            }
        }
        return res;
    }
};