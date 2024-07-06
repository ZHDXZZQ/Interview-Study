/*
    归并排序：时间Onlogn，空间On，稳定的排序算法
    设置每轮的归并段大小，如1，2，4，... 以此类推
    每轮将数组分成多个集合，每个集合就是当前归并段的大小
    对这多个归并段两两合并，最开始都是1个，这两个大小为1的段合并后，变成大小为2的段，这个段内是有序的
    然后下一轮就是把这多个大小为2的有序段再合并成大小为4的有序段，直到合成完毕
    对于最后一个不满足归并段大小的段，我们先不管，因为一定会有一次将他合并进来，对于最后一个段无需考虑大小，也无须考虑本轮是否参与合并，因为后续一定会合并
*/

#include <algorithm>
#include <vector>

int n;

template <class T>
void merge_sort(std::vector<T>& nums, int l, int r) {
    if (l >= r) { return; } // 如果当前段的左右边界相同了，那么无需合并
    int mid = l + r >> 1;   // 选出当前段的中点，至少能划分成两个大小为1的归并段，两边的段一定都是有序的
    merge_sort(nums, l, mid);   // 递归的处理两边的每个子段，递归到一个大小为2的子段，将其拆分为大小为1的两个段开始排序
    merge_sort(nums, mid + 1, r);
    std::vector<T> temp(r - l + 1); // 建立一个缓存，用作存储当前两个段排序的结果
    int k = 0, i = l, j = mid + 1;  // i表示左边段的开头，j表示右边段的开头，k表示当前缓存存储的位置
    while (i <= mid && j <= r) {    // 两个段都没有合并完
        if (nums[i] <= nums[j]) {   // 因为都是有序的，所以找到当前两个段头更小的那个，顺序存入缓存
            temp[k ++] = nums[i ++];
        } else {
            temp[k ++] = nums[j ++];
        }
    }
    while (i <= mid) {  // 此时有一个段归并完了，剩下的部分直接接到后面即可，一定都比现在的大
        temp[k ++] = nums[i ++];
    }
    while (j <= r) {
        temp[k ++] = nums[j ++];
    }
    for (i = l, j = 0; i <= r; ++ i, ++ j) {    // 将缓存存回
        nums[i] = temp[j];
    }
}

template <class T>
void MergeSort(std::vector<T>& nums) {
    n = nums.size();
    merge_sort(nums, 0, n - 1);
}