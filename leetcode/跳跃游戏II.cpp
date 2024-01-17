// 思路： 可以用动态规划，但是需要On空间。这里采用贪心，时间On，空间O1
// 1. 首先记录当前能到达的最远位置
// 2. 记录跳跃次数，以及上次跳跃所能到的最远位置end
// 3. 用i遍历数组，i到end之间为上次跳跃可达的位置，也是本次跳跃可选的起跳位置
// 4. 当i遇到end时，表明本次跳跃可经历的起跳位置已经结束，然后更新end为本次跳跃可到达的最远位置，end到最远位置之间皆可算作下一次跳跃的起跳点

class Solution {
public:
    int jump(vector<int>& nums) {
        int max_far = 0;// 目前能跳到的最远位置
        int step = 0;   // 跳跃次数
        int end = 0;    // 上次跳跃可达最远位置
        for (int i = 0; i < nums.size() - 1; i++) {
            max_far = max(max_far, i + nums[i]);
            // 到达上次跳跃能到达的右边界
            if (i == end) {
                end = max_far;  // 目前能跳到的最远位置变成了下次起跳位置的右边界
                ++ step;         // 进入下一次跳跃
            }
        }
        return step;
    }
};