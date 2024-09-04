/*
    思路： 树形dp，时间On，空间On。其实也是记忆化搜素dfs，类似打家劫舍
    1. 先制作一个树
    2. 找到根节点
    3. 对于每个树，他会有两种情况
    4. 第一种，选择根节点，则每个子节点都不能选，加和每个子树的最大值
    5. 第二种，不选择根节点，则每个子节点可以自由选择，加和每个子树的两种情况的最大值
    6. 返回最大值
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    vector<int> sons;  
};

int n;
unordered_map<int, TreeNode*> umap; // 记录每个节点编号对应的节点
vector<bool> has_father;    // 记录某个节点是否有父亲，用于筛选根节点

// 动态规划记忆表
unordered_map<TreeNode*, int> dp_true;  // 记录该子树中使用当前为根节点的最大值
unordered_map<TreeNode*, int> dp_false; // 记录该子树中不使用当前为根节点的最大值

// 记忆化搜索函数
int dance(TreeNode* t, bool use_t) {   // t为计算当前子树的根节点，计算最大价值，use_t代表是否使用该节点
    if (use_t) {    // 如果要使用根节点
        // 如果已经计算过，直接返回结果
        if (dp_true.find(t) != dp_true.end()) {
            return dp_true[t];
        }
        int res = t->val; // 使用当前节点时，先加上当前节点的值
        for (auto& son_node : t->sons) {
            auto real_son_node = umap[son_node];
            // 子节点在不使用的情况下计算
            res += dance(real_son_node, false);
        }
        dp_true[t] = res; // 记录计算结果
        return res;
    }

    // 不使用根节点
    if (dp_false.find(t) != dp_false.end()) {   // 如果已经计算过，直接返回
        return dp_false[t];
    }
    int res = 0; // 不使用当前节点
    for (auto& son_node : t->sons) {
        auto real_son_node = umap[son_node];
        // 选择使用或不使用子节点为根节点的子树的最佳值
        res += max(dance(real_son_node, false), dance(real_son_node, true));
    }
    dp_false[t] = res; // 记录计算结果
    return res;
}

int main() {
    cin >> n;
    has_father = vector<bool>(n + 1, false);

    // 创建每个节点并读入节点值
    for (int i = 1; i <= n; ++i) {
        TreeNode* node = new TreeNode(); // 创建新节点并初始化 val
        cin >> node->val;
        umap[i] = node; // 构建索引
    }

    // 构建树的父子关系
    for (int i = 0; i < n - 1; ++i) {
        int father, son;
        cin >> son >> father;
        has_father[son] = true; // 记录父子节点关系
        umap[father]->sons.push_back(son);
    }

    // 找到根节点
    TreeNode* root = nullptr;
    for (int i = 1; i <= n; ++i) {
        if (!has_father[i]) {
            root = umap[i]; // 找到根节点
            break;
        }
    }

    // 计算结果，取使用根节点和不使用根节点的最大值
    int res = max(dance(root, true), dance(root, false));
    cout << res << endl;

    // 清理内存
    for (auto& [key, node] : umap) {
        delete node;
    }

    return 0;
}
