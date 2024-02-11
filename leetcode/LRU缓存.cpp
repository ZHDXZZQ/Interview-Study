// 思路： 双向链表 + 哈希表，每次操作时间O1，总共空间On，n为capacity大小
// 1. 具体步骤看注释，就是构造了一个类，该方法没有处理被摘出节点的左右指针

class LRUCache {
private:
    struct node;
    typedef shared_ptr<node> nodeptr;
    struct node {           //设计结构体
        nodeptr left;       //双向链表的左右指针
        nodeptr right;
        int key;            //题目需要的key和value
        int value;
        node() {
            left = nullptr;
            right = nullptr;
        }
        node(int k, int v) : key(k), value(v) {     //构造函数
            left = nullptr;
            right = nullptr;
        }
    };
    nodeptr head;          //头尾节点，不存储数据，靠近头节点的是即将被淘汰的，尾节点的是新加入的
    nodeptr tail;
    unordered_map<int, nodeptr> i2n;    //现有的kv对
    int size;           //容器大小

public:
    LRUCache(int capacity) { 
        size = capacity;        //初始化容器大小和头尾节点，当前链表为空
        head = make_shared<node>();
        tail = make_shared<node>();
        head->right = tail;
        tail->left = head;
    }

    void insert(int k, int v) { //插入函数
        auto cur_node = make_shared<node>(k, v);    //新建kv节点
        i2n[k] = cur_node;      //并将节点插入队尾
        tail->left->right = cur_node;
        cur_node->right = tail;
        cur_node->left = tail->left;
        tail->left = cur_node;
    }

    void extract(int k) {
        if(k == -1) {       //如果k为-1，表示是当前容器已满，需将队头移出
            auto cur_node = head->right;
            head->right = head->right->right;
            head->right->left = head;
            i2n.erase(cur_node->key);
        } else {            //否则的话是容器中已存在当前key，需要改变value的情况，把当前节点摘出
            auto cur_node = i2n[k];
            cur_node->left->right = cur_node->right;
            cur_node->right->left = cur_node->left; 
            i2n.erase(cur_node->key);
        }
    }

    int get(int key) {
        if(i2n.find(key) != i2n.end()) {    //如果找到了key对应的节点
            auto value = i2n[key]->value;
            extract(key);       //将当前节点从链表中摘出放到队尾
            insert(key, value);
            return value;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        if(size == 0) return;
        if(i2n.find(key) != i2n.end()) {    //如果找到了当前节点
            extract(key);           //需要先把该节点放到队尾，再更新value的值
            insert(key, value);
        } else {
            if(i2n.size() >= size) {    //没找的的话需要插入，此时判断是否容器已满
                extract(-1);            //容器已满移出队头
            }
            insert(key, value);     //然后插入新增节点
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
























/* ------------------------------ */
//下附Y总优化版本，实际上就是换了种写法
class LRUCache {
public:
    struct node{
        int key, val;
        node *left, *right;  //双向链表
        node(int key, int val) {  //构造函数
            this->key = key, this->val = val;
            left = NULL, right = NULL;
        }
    }*L, *R;  //声明两个左右端点，最左端表示新使用，最右端表示最久未使用

    int n;  //缓存大小

    unordered_map<int, node*> rec;  //key对应找到node

    LRUCache(int capacity) {
        n = capacity;
        L = new node(-1, -1);  //初始化
        R = new node(-1, -1);
        L->right = R;  //当前链表为空
        R->left = L;
    }
    
    void remove(node *t) {  //移除t节点
        t->right->left = t->left;
        t->left->right = t->right;
    }

    void insert(node *t) {  //把这个刚使用的节点插到L后面
        t->right = L->right;
        t->left =  L;
        L->right->left = t;
        L->right = t;
    }

    int get(int key) {
        if(rec.find(key) == rec.end()) return -1;  //没找到
        auto *p = rec[key];
        remove(p);  //重新插入这个节点，因为刚刚使用过
        insert(p);
        return p->val;
    }
    
    void put(int key, int value) {
        if(rec.find(key) != rec.end()) {  //如果找到了
            auto *p = rec[key];
            p->val = value;  //更改val的值并重新插入
            remove(p);
            insert(p);
        }
        else {   //如果没找到
            if(rec.size() == n) {  //如果缓存满了
                auto *p = R->left;  //删掉一个最久未使用的
                remove(p);
                rec.erase(p->key);  //从rec种删除
                delete p;  //释放这块的空间
            }
            auto *p = new node(key, value);
            rec[key] = p;  //插入一个新节点
            insert(p);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */