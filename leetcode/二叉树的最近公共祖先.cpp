/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 思路： 利用位运算，时间On，空间O1
// 1. 可以利用位运算来表示该节点的子树中有没有p和q
// 2. 例如0表示都没有，1表示有p，2表示有q，3表示都有，就是00，01，10，11
// 3. 也可以用整数类型来表示有无p和q节点
// 4. 然后进行深度优先遍历，最先得到二者都有的节点即为最近公共祖先

class Solution {
public:
    TreeNode* res = NULL;       //结果节点，全局声明

    int dfs(TreeNode* t, TreeNode* p, TreeNode* q) {    //返回值表示该节点及其子树是否包含p和q
        if(res != NULL || !t) return 0;     //如果已经得到最终结果或者该点为空，则返回0即可
        int status = 0;
        if(t == p) status = 1;              //状态记录当前节点及其子树是否包含p和q
        else if(t == q) status = 2;
        status |= dfs(t->left, p ,q);       //与子树的结果进行或运算
        status |= dfs(t->right, p, q);
        if(status == 3) {                   //如果值为3表示该节点及其子树包含p和q，且一定是第一个全部包含的
            res = t;                        //记录结果并返回0即可，因为上面的节点无需再计算了
            return 0;
        }
        return status;                      //返回当前子树包含了p和q的情况
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return res;
    }
};