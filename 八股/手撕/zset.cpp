/*
    跳表（Skip List）是一种随机化数据结构，能够在Ologn的时间复杂度内进行查找、插入和删除操作。
    以下是一个实现跳表的基本示例，结合一个跳表作为有序集合（zset）的实现。

    跳表的基本结构
    节点结构：每个节点包含值、分数和指向下层和同层节点的指针。
    跳表结构：包含多个层级，每层是一个有序链表。
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;

// 节点结构
struct Node {
    double score;
    string value;
    vector<Node*> forward; // 向前指针
    Node(double s, const string& v, int level) : score(s), value(v), forward(level, nullptr) {}
};

// 跳表类
class SkipList {
private:
    int maxLevel;
    int currentLevel;
    Node* header; // 跳表的头节点
    double p; // 节点提升到上层的概率

public:
    SkipList(int maxLvl, double prob) : maxLevel(maxLvl), currentLevel(0), p(prob) {
        header = new Node(numeric_limits<double>::lowest(), "", maxLevel); // 初始化头节点
    }

    ~SkipList() {
        // 清理跳表
        Node* node = header;
        while (node) {
            Node* next = node->forward[0];
            delete node;
            node = next;
        }
    }

    // 随机生成节点层级
    int randomLevel() {
        int level = 0;
        while (static_cast<double>(rand()) / RAND_MAX < p && level < maxLevel) {
            level++;
        }
        return level;
    }

    // 插入操作
    void insert(double score, const string& value) {
        vector<Node*> update(maxLevel, nullptr);
        Node* current = header;

        // 寻找插入位置
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->score < score) {
                current = current->forward[i];
            }
            update[i] = current; // 更新节点路径
        }

        current = current->forward[0];

        // 如果 score 已存在，更新值
        if (current && current->score == score) {
            current->value = value; // 更新值
            return;
        }

        // 生成随机层级
        int newLevel = randomLevel();

        // 如果新层级高于当前层级，更新头节点的 forward 指针
        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i <= newLevel; i++) {
                update[i] = header;
            }
            currentLevel = newLevel;
        }

        // 创建新节点并插入
        Node* newNode = new Node(score, value, newLevel + 1);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    // 查找操作
    Node* search(double score) {
        Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->score < score) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return (current && current->score == score) ? current : nullptr; // 返回找到的节点或 nullptr
    }

    // 打印跳表
    void print() {
        for (int i = currentLevel; i >= 0; i--) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node) {
                cout << "(" << node->score << ", " << node->value << ") ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0))); // 设置随机种子
    SkipList skipList(4, 0.5); // 最大层级为 4，提升概率为 0.5

    // 测试插入
    skipList.insert(1.0, "a");
    skipList.insert(2.0, "b");
    skipList.insert(3.0, "c");
    skipList.insert(2.5, "d");

    // 打印跳表
    skipList.print();

    // 测试查找
    Node* foundNode = skipList.search(2.0);
    if (foundNode) {
        cout << "Found: (" << foundNode->score << ", " << foundNode->value << ")" << endl;
    } else {
        cout << "Not found" << endl;
    }

    return 0;
}

/*
    代码说明
        节点结构：Node 结构体包含分数、值和指向其他节点的指针。
        跳表结构：SkipList 类包含方法用于插入、查找和打印节点。
        插入操作：插入新节点时，首先查找适当的位置，然后创建节点并更新指针。
        查找操作：通过跳表的层级快速定位到目标节点。
        随机层级：使用 randomLevel 方法决定新节点的层级。
    使用方法
        创建 SkipList 实例并插入元素。
        调用 search 方法查找特定分数的值。
        调用 print 方法查看跳表结构。
    注意事项
        本示例为基本实现，实际使用中可扩展功能，例如删除节点、动态调整层级等。
        请根据需要进行异常处理和内存管理。
*/