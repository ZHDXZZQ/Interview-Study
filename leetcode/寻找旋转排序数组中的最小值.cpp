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
            if (nums[mid] <= nums[n - 1]) { //如果这里和nums[0]比找到的就是最大的数，这里为什么是最右边呢？
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return nums[l];
    }
};

// 牛客
// 思路： 二分， 时间Ologn，空间O1
// 1. 每次选中中间的位置，和区间内最后一个位置的数字相比
// 2. 如果当前数字小，则说明那么最小的值一定在当前位置或者左边
// 3. 如果当前数字更大，则说明最小的值一定在这个数的右边

class Solution {
public:
    int minNumberInRotateArray(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r) / 2;      //l=mid+1，所以这里不用+1
            if (nums[mid] < nums[r]) { // 如果中间的比右边的小，说明中间往后是有序的，最小值一定在左边，包含中间
                r = mid;
            } else if (nums[mid] > nums[r]) {   // 如果中间值大了，说明中间值原来一定是在后边的，那么最小值一定在右边
                l = mid + 1;
            } else {    // 如果相等了，可能是重复数，那么最小值有可能在两边，通过缩小区间范围来确定位置
                -- r;
            }
        }
        return nums[r];
    }
};

/*12345
        23451
        34512
        45123
        51234*/
//这个题应该是十月份还是九月底在实验室思考的题，另一个链表合并是10.12号在CC做的？那个时候很开心啊