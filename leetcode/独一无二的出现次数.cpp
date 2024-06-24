/*
    思路： 哈希表，时间On，空间On
    1. 用一个哈希表存储每个数字出现的个数
    2. 另一个哈希表存储每个出现个数的个数
*/

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> num_cnt;    // 每个数字出现的个数
        unordered_map<int, int> cnt_cnt;    // 每个数字出现的个数的个数
        for (auto& num : arr) { 
            if (num_cnt.count(num)) {   // 如果之前出现过这个数字
                -- cnt_cnt[num_cnt[num]];   // 因为本次多了一个，所以要把之前那个次数减掉
            } else {
                num_cnt[num] = 0;   // 否则的话第一次出现初始化为0
            }
            auto& cnt = num_cnt[num];
            ++ cnt; // 出现次数+1
            ++ cnt_cnt[cnt];    // 该出现次数的出现次数+1
        }
        for (auto& iter : cnt_cnt) {    // 遍历所有出现次数
            if (iter.second > 1) {  // 如果某个大于1，说明有不唯一的出现次数的数字
                return false;
            }
        }
        return true;
    }
};