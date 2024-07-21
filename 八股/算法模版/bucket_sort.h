/*
    桶排序：一种基于分布的排序算法，适用于数据均匀分布在一定范围的情况。
    它的基本思想是将数据分配到多个桶中，每个桶分别进行排序，然后合并桶中的数据。
    每个桶装一个范围的元素，桶内排好（桶内可以是任意排序方式）再放出来，稳定与否取决于桶内排序方法。
    最好时间On，平均On，最差时间On²（全在一个桶里），空间On。
*/

#include <algorithm>
#include <vector>

// 桶大小可以自定义，也可以直接一个数据一个桶，一个数据一个桶的话需要计算最大值和最小值来确定桶空间，空间需要更大

template <class T>
void BucketSort(std::vector<T>& nums) {
    int n = nums.size();
    std::vector<std::vector<T>> buckets(BUCKET_COUNT);

}