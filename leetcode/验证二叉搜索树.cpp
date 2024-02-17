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

// 思路： 中序遍历，时间On，空间Ologn（链状树为On）
// 1. 因为是二叉搜索树，所以中序遍历一定是递增的
// 2. 而我们只需要判断当前值是否大于中序遍历的前一个值即可，可以节省空间（但栈空间也占用了不少）
// 3. 每次只需要记录中序遍历前一个结点的值是多少即可
// 4. 由于题目的取值范围为int全域，因此需要加一个标志判断是否是第一个节点

class Solution {
public:
    int last_num = 0;           //中序遍历的前一个节点的值
    bool is_first = true;       //当前节点是否是中序遍历的第一个节点
    bool isValidBST(TreeNode* root) {
        if(root == NULL) return true;   //如果当前节点为空，则不用判断
        bool success = true;            //记录状态
        success &= isValidBST(root->left);  //判断左子树是否符合要求，以中序遍历的顺序，左根右
        if(is_first == false) {         //判断该节点是否是第一个节点
            if(root->val <= last_num) return false; //如果不是，和前一个节点的值比较，如果非递增，则返回false，无需继续判断右子树
        } else {                //如果是第一个节点，
            is_first = false;   //则无需判断，只需要改变标志即可
        }
        last_num = root->val;   //记录当前节点的值为last_num用于下一个节点进行判断
        success &= isValidBST(root->right);     //中序遍历，右子树判断是否满足要求
        return success;         //返回当前子树是否满足要求
    }
};