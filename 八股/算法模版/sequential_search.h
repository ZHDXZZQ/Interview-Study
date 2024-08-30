/*
    顺序查找： 适用于线性表，按照顺序查找，返回所有匹配数字的下标
    时间On，空间O1
*/

#include <vector>

// const int a[10] = {1, 2, 2, 4, 5, 7, 8, 9, 13, 13};

template <class T>
void SeqSearch(std::vector<T>& nums, T target) {
    int n = nums.size();
    bool flag = false;
    for (int i = 0; i < n; ++ i) {
        if (nums[i] == target) {
            std::cout << i << " ";
            flag = true;
        }
    }
    if (flag == false) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << std::endl;
    }
    return;
}