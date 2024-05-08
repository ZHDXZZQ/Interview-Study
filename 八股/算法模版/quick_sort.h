/*
    快速排序：基于分治的，每次选取一个哨兵节点作为枢纽，然后从两头往中间找，将大于枢纽的值放在右边
    将小于枢纽的值放在左边，这样完成一趟排序后，枢纽在中间，枢纽的左边的值都小于枢纽，右边的值都大于枢纽。
    每轮排序都确定了当前枢纽的最终位置，枢纽可以是任意一个值，我们选取中间作为枢纽（哨兵）效果最优。
    然后我们在将枢纽的左右部分作为新的区间进行上述流程，直到子区间为空，相当于每次将序列一分为二
    不稳定的算法，因为子区间内无法考虑到父区间的情况，所以最终结果不稳定。
    时间复杂度：最坏On^2（基本有序时）、平均Onlogn；空间：平均Ologn，最坏On
*/

#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
void quick_sort(std::vector<T>& nums, int l, int r) {
    if (l >= r) {
        return;
    } 
    auto sentinel = nums[l + r >> 1];   // 选择哨兵
    int i = l - 1;  // 设立当前的i和j为两个边界的外边一个，这么做可以方便第一轮时先执行后面++和--
    int j = r + 1;
    while (i < j) {
        do {
            ++ i;       // 先++和后面的先--，同时避免二者指向重复数据而无限循环，
        } while (nums[i] < sentinel);   // i找到左边大于等于哨兵的值

        do {
            -- j;
        } while (nums[j] > sentinel);   // j找到右边小于等于哨兵的值

        if (i < j) {
            std::swap(nums[i], nums[j]);    // 当i还在j的左边时，二者交换
            // 为什么不可以在这里++和--
        }
    }   // 一直循环，直到i达到或超过j
    quick_sort(nums, l, j); // 对两边进行分治，
    // 如果要使用i-1 和 i，上面要用l + r + 1 >> 1，否则会死循环
    quick_sort(nums, j + 1, r);
}

template <class T>
void QuickSort(std::vector<T>& nums) {
    int n = nums.size();
    quick_sort(nums, 0, n - 1);
}