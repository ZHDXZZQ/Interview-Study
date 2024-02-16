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

// 思路： 层次遍历，时间On，空间On
// 1. 按照层次遍历的方法处理所有节点
// 2. 多一次判断，如果当前节点是该层的最后一个几点，则插入答案中

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return {};    //特判
        vector<int> res;        
        queue<TreeNode*> q;     //队列存储，用于层次遍历
        q.push(root);           //根节点入队
        while(q.size()) {       //只要队列中有节点，表明还没有结束，并且此时队列中的节点都是同一层的节点
            int cnt = q.size(); //记录当前层的节点数
            while(cnt --) {     //遍历该层每个节点
                auto head = q.front();  //记录当前的队头节点
                q.pop();        //将队头节点出队
                if(head->left) q.push(head->left);  //将队头节点的左右孩子依次入队
                if(head->right) q.push(head->right);
                if(cnt == 0) res.push_back(head->val);  //如果当前队头节点是该层最后一个节点，记录答案
            }       //该循环结束，队列中存储的就是下一层的所有节点按序存放的
        }   //循环结束，层次遍历结束
        return res;
    }
};