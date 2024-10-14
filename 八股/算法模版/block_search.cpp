/*
    分块查找算法（Block Search），也叫分段查找，是一种基于分块思想的查找算法。
    其基本思想是：先将数据划分为若干块，并为每块设定一个索引，然后通过索引确定需要查找的块，最后在块内执行顺序查找。
*/
#include <iostream>
#include <vector>
#include <cmath>  // for sqrt

// 顺序查找块内数据
int linearSearchInBlock(const std::vector<int>& block, int key) {
    for (size_t i = 0; i < block.size(); ++i) {
        if (block[i] == key) {
            return i;  // 返回块内索引
        }
    }
    return -1;  // 未找到
}

// 分块查找算法
int blockSearch(const std::vector<int>& data, int key) {
    int n = data.size();
    int blockSize = std::sqrt(n);  // 设定块大小为 √n
    
    // 构建索引数组（每块的最大值）
    std::vector<int> index;
    for (int i = 0; i < n; i += blockSize) {
        index.push_back(data[std::min(i + blockSize - 1, n - 1)]);  // 每块最后一个元素
    }
    
    // 找到合适的块
    int blockNum = -1;
    for (size_t i = 0; i < index.size(); ++ i) {
        if (key <= index[i]) {
            blockNum = i;  // 找到目标块
            break;
        }
    }
    
    if (blockNum == -1) {
        return -1;  // 不在索引范围内，未找到
    }
    
    // 确定块的起始和结束位置
    int blockStart = blockNum * blockSize;
    int blockEnd = std::min(blockStart + blockSize, n);
    
    // 在块内顺序查找
    for (int i = blockStart; i < blockEnd; ++ i) {
        if (data[i] == key) {
            return i;  // 返回数组中的位置
        }
    }
    
    return -1;  // 未找到
}

int main() {
    // 示例数据，假设已排序
    std::vector<int> data = {1, 3, 7, 9, 12, 18, 25, 30, 36, 40, 45, 50};
    
    int key = 18;
    
    int index = blockSearch(data, key);
    
    if (index != -1) {
        std::cout << "元素 " << key << " 找到在位置: " << index << std::endl;
    } else {
        std::cout << "元素 " << key << " 未找到！" << std::endl;
    }
    
    return 0;
}
