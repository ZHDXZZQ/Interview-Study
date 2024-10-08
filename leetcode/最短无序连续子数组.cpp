/*
    思路： 双指针，时间On，空间O1
    1. 首先是要找到一个子数组，排序后使得整体升序，所以这一定是一个区间，这个区间我们用两个指针来找
    2. 区间前后一定是有序的，因此可以找到前后第一个无序的部分作为起始端点
    3. 然后区间中的数字大小一定是位于两边的有序的数字的大小之间的
    4. 因此如果两边端点外的数如果未能包含区间中的数，则向两边扩大区间，代表这些数字也要参与排序
*/

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < n - 1 && nums[l] <= nums[l + 1]) {   // 左端点从左往右找到第一个降序的数字
            ++ l;
        }
        if (l == n - 1) {   // 如果找到头了，则已经全部有序
            return 0;
        }
        while (r > 0 && nums[r - 1] <= nums[r]) {   // 否则右端点从右往左找到第一个升序的数组
            -- r;
        }
        for (int i = l + 1; i < n; ++ i) {      // 遍历左端点右边的数字，一定要保证左端点小于其右边的全部数字，避免即使有序但是大小不符合要求的情况，也得参与排序
            while (l >= 0 && nums[l] > nums[i]) {   // 区间前面的数字一定要小于区间中及后面的所有数字，否则参与排序
                -- l;
            }
        }
        for (int i = r - 1; i >= 0; -- i) {     // 同理，让区间右边的数字一定都要大于区间中以及左边的数字
            while (r < n && nums[i] > nums[r]) {
                ++ r;
            }
        }   // 此时l和r就是指向最终的无需排序的数字
        return r - l - 1;   // 区间中的数字就是要排序的数字
    }
};