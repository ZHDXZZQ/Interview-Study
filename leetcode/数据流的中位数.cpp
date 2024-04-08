// 思路： 对顶堆维护，时间Ologn，即堆排序时间，空间On
// 1. 对题中的所有数进行排序，将其轴对称的划分为两部分，左边建大顶堆，右边建小顶堆，因为左边只需要最大值，右边只需要最小值，即中间的数
// 2. 每次做好两边堆的平衡，保证左边比右边数量相同或只多一个

class MedianFinder {
public:
    MedianFinder() {}
    
    void addNum(int num) {  //我们让左边的堆可以多一个元素
        if (left_heap.empty() || num < left_heap.top()) {   //如果左边为空，或者值更小
            left_heap.push(num);    //插到左边
            if (left_heap.size() > right_heap.size() + 1) { //如果左边比右边多了超过1个
                right_heap.push(left_heap.top());   //则把左边的堆顶移到右边
                left_heap.pop();
            }
        } else {    //如果值大于左边堆顶
            right_heap.push(num);   //插到右边
            if (right_heap.size() > left_heap.size()) { //如果右边多了
                left_heap.push(right_heap.top());   //把右边的堆顶插到移到左边
                right_heap.pop();
            }
        }
    }
    
    double findMedian() {
        auto size = right_heap.size() + left_heap.size();   //统计两边总数
        if (size % 2 == 0) {    //如果是偶数，则各取堆顶除以2
            return (right_heap.top() + left_heap.top()) / 2.0;
        }
        return left_heap.top(); //如果是奇数，直接取左边堆顶即为众位数
    }
private:
    priority_queue<int, vector<int>, greater<int>> right_heap;  //右边的小顶堆
    priority_queue<int> left_heap;  //大顶堆，可以缺省
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */