// 思路： 二分，时间Ologn，空间O1
// 1. 二分查找，注意判断特殊情况

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;      //当前查找区间的两边界
        while(left < right) {                       //如果边界没有重合，则开始查找
            int mid = left + right >> 1;            //因为是有序的，所以确定区间的中点，判断中点值与目标值的大小关系
            if(target > nums[mid]) left = mid + 1;  //如果目标值更大，则在右边的区间继续查找
            else right = mid;                       //否则在左边的区间继续查找
        }                                         //此时左右边界一定重合，而不会反向错开
        if(target > nums[right]) return right + 1;   //如果目标值大于当前值，表明要插入到当前位置的右边
        return left;                                //否则的话是要插入到当前位置，或者恰好就是该值
    }
};