/*
    思路： 遍历树，时间On，空间On，n为全部节点数
    1. 按顺序遍历每个节点，判断是否是叶节点
    2. 任意遍历方法皆可，只要保证叶子输出的顺序是左往右即可
    3. 对于叶子节点进行记录，二者判断
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void dfs(TreeNode* t, vector<int>& res) {    
        // 先序遍历dfs Ologn但由于需要记录，所以也是On，也可以用广搜空间On
        if (!t) { return; }
        if (t->left == nullptr && t->right == nullptr) {    // 如果是叶子节点
            res.push_back(t->val);
        }
        dfs(t->left, res);  // 遍历左右子节点
        dfs(t->right, res);
    }
    
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> leaf1;  // 可以拿string存储
        dfs(root1, leaf1);
        vector<int> leaf2;
        dfs(root2, leaf2);
        if (leaf1 == leaf2) {   // 判断是否相等
            return true;
        }
        return false;
    }
};