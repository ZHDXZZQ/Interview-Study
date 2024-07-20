/*
    思路： 小根堆，时间O（n+k）logn，空间On
*/

class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int n = costs.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;   // 维护一个小根堆，存入价值和位置
        int left = candidates - 1, right = n - candidates;  // 记录左半部分和右半部分
        if (left + 1 < right) { // 如果左右部分加起来不是全部，则分别插入
            for (int i = 0; i <= left; ++i) {   // 左半部分插入
                heap.emplace(costs[i], i);
            }
            for (int i = right; i < n; ++i) {   // 右半部分插入
                heap.emplace(costs[i], i);
            }
        } else {    // 如果两边的候选加起来超过了所有工人数量
            for (int i = 0; i < n; ++i) {   // 全部插入
                heap.emplace(costs[i], i);
            }
        }
        long long ans = 0;
        while (k --) {
            auto [cost, id] = heap.top();   // 拿出堆顶的工人，他的花销和位置一定都是最小的
            heap.pop();
            ans += cost;
            if (left + 1 < right) { // 如果此时左右部分还没有包含全部
                if (id <= left) {   // 如果位于左半部分，则把左半部分的下一个人插入
                    ++ left;
                    heap.emplace(costs[left], left);
                } else {    // 否则把右半部分的下一个人插入
                    --right;
                    heap.emplace(costs[right], right);
                }
            }   // 如果已经包含全部，就出人就行了
        }
        return ans;
    }
};
