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

/*
    思路： 二叉搜索树按大小搜索，时间Ologn，空间Ologn，最坏情况下一条链即为On
    1. 利用二叉搜索树的特性，和当前节点进行判断，如果小于，则搜索左边
    2. 否则搜索右边
    3. 搜到则返回该节点，无需继续向下搜索
*/

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
         if (!root) {
            return nullptr; // 根节点为空，返回nullptr
        }
        if (root->val == val) {
            return root; // 找到目标值，返回节点
        }
        if (val < root->val) {
            return searchBST(root->left, val); // 目标值小于当前节点值，搜索左子树
        } else {
            return searchBST(root->right, val); // 目标值大于当前节点值，搜索右子树
        }
        return nullptr;
    }
};