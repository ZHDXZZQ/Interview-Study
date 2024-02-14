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

// 思路： 整体移动左子树，时间On，空间O1
// 1. 遍历所有右子树上的右孩子节点，如果该节点有左子树，则把左子树整体移动到当前节点的右子树
// 2. 将当前节点原本的右孩子接到其左子树上最右边的右孩子叶子节点的右孩子上
// 3. 这样所有节点最多遍历两边，且不用特殊操作

class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode* dummy = new TreeNode(-1, nullptr, root);
        while(dummy->right) {       //如果当前节点的右孩子还存在，则遍历
            dummy = dummy->right;   //dummy指向当前节点的右孩子节点，作为当前节点
            auto left_tree = dummy->left;   //找到当前节点的左子树
            if(left_tree == NULL) continue; //如果当前节点没有左子树，则跳过
            while(left_tree->right) {   //否则，找到当前节点的左子树的最右孩子叶子节点
                left_tree = left_tree->right;
            }
            left_tree->right = dummy->right;    //将当前节点的左子树的右链全部接到当前节点的右子树中，然后继续遍历其右孩子即可
            dummy->right = dummy->left;
            dummy->left = nullptr;
        }
    }
};