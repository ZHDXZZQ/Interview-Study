// 思路： 用结果数组存储左乘积，一个变量存储右乘积，不用除法。时间On，空间O1（结果数组不算做额外空间）
// 1. 首先讲结果数组的每一位表示原数组该位左边的所有数（包含自己）的乘积
// 2. 用一个变量表示某位置右边所有数的乘积
// 3. 从后往前遍历结果数组，每个元素等于其左边所有数的乘积乘右边所有数的乘积，同时每次更新右边所有数的乘积
// 4. 特殊情况处理结果数组的第一个元素

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), nums[0]);  //结果数组，特殊处理res[0]
        for(int i = 1; i < nums.size(); ++ i) {
            res[i] = nums[i] * res[i - 1];      //令结果数组的每一位等于其包含自己的左边所有数的乘积
        }
        int right_sum = 1;   //存储右边所有数的乘积
        for(int i = nums.size() - 1; i >= 1; -- i) {  //从后往前遍历结果数组
            res[i] = res[i - 1] * right_sum;    //每一位等于其左边所有数的乘积乘右边所有数的乘积
            right_sum *= nums[i];   //更新右边所有数的乘积
        }
        res[0] = right_sum;     //特殊处理res[0]，如果res[i]表示的纯粹是左边所有数的乘积，则不需要这么麻烦的处理
        return res;
    }
};