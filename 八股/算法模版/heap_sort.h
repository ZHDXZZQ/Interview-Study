/*
    堆排序：大根堆或小根堆，堆顶即为当前所有数的最大值或最小值，树形结构，每三个节点（父子）都满足堆的规律，即父节点为三者的最大值或最小值
    每插入一个值则放到树的最后一层往后接入，然后根据这个节点从下往上调整堆满足堆的规律，每次插入时间Ologn
    每次获取当前堆顶后，把最后一个节点（最后一层的最右节点）移动到堆顶，再从上往下依次调整堆以符合堆的规律，时间Ologn
    堆排序的时间复杂度为Onlogn，空间On，优先队列即为堆，不稳定，堆顶即为当前最值，排序不考虑插入。
    这里实现一个小根堆，用一维数组维护堆的完全二叉树
    heap表示数组，size表示堆中元素数量
    down方法是把当前节点的元素和孩子比较，即向下调整，调整三个节点的值
    up方法是向上调整，每次只需要比较和父亲的大小并是否交换即可
*/

#include <algorithm>
#include <vector>

template <typename T>
class MinHeap {
public:
    MinHeap(std::vector<T>& nums) : nums(nums), heap(nums), size(nums.size()) {
        for (int i = size / 2; i >= 0; --i) {   // 从倒数第二层最右节点开始，三个三个一组从下往上交换，直到每个三元组都是父节点最小
            down(i);
        }
    }

    void insert(int x) {   // 插入一个数字
        ++ size;
        heap.push_back(x);
        nums.emplace_back(x);
        up(size - 1);   // 调整堆
    }

    void sort() {
        int originalSize = size;
        for (int i = 0; i < originalSize; ++i) {
            nums[i] = heap[0];  // 取出堆顶
            std::swap(heap[0], heap[size - 1]);   // 将堆尾移动至堆顶
            -- size;    // 取出一个元素，数量-1
            down(0);    // 从上往下调整堆，堆顶仍然为最小元素
        }

        size = originalSize;    // 恢复大小，以便后续插入时用
        for (int i = size / 2; i >= 0; --i) {   // 还原堆
            down(i);
        }
    }

private:
    void down(int u) {  // 父节点为u
        int t = u;  // 利用t找到三个节点中最小的，和父节点u交换
        if (u * 2 < size && heap[u * 2] < heap[t]) {    // u * 2为左孩子
            t = u * 2;  // 父节点应该为更小的
        }
        if (u * 2 + 1 < size && heap[u * 2 + 1] < heap[t]) {    // u * 2 + 1为右孩子
            t = u * 2 + 1;  // 父节点应该为更小的
        }
        if (u != t) {
            std::swap(heap[u], heap[t]);    // 父节点和某个子节点交换
            down(t);    // 若发生交换，要递归向下处理，直到堆底
        }
    }

    void up(int u) {    // 插入时调用自下而上调整堆
        while (u / 2 >= 0 && heap[u / 2] > heap[u]) {   // u / 2为下取整，是父节点
            std::swap(heap[u / 2], heap[u]);    // 如果父节点的值大于当前节点，则交换，直到这一条路交换到头节点或无需变动为止
            u /= 2;
        }
    }

private:
    std::vector<T>& nums;
    std::vector<T> heap;
    int size;
};

template <class T>
void HeapSort(std::vector<T>& nums) {
    MinHeap<T> min_heap(nums);
    min_heap.sort();
    min_heap.insert(0);
    min_heap.sort();
    return;
}