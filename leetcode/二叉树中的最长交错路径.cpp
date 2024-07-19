/*
    思路： dfs，时间O2n，空间On，递归站空间
    1. 对于每个节点，遍历左右孩子，记录节点数并求最大值
    2. 通过一个标志记录此时是向左还是向右，如果下次遍历的开始和之前方向一样，数量从0开始
*/

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
class Solution {
public:
    int res = 0;
    void go(TreeNode* t, int cnt, bool turn_left) {
        if (!t) {
            return;
        }
        ++ cnt;
        res = max(res, cnt);    // 记录当前路径中的节点数
        if (turn_left) {    // 如果刚才是向左
            go(t->right, cnt, false);   // 那么此时向右可以继续遍历
            go(t->left, 0, true);   // 也可以从这个结点开始接着向左遍历，只不过是从0开始
        } else {    // 向右的同理
            go(t->left, cnt, true);
            go(t->right, 0, false);
        }
    }
    int longestZigZag(TreeNode* root) {
        go(root->left, 0, true);    // 向左遍历
        go(root->right, 0, false);  // 向右遍历
        return res;
    }
};