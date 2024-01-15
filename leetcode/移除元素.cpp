// 思路：双指针法，时间On，空间O1
// 1. 一个指针pos指向结果数组的末位
// 2. 另一个指针遍历数组，将非val的元素放到pos位置，并更新pos，保证前pos个元素不包含val
// 3. 如果遇到val，则直接遍历下一个，pos位置不动
// 4. 这样在遍历完一遍数组后，非val的值都放到了前pos个且没有丢失

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int pos = 0;  //指向排除掉val的数组的末位
        for(int i = 0; i < nums.size(); ++ i) {
            if(nums[i] != val) {   //如果当前位置值不为val，摆到pos处；如果为val，则pos不动
                nums[pos ++] = nums[i];
            }
        }
        return pos;
    }
};