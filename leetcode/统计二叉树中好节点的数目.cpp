/*
    思路： 遍历，时间On，空间O1
    1. 每次向下遍历时，存储到当前路径上的最大值，判断每个节点是否是好节点
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
    int res = 1;    // 根节点默认为好节点

    void is_good(TreeNode* t, int max_val) {
        if (t == nullptr) {
            return;
        }
        int& v = t->val;
        if (v >= max_val) { // 如果当前节点的值大于等于前面路径上的全部值得最大值，则是一个好节点
            ++ res;
        }
        max_val = max(max_val, v);  // 更新最大值
        is_good(t->left, max_val);  // 遍历每个孩子
        is_good(t->right, max_val);
    }

    int goodNodes(TreeNode* root) {
        if (!root) {
            return res;
        }
        is_good(root->left, root->val);
        is_good(root->right, root->val);
        return res;
    }
};