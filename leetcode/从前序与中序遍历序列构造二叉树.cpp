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

// 思路： 根据性质模拟， 时间On，空间On。 力扣官方栈的思想很巧妙，可以迭代去做
// 1. 可以理解为每次创建一个子树的根节点，而在前序遍历中，该节点在该子树前序遍历的第一个位置
// 2. 因此，每次我们只需要根据前序遍历的第一个节点，找到他在中序遍历中的位置
// 3. 然后可以得到中序遍历中，该节点前即为左子树，该节点后即为右子树，每次找到子树的节点数量
// 4. 然后对应的就可以根据数量找到前序遍历中该节点的子树的根节点的位置，构造即可
// 5. 因为题目中说节点的值互不相同，因此为了中序遍历可以方便的找到具体的位置，我们采用哈希map

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
       int n = inorder.size();
        for (int i = 0; i < n; ++ i) {      //记录每个节点在中序遍历中的位置
            inorder_pos[inorder[i]] = i;
        }
        return build(0, 0, n - 1, preorder);    //开始构造
    }
    //pl指的是当前构建的子树前序遍历中的第一个节点
    //il和ir指的是当前构建的子树中序遍历的两端点，根据这两个端点和根节点在中序遍历ide位置，可以轻松得到两个子树的节点个数
    TreeNode* build(int pl, int il, int ir, vector<int>& preorder) {
        if (il > ir) { return NULL; }       //如果中序遍历的两端点中间没有任何东西，则表明该子树为空
        int pos = inorder_pos[preorder[pl]];    //pos记录了当前子树的根节点在中序遍历中的位置
        auto cur_node = new TreeNode(preorder[pl]); //当前pl指向的节点即为该子树的根节点，构建节点
        cur_node->left = build(pl + 1, il, pos - 1, preorder);  
        //其左子树的根节点一定是前序遍历中该节点的下一个节点，il和ir可以帮助我们判断是否子树为空，因此对pl无需做判断处理
        //左子树的中序遍历的左端点就是当前子树中序遍历的左端点，右端点就是当前根节点位置的左边一个
        cur_node->right = build(pl + pos - il + 1, pos + 1, ir, preorder);
        //右子树的中序遍历的左端点就是当前根节点位置的右边一个，右端点就是当前中序遍历的右端点
        //右子树的根节点在前序遍历中的位置，就是当前根节点在前序遍历中的位置加上左子树的数量
        return cur_node;
    }
private:
    unordered_map<int, int> inorder_pos;    //key为节点值，value为在中序遍历结果中的位置
};