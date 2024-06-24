#include <iostream>
#include <vector>
#include "bubble_sort.h"
#include "quick_sort.h"
#include "select_sort.h"

const int a[10] = {2, 4, 8, 1, 7, 3, 4, 2, 9, 5};
// const int a[5] = {2, 4, 8, 1, 7};


int main() {
    std::vector<int> nums;
    for (int i = 0; i < sizeof(a) / 4; ++ i) {
        nums.push_back(a[i]);
    }
    // BubbleSort(nums);
    // QuickSort(nums);
    SelectSort(nums);
    for (auto& num : nums) {
        std::cout << num << " , ";
    }
    return 0;
}