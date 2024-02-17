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

// 思路： 利用队列进行层次遍历bfs，时间On，空间On
// 1. 利用队列存储当前层的所有节点
// 2. 利用一个标志判断当前层是从左往右遍历还是从右往左遍历
// 3. 参照树的层序遍历进行即可

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(!root) return {};        //特判
        queue<TreeNode*> q;         //用于按序存储每层的节点
        vector<vector<int>> res;
        q.push(root);           //根节点入队
        bool flag = true;       //true为从左往右遍历，false为从右往左遍历
        while(q.size()) {       //当前队列中存储的是该层的全部节点，如果不为空，则需要继续遍历
            int cnt = q.size(); //记录该层的节点个数，准确的每次干掉的只要该层的节点
            vector<int> tmp;    //存储该层的结果
            while(cnt --) {     //遍历该层的每个节点
                auto front = q.front();     //取出队头节点
                if(front->left) q.push(front->left);    //将队头节点的左右孩子依次入队，保证按序层次遍历
                if(front->right) q.push(front->right);
                q.pop();        //将队头节点出队
                tmp.push_back(front->val);  //将队头节点插入临时结果中
            }
            if(flag == false) {     //如果为false，则从右往左遍历，需要翻转
                reverse(tmp.begin(), tmp.end());        //时间On，空间O1
                flag = true;        //下一次从左往右遍历
            } else {
                flag = false;       //否则的话从左往右遍历无需翻转，只需要更改标志让下一次从右往左遍历即可
            }
            res.push_back(tmp);     //临时结果插入结果中
        }
        return res;
    }
};