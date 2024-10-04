/*
    红黑树（Red-Black Tree）是一种 自平衡二叉搜索树，它在插入和删除操作时保持平衡，通过增加额外的颜色属性来限制树的结构，以确保其高度是对数级别，从而保证常数时间的平均查找性能。

    红黑树的特性：
        每个节点是红色或黑色。
        根节点是黑色。
        所有叶子节点（空节点）都是黑色。
        不能有两个相邻的红色节点（红色节点的父节点和子节点不能都是红色）。
        从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。
*/
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    // 构造函数
    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;  // 新节点默认为红色
    }
};

class RedBlackTree {
private:
    Node* root;

    // 左旋操作
    void rotateLeft(Node*& pt) {
        Node* pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != nullptr) {
            pt->right->parent = pt;
        }

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr) {
            root = pt_right;
        } else if (pt == pt->parent->left) {
            pt->parent->left = pt_right;
        } else {
            pt->parent->right = pt_right;
        }
        pt_right->left = pt;
        pt->parent = pt_right;
    }

    // 右旋操作
    void rotateRight(Node*& pt) {
        Node* pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != nullptr) {
            pt->left->parent = pt;
        }

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr) {
            root = pt_left;
        } else if (pt == pt->parent->left) {
            pt->parent->left = pt_left;
        } else {
            pt->parent->right = pt_left;
        }
        
        pt_left->right = pt;
        pt->parent = pt_left;
    }

    // 修复插入操作引起的红黑树性质违规
    void fixViolation(Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // 父节点是祖父节点的左子节点
            if (parent_pt == grand_parent_pt->left) {

                Node* uncle_pt = grand_parent_pt->right;

                // 情况1：叔叔节点是红色
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // 情况2：当前节点是其父节点的右子节点，需要左旋
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // 情况3：当前节点是其父节点的左子节点，需要右旋
                    rotateRight(grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {  // 父节点是祖父节点的右子节点
                Node* uncle_pt = grand_parent_pt->left;

                // 情况1：叔叔节点是红色
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    // 情况2：当前节点是其父节点的左子节点，需要右旋
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // 情况3：当前节点是其父节点的右子节点，需要左旋
                    rotateLeft(grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

public:
    // 构造函数
    RedBlackTree() { root = nullptr; }

    // 插入函数
    void insert(const int& data) {
        Node* pt = new Node(data);

        root = BSTInsert(root, pt);

        fixViolation(pt);
    }

    // 标准的二叉搜索树插入操作
    Node* BSTInsert(Node* root, Node* pt) {
        if (root == nullptr) {
            return pt;
        }

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    // 中序遍历
    void inorder() { inorderHelper(root); }

    void inorderHelper(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderHelper(root->left);
        cout << root->data << " ";
        inorderHelper(root->right);
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    cout << "创建的红黑树的中序遍历结果为：\n";
    tree.inorder();

    return 0;
}
