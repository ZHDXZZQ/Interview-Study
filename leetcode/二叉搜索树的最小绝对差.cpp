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

// 思路： 中序遍历，时间On，空间O1
// 1.因为是二叉搜索树，所以中序遍历的结果一定是有序的
// 2. 题目求任意两节点的最小差，那么一定是相邻两节点的差值是最小的
// 3. 所以每次比较中序遍历相邻两节点的差值并更新答案即可
// 4. 但是题目只需要当前节点的值和中序遍历中前一个节点的值作比较
// 5. 因此只需要有一个值来记录中序遍历中前一个节点的值即可，空间O1

class Solution {
public:
    int last_num = -1;      //记录中序遍历中前一个节点的值，这里用-1是因为题目给出的节点中的值都非负
    // 如果节点的值为全部的范围，则需要加一个标志记录是否为第一个数
    int res = INT_MAX;

    void inorder(TreeNode* t) {
        if(!t) return;
        inorder(t->left);   //中序遍历，左根右
        if(last_num != -1) {    //如果当前节点不是第一个节点
            res = min(res, t->val - last_num);  //计算当前节点和前一个节点的差，更新答案
        }
        last_num = t->val;      //将当前节点作为下一个节点的前一个节点
        inorder(t->right);
    }

    int getMinimumDifference(TreeNode* root) {
        inorder(root);
        return res;
    }
};