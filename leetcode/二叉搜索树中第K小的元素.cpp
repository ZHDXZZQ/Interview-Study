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

// 思路： 计数中序遍历，时间Ok，空间On栈空间（链状树的情况下为On，否则Ologn）
// 1. 因为是二叉搜索树，且只要找增序的第k个元素，所以中序遍历找第k个元素即可，找一个值来记录当前是第几个元素
// 2. 当碰到第k个元素的时候，返回即可

class Solution {
public:
    int pos = 0;    //记录当前元素的位置
    int res = 0;

    void inoreder(TreeNode* t) {
        if(t == NULL) return;
        inoreder(t->left);  //中序遍历
        if(-- pos == 0) {   //如果当前元素的中序遍历的位置是第k个，则返回
            res = t->val;
            return;
        }
        inoreder(t->right);
    }

    int kthSmallest(TreeNode* root, int k) {
        pos = k;            //更新k到全局变量
        inoreder(root);
        return res;
    }
};