/*
    二叉排序树，其中序遍历结果是有序的，可能是链状树，效率不稳定
    查找时间复杂度位于Ologn-On之间
*/

#include <iostream>

using namespace std;

template<typename T>
class BSTNode {
public:
    T val;
    int pos;
    BSTNode* left;
    BSTNode* right;

    BSTNode(T value, int p) : val(value), pos(p), left(nullptr), right(nullptr) {}
};

template<typename T>
class BSTree {
public:
    void insert(T num, int pos) {
        if (root == nullptr) {
            root = new BSTNode<T>(num, pos);
            return;
        }
        BSTNode<T>* parent = nullptr;
        BSTNode<T>* temp = root;
        
        // 查找合适的位置
        while (temp != nullptr) {
            parent = temp;
            if (num > temp->val) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }

        // 插入新节点到父节点的左或右子树
        if (num > parent->val) {
            parent->right = new BSTNode<T>(num, pos);
        } else {
            parent->left = new BSTNode<T>(num, pos);
        }
    }

    void build(vector<T>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++ i) {
            int& num = nums[i];
            insert(num, i);
        }
    }

    void search(int& target) {
        auto temp = root;
        while (temp) {
            if (temp->val == target) {
                cout << " found target : " << target << " 's position = " << temp->pos + 1 << endl;
                return ;
            }
            if (temp->val < target) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        cout << "no found : " << target << endl;
    }

    void debug() {
        debug_inorder(root);
    }

private:
    BSTNode<T>* root = nullptr;

    void debug_inorder(BSTNode<T>* t) {
        if (t == nullptr) {
            return;
        }
        debug_inorder(t->left);
        cout << t->val << " , ";
        debug_inorder(t->right);
    }
};

template <class T>
void BstSearch(std::vector<T>& nums, T target) {
    int n = nums.size();
    BSTree<int> tree;
    tree.build(nums);
    tree.search(target);
    tree.debug();
}