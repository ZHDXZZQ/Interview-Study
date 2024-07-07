/*
    思路： 前缀和，时间On，空间O1
    1. 用一个值记录整个数组所有数字的和，用一个值记录当前走过的所有数字的和
    2. 如果当前数字前后的值的和相等，则返回下标
*/

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int suffix = 0; // 记录所有数字的和
        for (auto& num : nums) {
            suffix += num;
        }
        int prefix = 0; // 记录前缀和
        for (int i = 0; i < nums.size(); ++ i) {
            suffix -= nums[i];  // 后缀减掉当前位置的数字
            if (prefix == suffix) { // 如果此时前后缀相同，则该位置就是中心
                return i;
            }
            prefix += nums[i];  // 否则该位置的和被遍历，加入前缀
        }
        return -1;
    }
};