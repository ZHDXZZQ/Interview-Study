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
    思路： 中序遍历，时间On，空间Ologn
    1. 反向中序遍历，右中左，因为是二叉搜索树，因此对中间值处理的时候，是从最大值的节点开始的
    2. 里用一个变量记录遍历过的值的和，即为大于等于当前节点的值的节点的值的和
    3. 直接利用和更新当前节点即可
*/

class Solution {
public:
    int sum = 0;

    void reverse_mid_order(TreeNode* t) {
        if (t == nullptr) {
            return ;
        }
        reverse_mid_order(t->right);    // 反向中序遍历
        sum += t->val;      // 记录当前遍历过得值的和，从后往前，因此和即为更新后当前节点应该的值
        t->val = sum;
        reverse_mid_order(t->left);
    }

    TreeNode* convertBST(TreeNode* root) {
        reverse_mid_order(root);
        return root;
    }
};