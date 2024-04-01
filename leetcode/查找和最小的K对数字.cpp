// 思路： 优先队列，时间Oklogk，空间Ok
// 1. 构造一个三元组，下标0存储和，下标1存储数组1的对应下标，下标2存储数组2的对应下标
// 2. 用这个三元组作为基础类型构造堆，按下标0的大小升序排序构造小根堆
// 3. 因为两个数组都是升序排序，因此先按照数组1的最小值和数组2的每一个都结合插入堆中
// 4. 然后取出堆顶，向堆中插入堆顶数组1的下一个值和堆顶数组2的当前值，原因是升序排列，下一个更大的值一定是其中一个值变大，而另一个值不变，这里数组2的下一个值也会在之后的情况中插入
// 5. 重复第四步直到找出k队

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
        //优先队列，已vector的0号元素进行升序排序，小根堆
        for (int i = 0; i < n; ++ i) {  //将数组1的头一个数字和数组2的每个数字组合插入
            q.push({nums1[0] + nums2[i], 0, i});
        }
        vector<vector<int>> res;
        while (k -- && q.size()) {
            auto heap_top = q.top();    //每次取出堆顶
            q.pop();
            res.push_back({nums1[heap_top[1]], nums2[heap_top[2]]});    //插入结果
            if (heap_top[1] + 1 < m) {  //将下一组和更大的组合插入，只改变数组1的下标就行了，这里就不证明了，模拟一下就想明白了
                q.push({nums1[heap_top[1] + 1] + nums2[heap_top[2]], heap_top[1] + 1, heap_top[2]});
            }
        }
        return res;
    }
};