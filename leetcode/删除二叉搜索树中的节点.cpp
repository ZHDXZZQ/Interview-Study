/*
    思路： 模拟，时间Ologn（即Oh），空间Ologn递归栈空间
    代码写的比较冗余，可以优化，懒得优化了hhh
*/

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
class Solution {
public:
    TreeNode* flr(TreeNode* t) {    // 找到左孩子的最右孩子
        if (!t) {
            return nullptr;
        }
        auto tmp = t;
        while (tmp->right) {
            tmp = tmp->right;
        }
        return tmp;
    }

    TreeNode* find_parent(TreeNode* t, int& key) {  // 找到目标节点的父节点
        if (!t) {
            return nullptr;
        }
        if (t->val == key) {
            return t;
        }
        if (t->left && t->left->val == key) {
            return t;
        }
        if (t->right && t->right->val == key) {
            return t;
        }
        if (t->val > key) {
            return find_parent(t->left, key);
        }
        return find_parent(t->right, key);
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode* target_parent = find_parent(root, key);
        if (target_parent == nullptr) {
            return root;
        }
        if (target_parent == root && root->val == key && !root->left && !root->right) { // 如果目标节点是根节点且无孩子
            return nullptr;
        }
        auto target = new TreeNode();
        bool is_left = true;
        if (target_parent->left && target_parent->left->val == key) {   // 找到要删除的目标节点
            target = target_parent->left;
        } else if (target_parent->right && target_parent->right->val == key) {
            target = target_parent->right;
            is_left = false;
        } else {
            target = target_parent;
        }
        if (!target->left && !target->right) {  // 如果目标节点无孩子，直接删除
            if (is_left) {
                target_parent->left = nullptr;
            } else {
                target_parent->right = nullptr;
            }
        } else if (target->left && !target->right) {    // 如果只有左孩子
            auto left_son = target->left;
            target->val = left_son->val;
            target->left = left_son->left;
            target->right = left_son->right;
            delete left_son;
        } else if(!target->left && target->right) { // 如果只有有孩子
            auto right_son = target->right;
            target->val = right_son->val;
            target->left = right_son->left;
            target->right = right_son->right;
            delete right_son;
        } else {    // 如果两边都有孩子
            auto left_son = target->left;
            auto right_son = target->right;
            target->val = right_son->val;
            auto left_right = flr(left_son);
            left_right->right = right_son->left;
            target->right = right_son->right;
            delete right_son;
        }
        return root;
    }
};