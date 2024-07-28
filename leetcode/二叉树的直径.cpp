/*
    思路： dfs，时间On，空间Ologn
    1. 对于每个节点，计算其左孩子的深度和右孩子的深度
    2. 更新两边最大深度的路径数之和和res取更大值
    3. 向上返回该节点的最大深度，即左孩子的深度和右孩子的深度+本节点1
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
    int res = 0;
    int get_h(TreeNode* t) {
        if (!t) {   // 如果为空，返回0
            return 0;
        }
        int l = get_h(t->left), r = get_h(t->right);    // 获取左右孩子的深度
        res = max(res, l + r);  // 更新结果为最长路径
        return max(l, r) + 1;   // 向上返回两节点的最大深度+1，为以本节点为根的树的最大深度
    }
    int diameterOfBinaryTree(TreeNode* root) {
        get_h(root);
        return res;
    }
};