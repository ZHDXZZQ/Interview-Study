// 思路： 双指针法，时间On，空间O1。方法同上一题
// 1. pos指针指向结果数组的末尾
// 2. 通过i遍历数组，i一定大于等于pos，又因为是非递减序列，所以i所指元素只可能大于或等于pos所指元素
// 3. 如果i和pos所指元素不等或和pos所指元素的前一个不等，说明结果数组中对于i所指的元素还未达到2个，那么将i所指元素放到pos处，pos更新；否则i继续向后遍历
// 4. 这样pos前所保留的所有元素都是不超过2个的元素

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() <= 2) return nums.size();  //特判
        int pos = 1;
        for(int i = 2; i < nums.size(); ++ i) {
            if(nums[i] != nums[pos] || nums[i] != nums[pos - 1]) {
                nums[++ pos] = nums[i];
            }
        }
        return pos + 1;
    }
};