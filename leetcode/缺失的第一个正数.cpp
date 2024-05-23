/*
    思路： 原地哈希，利用当前数组构造哈希表，时间On，空间O1
    1. 将每个数组下标范围内的数字放到对应下标处
    2. 然后从前往后遍历，第一个不与下标对应的数的下标即缺失的第一个正数
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++ i) {
            int& num = nums[i]; // 记录当前位置上的数
            while (num > 0 && num <= n && nums[num - 1] != num) {   //如果当前数符合数组下标范围，且目标位置不是正确的数，则对换
                swap(nums[i], nums[num - 1]);   // 循环对换，直到对换到当前位置的数不符合对换规则
            }
        }   // 此时，所有数已经到达自己的位置
        for (int i = 0; i < n; ++ i) {  // 顺序遍历数组，不匹配的位置即为第一个缺失的正数
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;   // 如果都在自己的位置上，返回下一个数字
    }
};