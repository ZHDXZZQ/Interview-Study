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
    思路： dfs，时间On，空间Ologn
    1. 对于任一三个节点的二叉树，仅有两种情况，即不抢劫根节点，而抢劫两个子节点
    2. 第二种情况即为，不抢劫两个子节点，抢劫根节点
    3. 因此每个二叉树用两个结果存储当前情况，第一个结果为不抢劫根节点，而抢劫两个子节点中的任意最大抢劫方法（有可能包含子节点，也可能不包含子节点而选中了子树中的其他节点）
    4. 第二个结果即为抢劫两颗子树但不选择两个子节点的情况+抢劫根节点的价值
*/

class Solution {
public:
    vector<int> dfs(TreeNode* t) {
        if (t == nullptr) { // 如果该节点为空，无价值
            return {0, 0};
        }
        auto lres = dfs(t->left);   // 否则计算抢劫两颗子树的价值，第一个结果不抢劫子节点，第二个结果一定抢劫子节点
        auto rres = dfs(t->right);
        return {max(lres[0], lres[1]) + max(rres[0], rres[1]), lres[0] + rres[0] + t->val};
        // 第一个结果为不抢劫该节点，选择抢劫两个子树的最大价值，可能包含其子节点，对于上层来说是孙子节点
        // 第二个结果为一定抢劫该节点，以及抢劫两个子树的不包含子节点的价值
    }

    int rob(TreeNode* root) {
        auto res = dfs(root);
        return max(res[0], res[1]); // 取抢劫方法的最大价值
    }
};