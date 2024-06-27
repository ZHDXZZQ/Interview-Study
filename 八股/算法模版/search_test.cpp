#include <iostream>
#include <vector>
#include "binary_search.h"

const int a[10] = {1, 2, 2, 4, 5, 7, 8, 9, 13, 13};

int main() {
    std::vector<int> nums;
    for (int i = 0; i < sizeof(a) / 4; ++ i) {
        nums.push_back(a[i]);
    }
    BinarySearch(nums, 4);
    BinarySearch(nums, 1);
    BinarySearch(nums, 13);
    BinarySearch(nums, 0);
    BinarySearch(nums, 19);
    return 0;
}