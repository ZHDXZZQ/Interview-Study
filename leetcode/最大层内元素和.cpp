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
    思路： bfs二叉树的层次遍历，时间On，空间On
*/

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q; // 存储每层的节点
        q.push(root);   // 初始化根节点插入
        int max = INT_MIN;  // 记录当前最大值
        int res;    // 最大层和的最小层数
        int count = 0;  // 记录层数
        while (q.size()) {  // 如果队列中还有节点，说明还有下一层
            int cnt = q.size(); // 记录当前层的节点数量
            ++ count;   //层数+1
            int sum = 0;    // 计算当前层和
            while (cnt--) { // 加本层内所有节点的和
                auto t = q.front(); // 取出头节点并插入左右节点
                q.pop();
                if (t->left) {
                    q.push(t->left);
                }
                if (t->right) {
                    q.push(t->right);
                }
                sum += t->val;  // 加上这个节点的值
            }
            if (sum > max) {    // 如果本层和更大
                max = sum;  // 更新最大值
                res = count;    // 更新最大层和的最小层数
            }
        }
        return res;
    }
};