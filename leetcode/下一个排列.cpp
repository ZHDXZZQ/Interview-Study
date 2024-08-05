/*
    思路： 找规律，时间On，空间O1
    形如1 2 5 4 2  ->   1 4 2 2 5
    可以发现规律，如果是纯递增序列，如12345，那么结果是12354，尽量从较小的位交换
    如果结果是54321，那么已经是最大，直接反转变成12345
    如果是23541，可以发现一定是有递增有递减的，那么从后往前找到第一个递减的位置
    比如后面的541其实是已经不可再动的，因为这三个数怎么组合都不会比541更大，那么第一个递减的位置就是3
    此时我们知道，3541的组合，5和4打头都会更大，那么比他的大的最小值是多少？
    一定是4打头，因为5打头就太大了，3打头没有更大的数了，所以4打头，我们找到比3大的最小的值，即4而不是5
    然后替换位置得到4531，此时变大了，但是还有更小的情况，因为替换后也一定是531这种递减的，因为541本来就是递减的，而3找到的是最后一个比他大的数
    此时反转531得135，即是顺序最小值，得到24135为最小值
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int ptr = n - 1;
        while (ptr && nums[ptr - 1] >= nums[ptr]) { // 从后往前找到第一个逆序的值，此时ptr指向后往前递增的最大值，ptr-1为第一个递减的值
            -- ptr;
        }
        if (ptr == 0) { // 如果已经到头，说明纯逆序，反转即可
            reverse(nums.begin(), nums.end());
            return;
        }
        int next_smallest_bigger = ptr - 1; // 找到第一个递减的之
        int cur = nums[next_smallest_bigger];
        while (next_smallest_bigger < n - 1 && nums[next_smallest_bigger + 1] > cur) {
            ++ next_smallest_bigger;    // 往后找，找到最后一个比他大的数
        }
        swap(nums[next_smallest_bigger], nums[ptr - 1]);    // 替换后，后面也是递减序列
        reverse(nums.begin() + ptr, nums.end());  // 反转后面这部分，得到结果
        return;
    }
};