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
// 1. 可以理解为每次创建一个子树的根节点，而在后序遍历中，该节点在该子树后序遍历的最后一个位置
// 2. 因此，每次我们只需要根据后序遍历的最后一个节点，即根节点，找到他在中序遍历中的位置
// 3. 然后可以得到，在中序遍历中，该节点位置前的节点即为左子树，该节点位置后的节点即为右子树，每次找到下一个子树的节点数量
// 4. 然后对应的就可以根据数量找到后序遍历中该节点的子树的根节点的位置，构造即可
// 5. 因为题目中说节点的值互不相同，因此为了中序遍历可以方便的找到具体的位置，我们采用哈希map

class Solution {
public:
    //pr为当前子树根节点的位置，即后序遍历中根节点的下标，il和ir为中序遍历中当前子树的节点的范围
    TreeNode* build(int pr, int il, int ir, vector<int>& postorder) {
        if (il > ir) { return nullptr; }    //如果当前子树的中序遍历为空，返回空
        int& cur_val = postorder[pr];       //找到当前子树的根节点的值
        auto cur_node = new TreeNode(cur_val);  //构建该子树的根节点
        int& in_pos = inorder_pos[cur_val];     //找到该根节点在中序遍历中的位置
        cur_node->left = build(pr - ir + in_pos - 1, il, in_pos - 1, postorder);    //构造左子树
        //左子树的根节点为当前根节点在后序遍历中的位置往前走m个，m为其右子树的节点个数，左子树为当前根节点在中序遍历中的位置左边的节点
        cur_node->right = build(pr - 1, in_pos + 1, ir, postorder); //构造右子树
        //右子树的根节点为当前根节点在后续遍历中的位置往前1个，右子树为当前根节点中序遍历中的位置右边的节点
        return cur_node;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        for (int i = 0; i < n; ++ i) {  //记录每个节点中序遍历的位置
            int& num = inorder[i];
            inorder_pos[num] = i;
        }
        return build(n - 1, 0, n - 1, postorder);   //初始化传入参数，根节点为最后一个节点
    }

private:
    unordered_map<int, int> inorder_pos;
};