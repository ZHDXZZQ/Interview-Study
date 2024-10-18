/*
    思路： dfs，时间On²，空间On，平均空间Ologn
*/

class Solution {
public:
    int dfs(TreeNode* t, int sum, int cur) {
        if (!t) {
            return 0;
        }
        
        // 当前路径和
        cur += t->val;
        
        // 判断当前路径和是否等于目标 sum
        int count = (cur == sum) ? 1 : 0;
        
        // 继续向左子树和右子树递归，并统计路径数
        count += dfs(t->left, sum, cur);
        count += dfs(t->right, sum, cur);
        
        return count;
    }

    int FindPath(TreeNode* root, int sum) {
        if (!root) {
            return 0;
        }

        // 以当前节点为根的路径数
        int res = dfs(root, sum, 0);

        // 递归左右子树，寻找从其他节点开始的路径，要从入口处递归
        res += FindPath(root->left, sum);
        res += FindPath(root->right, sum);

        return res;
    }
};
