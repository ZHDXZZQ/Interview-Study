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

// 思路： 深度优先递归，时间On，空间On，一般情况下Ologn的空间，如果树为链状则为On
// 1. 首先判断当前节点是否为空，如果为空则不进行任何操作
// 2. 否则交换当前节点的左右孩子
// 3. 然后再对其左右孩子进行同样的上述操作，此时左右孩子已经换位
// 4. 最后，返回root节点即可

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == NULL) return NULL;
        auto tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};