/*
   直接插入排序：适用于顺序存储，从前往后遍历，如果当前数字小于前一个数，说明该数字要往前移动
   设立哨兵，找到这个数应该在的位置，将这个数插入，往前查找的过程中，依次移动每个数字
   稳定的，空间O1，时间On²，适用于线性表。不能确定每个数的最终位置，但是已经排好的部分时有序的
*/

#include <algorithm>
#include <vector>

template <class T>
void InsertSort(std::vector<T>& nums) {
    int n = nums.size();
    auto sentry = nums[0];      // 哨兵
    for (int i = 1; i < n; ++ i) {  // 遍历每个数字
        if (nums[i] < nums[i - 1]) {    // 如果比前面的小，因为前面的已经有序，所以它一定要在前面找个地方插入
            sentry = nums[i];   // 设置为哨兵
            int j = i - 1;      // 从前一个开始判断
            while (nums[j] > sentry && j >= 0) {    // 找到它的插入位置
                nums[j + 1] = nums[j];  // 查找过程中，把每个数字都后移，腾位置
                -- j;
            }
            nums[j + 1] = sentry;   // 找到位置，插入
        }
    }
}