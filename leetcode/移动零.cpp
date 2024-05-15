/*
    思路： 顺序对换双指针，时间On，空间O1
    1. 第一个指针找到第一个0的位置，然后另一个指针从这个位置往后找
    2. 如果碰到0，则继续找；否则，将当前数字和第一个指针的对象对换，然后两指针前进
    3. 这样，两个指针之间就一定全部都是0，并且其余数字按序存放
    4. 直到第二个指针到达尾部
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int zero_ptr = 0;
        while (zero_ptr < n && nums[zero_ptr] != 0) {   // 找到第一个0
            ++ zero_ptr;
        }
        if (zero_ptr >= n) {    // 如果全都是0，结束
            return;
        }
        int num_ptr = zero_ptr + 1; // 否则的话找到下一个位置开始判断
        while (num_ptr < n) {   // 只要第二个指针没到尾，就继续
            if (nums[num_ptr] != 0) {   // 如果当前指向非0数字
                swap(nums[num_ptr], nums[zero_ptr]);    // 对换，把0换过来，保证非0数字的顺序
                ++ zero_ptr;
            }
            ++ num_ptr; // 指针前进
        }
        return;
    }
};