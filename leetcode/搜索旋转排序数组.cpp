// 思路：二分，时间Ologn，空间O1
// 1. 本题最麻烦的点在于要考虑边界问题，而且要全面整体的考虑
// 2. 首先找到原本的终点，即最大值所在位置（或找最小值，思路相同），这里第一次二分来查找，如果中间值小于头，则最大值在左边，否则在右边
// 3. 然后判断目标值和头的比较，如果目标值大于头，则在刚刚找到的起点左边二分，否则在右边
// 4. 二分要注意，如果配置了l=mid，那么取mid要先+1，否则会死循环

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0;
        int r = n - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;      //二分时，如果下面的判断方式是l=mid，这里一定要+1再除以2
            if (nums[mid] >= nums[0]) {      //这里加不加等号都可，找到的是最大的值
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (target >= nums[0]) {
            l = 0;                  //如果目标值大于头，则在刚刚找的值得左边
        } else {
            ++ l;                   //否则在右边
            r = n - 1;
        }
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[mid] >= target) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        if (nums[r] == target) { return r; }    //这里只能返回r，因为l最后的操作时+1可能越界
        return -1;
    }
};