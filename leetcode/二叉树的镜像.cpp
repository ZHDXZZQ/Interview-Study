/*
    思路： 模拟，时间On，空间On
*/

/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pRoot TreeNode类 
     * @return TreeNode类
     */
    TreeNode* Mirror(TreeNode* pRoot) {
        // write code here
        if (!pRoot) {   // 如果该节点为空，返回空
            return nullptr;
        }
        auto left = pRoot->left;    // 记录一下左节点
        pRoot->left = pRoot->right; // 将右节点放到左边
        pRoot->right = left;        // 左节点放到右边
        Mirror(pRoot->left);        // 递归处理左右节点即可
        Mirror(pRoot->right);
        return pRoot;
    }
};