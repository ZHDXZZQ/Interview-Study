/*
    思路： 哈希表，时间On，空间On。也可以使用排序双指针？
    1. 存储每个数字的个数
    2. 判断能与当前数字合成目标数的数字是否还有剩余
    3. 如果有的话两两一对减去
*/

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> num_cnt;
        for (auto& num : nums) {    // 记录每个数字的数目
            ++ num_cnt[num];
        }
        int res = 0;
        for (auto& num : nums) {
            if (num_cnt[num] > 0) { // 如果当前数字在前面没有被使用过
                -- num_cnt[num];
                if (num_cnt[k - num] > 0) { // 如果和他配对的数字还有剩余
                    ++ res;
                    -- num_cnt[k - num];    // 二者组成一对出来
                } else {
                    ++ num_cnt[num];    // 否则这个数字不参与计算
                }
            }
        }
        return res;
    }
};