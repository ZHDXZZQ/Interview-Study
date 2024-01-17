// 思路： 记录当前能到达的最远位置，遍历时更新，时间On，空间O1
// 1. 遍历数组，判断是否能到达当前下标
// 2. 同时更新能到的的最远位置
// 3. 最后判断是否能到达最后

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int can_get_pos = 0;  //当前能到达的最远位置
        for(int i = 0; i < nums.size(); ++ i) {   //遍历数组，如果当前能到达的最远位置小于i，表明跳不到最后
            if(can_get_pos < i) return false;
            can_get_pos = max(can_get_pos, i + nums[i]);  //否则的话更新能到的最远位置
        }
        if(can_get_pos >= nums.size() - 1) return true;  //如果能到的位置是最后一个下标或更远，则成功
        return false;
    }
};