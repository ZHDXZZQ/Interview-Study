/*
    简单选择排序：每次从未排序的部分选择出一个值最小的数，或最大的数，放到它的最终位置上
    不稳定的算法，最坏/平均时间On^2，空间O1，每轮都至少确定一个元素的最终位置。
*/

#include <algorithm>
#include <vector>

template <class T>
void SelectSort(std::vector<T>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++ i) {
        int min_index = i;
        for (int j =i + 1; j < n; ++ j) {
            if (nums[j] < nums[min_index]) {
                min_index = j;
            }
        }
        std::swap(nums[min_index], nums[i]);
    }
}