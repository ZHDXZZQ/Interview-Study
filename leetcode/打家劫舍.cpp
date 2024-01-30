// 思路： DP，时间On，空间O1
// 1. 偷某个房子，我们只需要考虑两种情况
// 2. 第一个是偷上上个房子和这个房子。第二个是偷上个房子而不偷这房子。
// 3. 因此我们只需要记录偷上个房子能偷到的最大金额和偷上上个房子能偷到的最大金额，进行递归

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];  //特殊情况，只有一个房子或两个房子，偷最值钱的那个
        else if(n == 2) return max(nums[0], nums[1]);
        int one_gap = max(nums[0], nums[1]);    //one_gap用来表示偷到上一房子能偷到的最多的钱
        int two_gap = nums[0];                  //two_gap用来表示偷到上上个房子能偷到的最多的钱
        int res = 0;
        for(int i = 2; i < n; ++ i) {           //从第三个房子开始遍历
            res = max(two_gap + nums[i], one_gap);  //二种偷法中选择钱最多的偷法
            two_gap = one_gap;              //更新上个房子和上上个房子所指的房子
            one_gap = res;
        }
        return res;
    }
};