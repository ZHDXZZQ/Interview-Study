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

// 思路： 深度优先搜索，时间Omin（n，m），空间Omin（m，n），递归需要栈空间
// 1. 模拟判断，如果两个都是空表明没问题
// 2. 如果只有一个为空则返回错误
// 3. 否则的话比较两个的值是否相同，如果不同则返回错误
// 4. 否则递归判断左右子节点

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL && q == NULL) return true;
        else if(p == NULL || q == NULL) return false;
        if(p->val != q->val) return false;
        bool res = isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        return res;
    }
};