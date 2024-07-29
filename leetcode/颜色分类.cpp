/*
    思路： 三指针，分别管理自己的区域，时间On，空间O1
    1. zero指针表示其左边的部分都是0，two表示其右边的部分都是2
    2. zero到one指针之间一定都是1
    3. 因为one用来遍历，已经把2都移到右边，0都移到左边，而one指针一定快于zero，因此之间都是1，zero所指的值也是1
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int zero = 0, one = 0, two = n - 1;
        while (one <= two) {
            if (nums[one] == 0) {
                swap(nums[one], nums[zero]);
                ++ zero;
                ++ one;
                // 这里必须要++one，因为one和zero最开始指向同一个位置，有可能会死循环，而且要保证one在zero指针后面
            } else if (nums[one] == 2) {
                swap(nums[one], nums[two]);
                -- two; // 这里不能++one，因为避免one和two是挨着的两个
                // 假设此时two下是0，one下是1，那么交换后，循环结束，但是two下的0交换到前一个位置，并没有放到0的位置去
                // 因此two下的数字被转换过来后，需要进行二次判断
            } else {    // 如果指向1，就继续往后指
                ++ one;
            }
        }
        return ;
    }
};