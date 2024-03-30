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

// 思路： 宽搜+栈，时间On，空间On
// 1. 利用队列进行正常的宽搜进行层次遍历，将每次的结果存入栈中
// 2. 将栈中的结果依次取出，放入结果中
// 3. 当然可以存储到结果中，最后reverse一下即可

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) { return {}; }   //特判
        stack<vector<int>> rec;     //栈存储结果
        queue<TreeNode*> q;         //队列用于宽搜
        vector<vector<int>> res;    //存储最终结果
        q.push(root);               //将根节点入队，初始化队列
        while (q.size()) {          //只要队列不空，就遍历该层次
            int n = q.size();       //当前队列的内容是该层的所有节点
            vector<int> tmp;
            while (n --) {          //每次只存储当前层的节点
                TreeNode* front = q.front();
                q.pop();            //取出队头
                tmp.push_back(front->val);  //将队头记录下来
                if (front->left) { q.push(front->left); }   //队头的左右子节点入队
                if (front->right) { q.push(front->right); }
            }
            rec.push(tmp);          //将该层结果入栈
        }
        while (!rec.empty()) {      //将栈中结果依次取出，存入最终结果
            res.push_back(rec.top());
            rec.pop();
        }
        return res;
    }
};