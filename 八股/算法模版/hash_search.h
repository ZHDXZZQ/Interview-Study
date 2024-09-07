/*
    散列函数：定义域必须包括全部可能存储的关键字，值域的范围要看具体散列表的大小和地址范围
    结果应该是等概率、均匀分布在整个地址空间，减少冲突
    尽量简单，O1的复杂度计算出结果。
    1. 直接定址法：y = x or y = ax + b
    2. 除留余数法：y = x % p
    3. 数字分析法：适合已知关键字集合的情况
    4. 平方取中法：选取关键字平方的中间几位作为地址

    处理冲突的方法
    1. 开放定址法：
        线性探测法：顺序往后找
        平方探测法：+1，-1，+4，-4，+9，-9...
        双散列法：再增加一个散列函数，当第一个地址冲突时，再计算一次新的函数
        伪随机序列法：随机数
    2. 拉链法

    示例一个简单的unordered_map，利用拉链法，即哈希桶
*/
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// 定义一个节点结构体，用于存储键值对
struct HashNode {
    int key;
    string value;

    HashNode(int k, string v) : key(k), value(v) {}
};

// 实现一个简易的 unordered_map 类
class UnorderedMap {
private:
    vector<list<HashNode>> table;  // 使用链表处理冲突
    int capacity;                  // 哈希表容量
    int size;                      // 哈希表中元素的数量

    // 哈希函数，将键映射到索引
    int hashFunction(int key) {
        return key % capacity;
    }

public:
    // 构造函数，初始化哈希表
    UnorderedMap(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    // 插入键值对
    void insert(int key, const string& value) {
        int hashIndex = hashFunction(key);
        
        // 遍历链表检查是否存在该键，存在则更新值
        for (auto& node : table[hashIndex]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        // 如果键不存在，则在链表中插入新节点
        table[hashIndex].push_back(HashNode(key, value));
        ++size;
        cout << "Inserted key " << key << " with value " << value << endl;
    }

    // 查找键值对
    string search(int key) {
        int hashIndex = hashFunction(key);

        // 遍历链表寻找键
        for (auto& node : table[hashIndex]) {
            if (node.key == key) {
                cout << "Found key " << key << " with value " << node.value << endl;
                return node.value;
            }
        }

        cout << "Key " << key << " not found" << endl;
        return "";
    }

    // 删除键值对
    void remove(int key) {
        int hashIndex = hashFunction(key);

        // 查找并删除链表中的节点
        auto& chain = table[hashIndex];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                --size;
                cout << "Removed key " << key << endl;
                return;
            }
        }

        cout << "Key " << key << " not found, cannot remove" << endl;
    }

    // 显示哈希表的内容
    void display() {
        for (int i = 0; i < capacity; ++i) {
            cout << "Bucket " << i << ": ";
            for (auto& node : table[i]) {
                cout << "(" << node.key << ", " << node.value << ") ";
            }
            cout << endl;
        }
    }

    // 获取哈希表中元素数量
    int getSize() const {
        return size;
    }

    // 获取哈希表的容量
    int getCapacity() const {
        return capacity;
    }
};

// 测试代码
template <class T>
void HashSearch(std::vector<T>& nums, T target) {
    UnorderedMap umap(nums.size()); 
    for (int i = 0; i < nums.size(); ++ i) {
        umap.insert(nums[i], to_string(i));
    }

    // 还可以删除某些kv对
    umap.search(target);

    umap.display();
}
