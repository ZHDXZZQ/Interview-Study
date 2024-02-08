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

// 思路： 利用队列/双端队列实现层序遍历，时间On，空间On
// 1. 将每层的节点放入队列中，记录每层节点数
// 2. 将该层节点依次出队并记录，并依次插入左右孩子
// 3. 此时队列中为下一层所有节点的按序排列，重复上述步骤，直到队列为空

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == NULL) return {}; //如果是空树，直接返回
        vector<vector<int>> res;    //存答案
        queue<TreeNode*> tnq;       //使用队列或双端队列存储每层的节点
        tnq.push(root);             //先将根节点入队
        while(!tnq.empty()) {       //只要队列中还有节点，就表明没有遍历完所有节点
            int cnt = tnq.size();   //cnt用于记录当前层有多少节点
            vector<int> cur_res;    //用于存储当前层的遍历结果
            while(cnt --) {         //将当前层的节点依次出列，并将左右孩子依次入队
                auto head = tnq.front();  
                tnq.pop();          //队头出队
                cur_res.push_back(head->val);   //将队头的值记录
                if(head->left) tnq.push(head->left);    //将队头的左右孩子入队
                if(head->right) tnq.push(head->right);
            }
            res.push_back(cur_res);     //当前层遍历完，结果更新
        }
        return res;
    }
};