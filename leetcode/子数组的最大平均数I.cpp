/*
    思路： 滑动窗口，时间On，空间O1
    1. 每次计算当前k个数字作为一个窗口内的所有数字的和，并更新平均数
    2. 每次移动一个窗口，弹出前面的数字，加入新的数字，并计算平均数更新结果
*/

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0;
        int r = 0;  // 窗口左右两端
        double cur_sum = 0.0;   // 当前窗口内的和
        while (r < k) { // 统计初始窗口
            cur_sum += static_cast<double>(nums[r]);
            ++ r;
        }
        double res = cur_sum / double(k);   // 初始窗口的平均值
        while (r < n) {
            cur_sum += static_cast<double>(nums[r]);    // 之后每次窗口往后移动一格并计算
            cur_sum -= static_cast<double>(nums[l]);
            ++ l;
            ++ r;
            res = max(res, cur_sum / double(k));
        }
        return res;
    }
};