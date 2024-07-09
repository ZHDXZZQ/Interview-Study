/*
    思路： bfs，时间On，空间On
    1. 从0开始，往外按圈寻找每个节点，如果该节点是向0走的，则这条路不用管，继续往后找
    2. 如果该节点是向外走的，则改变一下，再往后找
    3. 因为只有n-1条边，一定不成环，因此无需考虑是否有更短路径而导致不改变这条路
*/

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<int>> a2b;    // 存储从k到v的路径
        unordered_map<int, vector<int>> b2a;    // 存储从v到k的路径
        for (auto& load : connections) {
            a2b[load[0]].push_back(load[1]);
            b2a[load[1]].push_back(load[0]);
        }
        vector<bool> is_gone(n, false); // 记忆哪个点是否走过
        int res = 0;
        queue<int> q;
        q.push(0);
        while (q.size()) {
            auto pos = q.front();   // 取出当前的节点
            q.pop();
            is_gone[pos] = true;    // 记录已走过
            for (auto& next : a2b[pos]) {   // 遍历从这个点出发所能到达的所有点
                if (is_gone[next] == false) {   // 如果遍历到的点已走过，则不管
                    q.push(next);   // 否则将这个点插入，这将是一个需要更改的边
                    ++ res;
                }
            }
            for (auto& next : b2a[pos]) {
                if (!is_gone[next]) {   // 遍历到达这个点的边，如果没有走过，也加入队列
                    q.push(next);   // 由于这条路是向0走的，因此无需更改这条边
                }
            }
        }
        return res;
    }
};