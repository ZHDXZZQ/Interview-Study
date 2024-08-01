/*
    思路： 动态规划，时间On，空间O1
    1. 每一步计算出当前区间的正数最大值和负数最小值，如果碰到0则全部为0开始新的遍历
    2. 因为只需要考虑正数、负数和0，对于正数，希望碰到一个正数，会更大，碰到负数，希望碰到一个负数，也会更大
    3. 因此每一步即使乘起来变成负数变小了，也要保留，因为下一个可能是个负数而变大，只有0的情况需要清0，每轮都记录一下当前可能的最大值
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        double res = nums[0];
        double biggest = nums[0], smallest = nums[0];
        for (int i = 1; i < n; ++ i) {
            const double& num = nums[i];
            double next_big = biggest * num;    // 旧区间的最大值*该数
            double next_small = smallest * num; // 旧区间的最小值*该数
            biggest = max(num, max(next_big, next_small));  // 选出新的最大值和最小值，如果为0则直接全部为0
            smallest = min(num, min(next_big, next_small));
            res = max(res, biggest);    // 每轮记录新的最大值
        }
        return static_cast<int>(res);
    }
};