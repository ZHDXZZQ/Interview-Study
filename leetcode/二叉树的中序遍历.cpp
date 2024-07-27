/*
    思路： 递归，时间On，空间Ologn，最坏On。递归需要栈维护也是On
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
    vector<int> res;
    void mid_order(TreeNode* t) {
        if (!t) {
            return;
        }
        mid_order(t->left); // 左中右
        res.emplace_back(t->val);
        mid_order(t->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        mid_order(root);
        return res;
    }
};