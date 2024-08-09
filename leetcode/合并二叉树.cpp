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
    思路： 模拟，时间On，空间Ologn，递归栈空间
    1. 递归遍历两个树的相同节点
    2. 如果不为空，则相加为新节点
    3. 如果有一个为空，则利用不为空的节点直接作为其当前节点，下面的节点也就无需遍历了
*/

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (root1 && root2) {   // 都不为空
            auto root = new TreeNode(); // 构建新节点，值为两个对应节点之和
            root->val = root1->val + root2->val;
            root->left = mergeTrees(root1->left, root2->left);  // 递归遍历其左右孩子节点
            root->right = mergeTrees(root1->right, root2->right);
            return root;
        } else if (root1 && !root2) {   // 其中一个为空，拿另一个不为空的作为当前节点
            return root1;
        } else if (!root1 && root2) {
            return root2;
        }
        return nullptr; // 都为空，返回nullptr
    }
};