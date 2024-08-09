/*
    计数排序：通过统计每个元素出现的次数，然后依次输出每个元素，从而达到排序的目的。
    时间On，空间On，稳定
    适用于数据范围不大的整数数组。
*/

#include <algorithm>
#include <vector>

template <class T>
void CountingSort(std::vector<T>& nums) {
    if (nums.empty()) {
        return;
    }

    int n = nums.size();

    // 找到数组中的最大值和最小值
    auto maxVal = *std::max_element(nums.begin(), nums.end());
    auto minVal = *std::min_element(nums.begin(), nums.end());

    // 计算范围大小
    int range = maxVal - minVal + 1;

    // 创建计数数组并初始化为0
    std::vector<T> count(range, 0);

    // 统计每个元素出现的次数
    for (auto num : nums) {
        ++ count[num - minVal];
    }

    int pos = 0;
    for (int i = 0; i < range && pos < n; ++ i) {
        while (count[i] --) {       // 按序将每个数字填入，每个数字填入n次
            nums[pos] = minVal + i;
            ++ pos;
        }
    }

    return;
}