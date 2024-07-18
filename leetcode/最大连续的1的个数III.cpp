/*
    思路：滑动窗口，时间On，空间O1
    1. 每次记录当前窗口内非1数字的个数
    2. 当超过k个时，需从左边弹出一个非1的数字
    3. 每次统计窗口内数字的数量
*/

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int cnt = 0;
        int res = 0;
        int l = 0, r = 0;
        while (r < n) {
            if (nums[r] != 1) { // 如果要滑入窗口的数字不为1
                ++ cnt; // 记录一个
                if (cnt > k) {  // 如果超过k个
                    while (nums[l] == 1) {  // 从左边弹出一个非1的数字
                        ++ l;
                    }
                    ++ l;
                    -- cnt;
                }
            }
            ++ r;
            res = max(res, r - l);  // 记录当前窗口的值
        }
        return res;
    }
};