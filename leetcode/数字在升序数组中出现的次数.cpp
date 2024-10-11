/*
    思路：二分，时间Ologn，空间O1
    1. 利用小数找不存在的数的位置
    2. 位置之间的数字个数就是结果
*/

class Solution {
public:
    int find(vector<int>& nums, float target) {
        int n = nums.size();
        int l = 0, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (nums[mid] >= target) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return r;
    }
    
    int GetNumberOfK(vector<int>& nums, int k) {
        // write code here
        return find(nums, k + 0.5) - find(nums, k - 0.5);
    }
};