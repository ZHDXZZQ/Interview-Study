/*
    思路： 滑动窗口，时间On，空间On
    1. 用一个窗口记录当前为1的数字，允许窗口中含有一个不为1的数字
    2. 如果新进入的窗口出现了一个不为1的数字，需要弹出之前那个不为1的数字
*/

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = 0;   // 左右窗口
        bool has_other = false; // 窗口内是否有其他值
        int res = 0;
        while (r < n) {
            if (nums[r] != 1) { // 如果新进入的值不为1
                if (has_other == true) {    // 如果已经有其他非1的数字
                    while (nums[l] == 1) {  // 滑动做窗口把上一个非1的数字弹出
                        ++ l;
                    }
                    ++ l;
                } else {    // 如果没有非1的数字，不管
                    has_other = true;
                }
            }
            ++ r;   // 滑动右窗口
            res = max(res, r - l);  // 记录当前窗口内的数字
        }
        return res - 1; // 删掉一个字符就是最多的1的情况
    }
};