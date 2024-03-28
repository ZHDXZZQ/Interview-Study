// 思路： 二分， 时间Ologn，空间O1
// 1. 没次选中中间的位置，和最后一个位置的数字相比
// 2. 如果当前数字小，则说明那么最小的值一定在当前位置或者左边
// 3. 如果当前数字更大，则说明最小的值一定在这个数的右边

class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r) / 2;      //l=mid+1，所以这里不用+1
            if (nums[mid] <= nums[n - 1]) { //如果这里和nums[0]比找到的就是最大的数
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return nums[l];
    }
};