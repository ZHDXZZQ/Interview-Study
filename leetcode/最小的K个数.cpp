/*
    思路： 堆排，时间Onlogk，空间On
*/

#include <functional>
#include <queue>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param input int整型vector 
     * @param k int整型 
     * @return int整型vector
     */

    // 可以暴力sort、快排、堆排、桶排，只有堆排符合要求

    vector<int> GetLeastNumbers_Solution(vector<int>& input, int k) {
        // write code here
        if (k == 0 || k > input.size()) {
            return {};
        }
        priority_queue<int, vector<int>> heap;  // 默认less大根堆
        for (auto& num : input) {
            if (heap.size() < k) {  // 当数量小于k时，依次入堆
                heap.push(num);
            } else {
                if (heap.top() > num) { // 判断是否该num更小，如果更小，入堆，堆中存储的是当前遍历到的最小的k个数
                    heap.pop();
                    heap.push(num);
                }
            }
        }
        vector<int> res;
        while (!heap.empty()) { // 出堆放入结果
            res.emplace_back(heap.top());
            heap.pop();
        }
        sort(res.begin(), res.end());   // 排序Oklogk
        return res;
    }
};