/*
    二分查找：前提被查找的对象序列有序，每次查找区间的中间，判断目标在左还是在右
    时间Ologn，空间O1。
    注意如果查找的每次更新的区间可能出现l=mid的话，mid需要等于l + r + 1 >> 1，否则为l+r
*/

#include <vector>

// const int a[10] = {1, 2, 2, 4, 5, 7, 8, 9, 13, 13};

template <class T>
void BinarySearch(std::vector<T>& nums, T target) {
    int n = nums.size();
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = l + r >> 1;   // 这里尤其注意，避免死循环
        if (nums[mid] >= target) {
            r = mid;
        } else {
            l = mid + 1;    // 建议采用这个方式
        }
    }
    if (nums[r] == target) {    // 这里一般选择r即可，拉几组数据判断
        std::cout << r << std::endl;
        return;
    }
    std::cout << " -1 " << std::endl;
    return;
}