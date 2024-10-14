/*
B树（B-Tree）是一种平衡的多路查找树，广泛应用于文件系统和数据库的索引结构。
B树的每个节点可以包含多个关键字（keys）和多个子树指针（children），并且节点中的关键字按升序排列。

B树的特点包括：
    每个节点可以有多个子节点。
    树的所有叶子节点处在同一层。
    B树是高度平衡的，具有较高的查找、插入和删除效率。

B树的性质：
    节点中的关键字数量范围是 [t−1,2t−1]，其中 t 是B树的阶数（最小度数）。
    每个非叶子节点有 [t,2t] 个子节点。
    根节点至少有两个子节点（除非是空树或单个节点的树）。
    插入和删除操作会保持树的平衡。

B树的基本操作：
    插入：在叶子节点进行插入，如果节点超过容量则进行节点分裂。
    删除：涉及合并或借用相邻节点的关键字，保持树的平衡。

插入操作：
    如果根节点满了，先分裂根节点，创建一个新根节点，然后将关键字插入到合适的子树中。
    插入非满节点时，直接插入到叶子节点中，如果子节点满了就先进行分裂。
*/
#include <iostream>
#include <vector>

// B树节点
class BTreeNode {
public:
    std::vector<int> keys;     // 节点中的关键字
    std::vector<BTreeNode*> children;  // 子节点指针
    int t;                      // B树的最小度数
    bool isLeaf;                // 是否为叶子节点

    BTreeNode(int _t, bool _isLeaf);
    
    // 查找一个关键字
    BTreeNode* search(int key);
    
    // 插入一个新的关键字到B树中
    void insertNonFull(int key);
    
    // 分裂子节点
    void splitChild(int i, BTreeNode* y);
    
    // 打印B树的结构
    void traverse();
};

// 构造函数
BTreeNode::BTreeNode(int _t, bool _isLeaf) {
    t = _t;
    isLeaf = _isLeaf;
}

// 遍历B树
void BTreeNode::traverse() {
    for (int i = 0; i < keys.size(); i++) {
        // 如果这个节点不是叶子节点，递归打印子树
        if (!isLeaf) {
            children[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    // 打印最后一个子节点
    if (!isLeaf) {
        children[keys.size()]->traverse();
    }
}

// 在B树中查找一个关键字
BTreeNode* BTreeNode::search(int key) {
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

// 插入非满节点
void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;
    
    if (isLeaf) {
        // 在叶子节点中插入新关键字
        keys.push_back(0);  // 占位
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;  // 插入新关键字
    } else {
        // 在非叶子节点中递归查找插入位置
        while (i >= 0 && keys[i] > key) {
            i--;
        }
        
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            // 如果子节点满了，先分裂
            splitChild(i + 1, children[i + 1]);
            
            // 检查中间关键字是否需要插入到右边的子节点
            if (key > keys[i + 1]) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(key);
    }
}

// 分裂子节点
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys.resize(t - 1);
    
    // 将y的后t-1个关键字移动到z
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }
    
    // 如果不是叶子节点，将y的后t个子节点指针移动到z
    if (!y->isLeaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }
    
    // 缩减y的关键字个数
    y->keys.resize(t - 1);
    
    // 将z插入到当前节点的子节点指针中
    children.insert(children.begin() + i + 1, z);
    
    // 将y的中间关键字提升到当前节点
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// B树
class BTree {
public:
    BTreeNode* root;
    int t;  // 最小度数

    BTree(int _t) {
        root = nullptr;
        t = _t;
    }
    
    // 查找关键字
    BTreeNode* search(int key) {
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
void BTree::insert(int key) {
    if (root == nullptr) {
        // 如果根节点为空，创建新节点
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            // 如果根节点满了，分裂根节点
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            
            int i = (s->keys[0] < key) ? 1 : 0;
            s->children[i]->insertNonFull(key);
            
            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}

int main() {
    BTree t(3);  // 创建一个3阶B树
    
    // 插入数据
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
    
    std::cout << "遍历B树: ";
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
