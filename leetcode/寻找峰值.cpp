// 思路： 二分，时间Ologn，空间O1
// 1. 首先判断两个边界，如果两个边界存在峰值，则直接返回，可以避免只有2个数或者唯一峰值在边界的情况
// 2. 其次，题目给了条件相邻值一定不等，并且该题一定有峰值
// 3. 那么可以二分判断中间点，如果他是峰值则返回，如果不是则找两边更大的那边一定有峰值

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) { return 0; }       //如果只有1个数，这就是峰值
        int l = 0;
        int r = n - 1;
        if (nums[0] > nums[1]) { return 0; }    //边界特判，判断左右边界是否是峰值
        else if (nums[n - 1] > nums[n - 2]) { return n - 1; }
        while (l < r) {
            int mid = (l + r) / 2;      //二分，每次选择中间节点
            if (nums[mid] < nums[mid + 1]) {    //中间节点的值和任一边判断，如果旁边你的更大则说明这边一定有峰值
                l = mid;                    //反之则说明另一边一定有峰值
            } else {
                if (nums[mid] > nums[mid - 1]) {    //如果该点比两边都大，自己就是峰值
                    return mid;
                }
                r = mid;
            }
        }
        return 0;
    }
};