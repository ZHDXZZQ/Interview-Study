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

// 思路： 递归深搜，时间On，空间Ologn，链状树 空间On
// 1. 从根节点到叶节点计算每条链路的和，判断是否满足题意

class Solution {
public:
    bool calc_sum(TreeNode* r, int& targetSum, int cur_sum) {
        if(r == NULL) return false;     //如果当前节点为空，则这条路不行，因为能走到这来表明这条路前面也没有符合目标的和
        int sum = cur_sum + r->val;     //否则的话将该节点的值加到链路中去
        if(sum == targetSum && !r->left && !r->right) return true;      //如果符合目标值，且为叶节点，则返回可以
        return calc_sum(r->left, targetSum, sum) || calc_sum(r->right, targetSum, sum); //递归，只要有一条路满足则符合题意
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        return calc_sum(root, targetSum, 0);
    }
};