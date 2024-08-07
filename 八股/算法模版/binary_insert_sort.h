/*
    折半插入排序：二分插入排序：先二分的找到新元素需要插入的位置
    然后统一移动后面的元素腾出空间
    时间On^2因为每次仍需移动n个元素，空间O1，稳定的排序算法
*/

#include <algorithm>
#include <vector>

template <class T>
void BinaryInsertSort(std::vector<T>& nums) {
    int n = nums.size();
    int i, j, low, high, mid;
    auto sentry = nums[0];  // 哨兵，为本次要插入的数字
    for (i = 1; i < n; ++ i) {
        sentry = nums[i];
        low = 0, high = i - 1;
        while (low <= high) {   // 二分找到这个要插入的数字的位置
            mid = (low + high) / 2;
            if (nums[mid] > sentry) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }   // high + 1即为要插入的数字的位置，即前面的数字都小于等于哨兵，保持稳定
        for (j = i - 1; j >= high + 1; -- j) {
            nums[j + 1] = nums[j];  // 所有数字都往后移动一格
        }
        nums[high + 1] = sentry;    // 插入这个数字
    }
    return;
}