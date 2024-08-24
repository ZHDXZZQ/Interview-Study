/*
    希尔排序：先将待排序表分割成若干特殊子表，即把相隔某个“增量”的元素记作一个子表，对各个子表分别进行直接插入排序。
    当整个表中的元素已呈现基本有序时，再对全体记录进行一次直接插入排序。步长一般为5， 3， 1，可以自己设置，也可以二分设置。

    因为从前面的排序方法可知，直接插入排序的时间复杂度是On²，但如果序列有序时，其复杂度是On，由此可知直接插入排序适用于基本有序和数据量不大的排序表。
    希尔排序正是从这两点改进得来的，又称缩小增量排序。

    不稳定的算法，最坏On²，空间O1，仅适用于线性表为顺序存储的情况。
    时间效率依赖于增量序列，当数量在某个特定范围时，复杂度为On^1.3
*/

#include <algorithm>
#include <vector>

template <class T>
void ShellSort(std::vector<T>& nums) {
    int n = nums.size();
    // vector<int> steps = {9, 5, 3, 1};
    int step = n / 2;   // 初始化步长
    int sentry;     // 哨兵记录当前要移动的数字
    for ( ; step >= 1; step /= 2) {     // 步长
        for (int i = step; i < n; ++ i) {   // 遍历每个子区间
            if (nums[i] < nums[i - step]) { // 如果当前数字要换到前面
                sentry = nums[i];   // 哨兵记录当前要更换的这个更小的数字
                int j = i - step;
                for ( ; j >= 0 && nums[j] > sentry; j -= step) {
                    nums[j + step] = nums[j];   // 将区间中前面的数字依次后移
                }
                nums[j + step] = sentry;    // 当前j为区间中插入位置的前一个数字，将要移动的数字插入到正确位置
            }
        }
    }
}