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

// 思路： 分治，时间On，空间Ologn
// 1. 每次将中位数作为新节点创建，然后左右区间分别找中位数作为左右孩子
// 2. 重复递归，直到全部插入

class Solution {
public:
    TreeNode* insert(vector<int>& nums, int l, int r) {
        if(l > r) return nullptr;       //如果当前区间的左边界超过右边界了，则当前区间已经没有可插入的点
        int pos = (l + r) / 2;          //找到当前区间的中位数
        auto cur_node = new TreeNode(nums[pos]);
        cur_node->left = insert(nums, l, pos - 1);      //再将区间内的中间节点的左右两边作为两个区间递归
        cur_node->right = insert(nums, pos + 1, r);
        return cur_node;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n = nums.size();
        int pos =  (n - 1) / 2;     //找所有数的中位数作为根节点
        TreeNode* root = new TreeNode(nums[pos]);
        root->left = insert(nums, 0, pos - 1);  //根节点的左右孩子就是左右两个区间的中位数
        root->right = insert(nums, pos + 1, n - 1);
        return root;
    }
};
