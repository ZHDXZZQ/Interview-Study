// 思路： 双指针法，时间On，空间O1
// 1. pos指针指向结果数组的末尾
// 2. 通过i遍历数组，因为是非递减序列，所以i所指元素只可能大于或等于pos所指元素
// 3. 如果i和pos所指元素相等，那么i继续向后；否则将i所指元素放到pos处，pos更新
// 4. 这样pos前所保留的所有元素都是唯一元素

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() <= 1) return nums.size();  //特判
        int pos = 0;
        for(int i = 1; i < nums.size(); ++ i) {
            if(nums[i] != nums[pos]) {
                nums[++ pos] = nums[i];
            }
        }
        return pos + 1;
    }
};