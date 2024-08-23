/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
    思路： 层序遍历，也可以有任何一种遍历方式进行，时间On，空间On
    序列化与反序列化都用队列进行
    1. 序列化时层序遍历所有节点，对于空节点，存储为N，否则都存储为val，节点之间利用逗号相隔
    2. 反序列化时，每次构造当前队列头的节点的左右节点，如果构造出新节点，则入队，为空则不管
*/

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {    // 特判
            return "";
        }
        string res;
        queue<TreeNode*> q;
        q.push(root);   // 存储根节点
        res += to_string(root->val) + ',';  // 存储根节点的值
        while (q.size()) {
            auto t = q.front();
            q.pop();
            if (t->left) {  // 存入根节点的左右节点的值，为空则存储N，利用逗号分隔每个节点
                res += to_string(t->left->val) + ',';
                q.push(t->left);
            } else {
                res += "N,";
            }
            if (t->right) {
                res += to_string(t->right->val) + ',';
                q.push(t->right);
            } else {
                res += "N,";
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {     // 特判
            return nullptr;
        }
        queue<TreeNode*> q;
        int ptr = 0;    // 指向当前data的位置
        int n = data.size();
        while (ptr < n && data[ptr] != ',') {   // 找到根节点的值的位置
            ++ ptr;
        }
        int root_val = stoi(data.substr(0, ptr));
        ++ ptr; // ptr每轮都指向当前节点的值的开头
        TreeNode* root = new TreeNode(root_val);    // 创造根节点并插入
        q.push(root);
        while (ptr < n && q.size()) {   // 只要还有节点待构造
            auto t = q.front(); // 当前要构造的便是头节点的左右孩子，并且一定是成对的
            q.pop();
            int start = ptr;    // 记录值得开头
            if (data[ptr] != 'N') { // 非空
                while (ptr < n && data[ptr] != ',') {
                    ++ ptr;
                }
                int left_val = stoi(data.substr(start, ptr - start));   // 找到左孩子的值
                TreeNode* l = new TreeNode(left_val);   // 创造新结点并加入队列
                t->left = l;
                q.push(l);
                ++ ptr;
            } else {
                ptr += 2;   // 为空得节点直接指向下一个节点
            }
            start = ptr;        // 更新开头
            if (data[ptr] != 'N') { // 同理，找到右孩子
                while (ptr < n && data[ptr] != ',') {
                    ++ ptr;
                }
                int right_val = stoi(data.substr(start, ptr - start));
                TreeNode* r = new TreeNode(right_val);
                t->right = r;
                q.push(r);
                ++ ptr;
            } else {
                ptr += 2;
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));