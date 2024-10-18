/*
    思路： dfs，时间On，空间Ologn，最差On
*/

class Solution {
public:
    // 返回当前树的深度，如果子树不平衡，返回 -1
    int dep(TreeNode* t) {
        if (!t) return 0;
        
        int left_depth = dep(t->left);
        if (left_depth == -1) return -1;  // 左子树不平衡
        
        int right_depth = dep(t->right);
        if (right_depth == -1) return -1;  // 右子树不平衡
        
        // 如果左右子树的深度差大于 1，返回 -1 表示不平衡
        if (abs(left_depth - right_depth) > 1) {
            return -1;
        }
        
        // 返回当前树的深度
        return max(left_depth, right_depth) + 1;
    }

    bool IsBalanced_Solution(TreeNode* pRoot) {
        // 通过递归的深度计算来判断是否平衡
        return dep(pRoot) != -1;
    }
};
