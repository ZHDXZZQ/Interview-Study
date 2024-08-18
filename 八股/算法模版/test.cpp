#include <iostream>
#include <vector>
#include "bubble_sort.h"
#include "quick_sort.h"
#include "select_sort.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "bucket_sort.h"
#include "insert_sort.h"
#include "binary_insert_sort.h"
#include "counting_sort.h"
#include "base_sort.h"

const int a[] = {2, 4, 8, 1, 7, 3, 4, 2, 9, 5, 10, 14, 25, 930, 63, 184, 505, 278, 589, 109};
// const int a[5] = {2, 4, 8, 1, 7};


int main() {
    std::vector<int> nums;
    for (int i = 0; i < sizeof(a) / 4; ++ i) {
        nums.push_back(a[i]);
    }
    // BubbleSort(nums);
    // QuickSort(nums);
    // SelectSort(nums);
    // MergeSort(nums);
    // HeapSort(nums);
    // BucketSort(nums);
    // InsertSort(nums);
    // BinaryInsertSort(nums);
    // CountingSort(nums);
    BaseSort(nums);
    for (auto& num : nums) {
        std::cout << num << " , ";
    }
    return 0;
}