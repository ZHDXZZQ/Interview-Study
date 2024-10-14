/*
B+树是一种在数据库系统中常用的平衡多路搜索树，它是B树的一种变体，主要用于索引数据结构。

B+树与B树的主要区别在于：
    B+树的非叶子节点不保存数据记录，只保存键值。
    所有叶子节点通过指针连接形成一个链表，便于范围查询和顺序访问。

插入操作：
    如果根节点为空，创建一个新的叶子节点。
    否则，根据关键字大小找到合适的位置进行插入。
*/

#include <iostream>
#include <vector>

// B+树节点
class BPlusTreeNode {
public:
    std::vector<int> keys;            // 节点中的关键字
    std::vector<BPlusTreeNode*> children;  // 子节点指针
    BPlusTreeNode* next;             // 下一个叶子节点指针（仅叶子节点有）
    bool isLeaf;                      // 是否为叶子节点

    BPlusTreeNode(bool _isLeaf);
    
    // 查找一个关键字
    BPlusTreeNode* search(int key);
    
    // 插入一个新的关键字到B+树中
    void insert(int key);
    
    // 遍历B+树
    void traverse();
};

// 构造函数
BPlusTreeNode::BPlusTreeNode(bool _isLeaf) {
    isLeaf = _isLeaf;
    next = nullptr;
}

// 遍历B+树
void BPlusTreeNode::traverse() {
    for (int i = 0; i < keys.size(); i++) {
        if (!isLeaf) {
            children[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    if (!isLeaf) {
        children[keys.size()]->traverse();
    }
}

// 查找关键字
BPlusTreeNode* BPlusTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }
    
    if (i < keys.size() && keys[i] == key) {
        return this;  // 找到关键字
    }
    
    if (isLeaf) {
        return nullptr;  // 如果是叶子节点，返回空表示未找到
    }
    
    return children[i]->search(key);  // 递归查找子节点
}

// 插入操作
void BPlusTreeNode::insert(int key) {
    if (isLeaf) {
        // 在叶子节点中插入新关键字
        int i = 0;
        while (i < keys.size() && keys[i] < key) {
            i++;
        }
        keys.insert(keys.begin() + i, key);
    } else {
        // 在非叶子节点中找到合适的子节点插入
        int i = 0;
        while (i < keys.size() && keys[i] < key) {
            i++;
        }
        children[i]->insert(key);
    }
}

// B+树
class BPlusTree {
public:
    BPlusTreeNode* root;

    BPlusTree() {
        root = nullptr;
    }
    
    // 查找关键字
    BPlusTreeNode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }
    
    // 插入关键字
    void insert(int key);
    
    // 遍历树
    void traverse() {
        if (root != nullptr) root->traverse();
    }
};

// 插入操作
void BPlusTree::insert(int key) {
    if (root == nullptr) {
        // 如果根节点为空，创建新节点
        root = new BPlusTreeNode(true);
        root->keys.push_back(key);
    } else {
        root->insert(key);
    }
}

int main() {
    BPlusTree t;  // 创建一个B+树
    
    // 插入数据
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    
    std::cout << "遍历B+树: ";
    t.traverse();
    std::cout << std::endl;
    
    int key = 6;
    (t.search(key) != nullptr) ? std::cout << "找到 " << key << std::endl :
                                 std::cout << "未找到 " << key << std::endl;
    
    key = 15;
    (t.search(key) != nullptr) ? std::cout << "找到 " << key << std::endl :
                                 std::cout << "未找到 " << key << std::endl;
    
    return 0;
}
