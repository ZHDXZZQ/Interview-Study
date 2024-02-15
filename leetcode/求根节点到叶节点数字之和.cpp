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

// 思路： dfs递归，时间On，空间O1
// 1. 从父节点遍历所有孩子节点，直到叶节点，每次将当前节点及其父节点构成的值往下传
// 2. 当到达叶节点时，将这条路径上构成值加到结果中去
// 3. 因为返回结果是int类型，所以无需考虑溢出问题，如果是string或vector用高精度计算的方法即可

class Solution {
public:
    int res = 0;

    void calc(TreeNode* t, int num) {
        if(t == nullptr) return;        //如果当前节点为空，返回
        int cur_num = 10 * num + t -> val;  //否则将之前传来的值乘10，再加上当前结点的值
        if(!t -> left && !t -> right) { //如果该节点为叶子节点，将值加到结果中去
            res += cur_num;
            return;
        }
        calc(t -> left, cur_num);       //否则的话将值继续往左右子节点中传
        calc(t -> right, cur_num);
        return;
    }

    int sumNumbers(TreeNode* root) {
        calc(root, 0);
        return res;
    }
};