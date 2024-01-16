// 思路： 巧妙计数法，时间On，空间O1
// 1. 目标元素数量一定大于一半，也就是说目标元素和其他元素一一抵消，也一定会生剩余一个目标元素
// 2. 因此遍历数组，记录当前元素的个数以及值，一一比较，如果相同则个数增加
// 3. 如果不同则个数减少，如果个数为0表示当前数被抵消，选取新的元素作为当前数并置cnt为1
// 4. 重复上述步骤，最后留下的当前数必为目标元素

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cur_num = nums[0];  //记录当前数
        int cnt = 1;             //记录当前数个数
        for(auto& num : nums) {
            if(num == cur_num) { //如果遍历目标为当前数，个数+1
                ++ cnt;
            } else {
                if(-- cnt <= 0) { //否则个数-1，如果个数为0，则替换当前数并重置cnt
                    cur_num = num;
                    cnt = 1;
                }
            }
        }
        return cur_num;
    }
};