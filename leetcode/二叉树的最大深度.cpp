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

// 思路： 深度优先搜索，时间On，空间Oh，递归用到了栈空间
// 1. 遍历左右孩子，每次给定当前深度用于判断

class Solution {
public:
    int res = 0;
    
    void dfs(TreeNode* r, int h) {
        if(r == NULL) return;   //如果当前节点为空，不管
        res = max(res, h);      //否则更新深度
        if(r->left) dfs(r->left, h + 1);    //如果左右孩子不为空，则遍历左右孩子
        if(r->right) dfs(r->right, h + 1);
    }

    int maxDepth(TreeNode* root) {
        dfs(root, 1);
        return res;
    }
};