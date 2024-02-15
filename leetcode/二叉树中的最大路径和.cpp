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
 
// 思路： 递归，时间On，空间On栈空间
// 1. 问题分解成多个子问题，对于任意其中一个二叉树，他只存在两种情况需要考虑
// 2. 第一种情况，就是左子树+根+右子树作为局部子树去更新最大和，例如官方例子2中的局部子树
// 3. 第二种情况就是要将当前树作为父节点的子树传回父节点，由父节点将其当作某个子树参与运算，此时不可能返回左根右
// 4. 因为是路径和，所以一定是返回根节点 + 左子树或者右子树 的最大路径和
// 5. 依次递归到根节点，每个子树判断是否能更新答案，并且在返回上一层是判断如果当前最大路径和为负数，则返回0代表丢弃以免产生负向影响

class Solution {
public:
    int res = INT_MIN;

    int calc(TreeNode* p) {
        if(p == NULL) return 0;     //如果当前节点为空，则直接返回0
        int left_max = max(calc(p->left), 0);   //否则计算其左子树的路径和，如果为负则算0，表示放弃其左子树
        int right_max = max(calc(p->right), 0); //计算右子树的路径和，同上
        int cur_max = left_max + right_max + p->val;    //以当前节点为根，计算局部子树最大路径和，由左右根三部分组成
        res = max(res, cur_max);        //更新答案为最大值
        return p->val + max(left_max, right_max);   //返回当前节点为根的最大路径和给父节点，左右子树只能选择一边，为负则返回0代表这棵子树为副作用，不选
    }

    int maxPathSum(TreeNode* root) {
        calc(root);
        return res;
    }
};