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

// 思路： 二分，时间O（logn）^2，空间Ologn递归栈空间
// 1. 利用完全二叉树和满二叉树的性质，进行左右子树的递归分治
// 2. 如果某一个子树为满二叉树，则无需再往下递归，直接计算该子树的节点数和返回给父节点即可
// 3. 如果一个子树不是满二叉树，一定是右边不满足，则需要对左右子树进行递归，直到找到最小的满二叉树
// 4. 每次利用满二叉树的性质可以方便的在Ologn的时间复杂度下计算一个满二叉树的节点数
// 5. 而找到所有的满二叉树需要Ologn的时间复杂度，所有总的时间复杂度为O（logn）^2

class Solution {
public:
    int countNodes(TreeNode* root) {

        if(!root) return 0;         //如果当前节点为空，直接返回0个
        int left = 1, right = 1;    //记录左孩子的最大层数和右孩子的最大层数
        auto left_node = root->left, right_node = root->right;  //遍历左孩子和右孩子
        while(left_node) {          //一直遍历到最底部，用于判断该子树是否为满二叉树
            left_node = left_node->left;
            ++ left;
        }
        while(right_node) {
            right_node = right_node->right;
            ++ right;
        }
        if(left == right) {         //如果两边的深度相同，说明该子树为满二叉树，利用返回该满二叉树的节点个数
            return pow(2, right) - 1;
        }
        return countNodes(root->left) + 1 + countNodes(root->right);    //否则的话递归左右子树，返回当前子树的节点数
    }
};