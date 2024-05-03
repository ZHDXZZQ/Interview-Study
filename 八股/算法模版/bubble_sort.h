/*
    冒泡排序：从后往前（或从前往后）两两比较相邻元素，若为逆序，则交换他们，直到序列比较完
    稳定的算法，最坏/平均时间On^2，空间O1，每轮都至少确定一个元素的最终位置。
*/

#include <algorithm>
#include <vector>

template <class T>
void BubbleSort(std::vector<T>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++ i) {
        bool flag = false;  // 优化，如果某次未交换，可以提前结束算法
        for (int j = n - 1; j > i; -- j) {
            if (nums[j - 1] > nums[j]) {
                std::swap(nums[j - 1], nums[j]);
                flag = true;
            }
        }
        if (flag == false) {
            return;
        }
    }
}