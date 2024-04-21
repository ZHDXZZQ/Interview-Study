// 思路： dfs回溯， 时间On*2^n，空间On
// 1. dfs，模拟栈记录当前路径，到达终点后退栈回溯

class Solution {
public:
    vector<vector<int>> res;
    vector<int> last_node;  //记录当前路径
    int n;

    void dfs(vector<vector<int>>& graph) {
        int num = last_node.back();
        if (num == n - 1) {             //如果当前路径的最后一个节点是终点，则找到一条路径
            res.push_back(last_node);
            return;
        }
        for (auto& next : graph[num]) { //否则的话遍历当前节点的最后一个节点
            last_node.push_back(next);  //将所有的next依次进行dfs回溯
            dfs(graph);
            last_node.pop_back();
        }
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        n = graph.size();
        last_node.push_back(0); //插入起点
        dfs(graph);
        return res;
    }
};