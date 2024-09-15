#include <iostream>
#include <vector>
#include <chrono>
#include "binary_search.h"
#include "sequential_search.h"
#include "hash_search.h"
#include "bst_search.h"

const int a[10] = {1, 2, 2, 4, 5, 7, 8, 9, 13, 13};

int main() {
    std::vector<int> nums;
    for (int i = 0; i < sizeof(a) / 4; ++ i) {
        nums.push_back(a[i]);
    }
    auto start = std::chrono::high_resolution_clock::now();
    // BinarySearch(nums, 4);
    // BinarySearch(nums, 1);
    // BinarySearch(nums, 13);
    // BinarySearch(nums, 0);
    // BinarySearch(nums, 19);

    // SeqSearch(nums, 9);
    // SeqSearch(nums, 3);
    // SeqSearch(nums, 13);

    // HashSearch(nums, 9);

    BstSearch(nums, 9);

    // for (volatile int i = 0; i < 100000000; ++i);
    auto end = std::chrono::high_resolution_clock::now();

    // 计算时间差并输出（单位：毫秒）
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "cost: " << duration << " ms" << std::endl;
    return 0;
}