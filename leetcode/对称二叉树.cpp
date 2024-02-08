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

// 思路： dfs递归，时间On，空间On，递归栈空间
// 1. 如果当前相比较的两个节点相同则为true，否则返回false
// 2. 递归的遍历当前两个节点的左孩子和右孩子，右孩子和左孩子，保证是镜像的遍历

class Solution {
public:
    bool is_sym(TreeNode* p, TreeNode* q) {
        if(p == NULL && q == NULL) return true;
        else if(p == NULL || q == NULL) return false;
        if(p->val != q->val) return false;
        return is_sym(p->left, q->right) && is_sym(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
        return is_sym(root, root);
    }
};