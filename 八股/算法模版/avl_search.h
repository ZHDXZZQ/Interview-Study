#include <iostream>
#include <vector>

using namespace std;

// 节点结构
template<typename T>
class AVLNode {
public:
    T val;
    int pos;
    AVLNode* left;
    AVLNode* right;
    int height; // 节点的高度

    AVLNode(T value, int p) : val(value), pos(p), left(nullptr), right(nullptr), height(1) {}
};

// AVL树类
template<typename T>
class AVLTree {
public:
    void insert(T num, int pos) {
        root = insert(root, num, pos);
    }

    void search(int target) {
        auto temp = root;
        while (temp) {
            if (temp->val == target) {
                cout << "Found target: " << target << "'s position = " << temp->pos + 1 << endl;
                return;
            }
            if (temp->val < target) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        cout << "Not found: " << target << endl;
    }

private:
    AVLNode<T>* root = nullptr;

    // 插入节点并保持平衡
    AVLNode<T>* insert(AVLNode<T>* node, T num, int pos) {
        // 普通的BST插入
        if (node == nullptr) {
            return new AVLNode<T>(num, pos);
        }
        if (num < node->val) {
            node->left = insert(node->left, num, pos);
        } else if (num > node->val) {
            node->right = insert(node->right, num, pos);
        } else {
            return node; // 不允许重复值
        }

        // 更新当前节点的高度
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 检查平衡性
        int balance = getBalance(node);

        // 如果节点失去平衡，进行旋转操作
        // 左左情况
        if (balance > 1 && num < node->left->val) {
            return rightRotate(node);
        }
        // 右右情况
        if (balance < -1 && num > node->right->val) {
            return leftRotate(node);
        }
        // 左右情况
        if (balance > 1 && num > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // 右左情况
        if (balance < -1 && num < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // 右旋转
    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        // 进行旋转
        x->right = y;
        y->left = T2;

        // 更新高度
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x; // 新的根
    }

    // 左旋转
    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        // 进行旋转
        y->left = x;
        x->right = T2;

        // 更新高度
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y; // 新的根
    }

    // 获取节点高度
    int getHeight(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    // 获取平衡因子
    int getBalance(AVLNode<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
};

// 封装函数进行搜索
template <class T>
void AvlSearch(vector<T>& nums, T target) {
    AVLTree<T> tree;
    for (int i = 0; i < nums.size(); ++i) {
        tree.insert(nums[i], i);
    }
    tree.search(target);
}
