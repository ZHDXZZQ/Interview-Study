// 思路： 模拟实现类 字典树，时间每个操作为On，空间总体为O26*m，可认为Om，其中，n为单词个数，m为最大插入单词长度
// 1. 具体实现看注释
class Trie {
public:
    struct node {       //定义节点结构体，一个节点代表一个字符
        bool is_end;    //判断当前节点是否是某个单词的结尾
        vector<shared_ptr<node>> son;   //子节点，定义26个表示下一个字符，共享指针可以不用

        node() {
            is_end = false;     //初始化构造函数，结尾标志置fasle
            son.resize(26, nullptr);    //构造26个空节点
        }
    };
    shared_ptr<node> root;      //声明root节点

    Trie() {
        root = make_shared<node>(); //初始化root节点，root不表示任何字符
    }
    
    void insert(string word) {
        auto cur_node = root;
        for(auto& c : word) {       //遍历每个字符
            int pos = c - 'a';      //该字符在26个字母中的顺序，用来确定在son节点中的位置
            if(cur_node->son[pos] == nullptr) {     //如果当前字符的son节点对应位置为空，表明之前没有存储该字符顺序的单词
                cur_node->son[pos] = make_shared<node>();   //将该字符的son节点构造新node
            }
            cur_node = cur_node->son[pos];      //将当前节点指向下一个字符对应的节点
        }
        cur_node->is_end = true;        //构造完成后，cur_node指向最后一个字符的节点，将其is_end置为true标记为单词结尾
    }
    
    bool search(string word) {
        auto cur_node = root;
        for(auto& c : word) {
            int pos = c - 'a';
            if(cur_node->son[pos] == nullptr) return false;     //如果下一个字符找不到，则说明不存在该单词
            cur_node = cur_node->son[pos];      //否则指向下一个字符所对应的节点
        }
        return cur_node->is_end;        //如果该节点是单词结尾，则为true，否则word是某个单词的前缀，返回false
    }
    
    bool startsWith(string prefix) {
        auto cur_node = root;
        for(auto& c : prefix) {
            int pos = c - 'a';
            if(cur_node->son[pos] == nullptr) return false;
            cur_node = cur_node->son[pos];
        }
        return true;        //前缀无需考虑是否是结尾，只要所有字符顺序存储过，则返回true
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */






















//附优化版本，我也不明白为啥会在时空上都有优化，懂的小伙伴可以交流下
class Trie {
public:
    struct node{
        bool whether_end;
        node *son[26];
        node() {
            this->whether_end = false;  //判断当前位置是否作为某一个单词的结尾
            for(int i = 0; i < 26; i ++) this->son[i] = NULL;  //往下与26个字母可能存在任意组合
        }
    }*root;

    Trie() {
        root = new node();
    }
    
    void insert(string word) {
        auto tmp = root;
        for(auto ch: word) {
            if(!tmp->son[ch - 'a']) tmp->son[ch - 'a'] = new node();  //没找到下一个节点就新建
            tmp = tmp->son[ch - 'a'];
        }
        tmp->whether_end = true;  //最后一个字符的节点打一个true表示作为某一个单词的结尾
    }
    
    bool search(string word) {
        auto tmp = root;
        for(auto ch: word) {
            if(!tmp->son[ch - 'a']) return false;  //如果中间某处找不到，表示单词不存在
            tmp = tmp->son[ch - 'a'];
        }
        return tmp->whether_end;  //判断这个结尾的节点是否是一个存过的单词的结尾
    }
    
    bool startsWith(string prefix) {
        auto tmp = root;
        for(auto ch: prefix) {
            if(!tmp->son[ch - 'a']) return false;  //如果中间某处找不到，表示前缀不存在
            tmp = tmp->son[ch - 'a'];
        }
        return true;  //否则的话前缀存在
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */