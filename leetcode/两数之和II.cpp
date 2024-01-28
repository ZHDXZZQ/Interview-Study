// 思路： 双指针法，时间On，空间O1
// 1. 左指针指向开头，右指针指向结尾
// 2. 因为数组非递减，因此，如果二者的和大于目标，则需要大的数变小，即右指针左移
// 3. 同理，如果小于目标，则需要左指针右移
// 4. 如果等于目标，输出从1开始的下标
// 5. 如果指针相遇，则说明没有答案

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        auto n = numbers.size();
        int left = 0;
        int right = n - 1;
        while(left < right) {
            auto sum = numbers[left] + numbers[right];
            if(sum > target) {
                -- right;
            } else if (sum < target) {
                ++ left;
            } else {
                return {left + 1, right + 1};
            }
        }
        return {};
    }
};