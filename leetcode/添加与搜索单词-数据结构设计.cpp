// 思路： 字典树，同前面的Trie树，时间On，n为单个单词的最大长度，空间Om，m为所有单词的长度，前面有常数26倍。
// 1. 每个字母用一个节点来存，节点内包含26个子节点，指向26个可能的下一个字母
// 2. 节点用一个标志来标识是否该字符是某一个单词的结尾

class Node{
public:
    Node() {
        for (int i = 0; i < 26; ++ i) {
            next_char[i] = nullptr; //初始化每个节点的26个子节点
        }
    }

    bool is_end = false;    //标志该节点是否是某个单词的结尾
    Node* next_char[26];    //不能用vector，空间会超？
};

class WordDictionary {
public:
    WordDictionary() {
        root = new Node();
    }
    
    void addWord(string word) {
        int n = word.size();
        auto now_node = root;
        for (int i = 0; i < n; ++ i ) { //遍历每个字符
            int pos = word[i] - 'a';    //将每个字符在26个字母中的位置找到
            if (now_node->next_char[pos] == nullptr) {  //判断其对应子节点是否存在
                now_node->next_char[pos] = new Node();  //如果不存在则建立一个
            }
            now_node = now_node->next_char[pos];    //指向该子节点
        }
        now_node->is_end = true;        //遍历完之后，指向最后一个节点，将标志写为true
    }
    
    bool search(string word) {      //dfs深搜
        return dfs(word, 0, root);
    }

    bool dfs(string& word, int pos, Node* cur_node) {
        if (pos == word.size()) {   //如果搜到了单词的最后一个字母，返回该节点的标志
            return cur_node->is_end;
        }
        if (word[pos] == '.') { //如果碰到.，则将该节点的所有子节点遍历
            for (int i = 0; i < 26; ++ i) {
                if (cur_node->next_char[i] != nullptr) {    //如果子节点存在
                    bool res = dfs(word, pos + 1, cur_node->next_char[i]);  //当做一个成功匹配的字符继续深搜
                    if (res) { return true; }   //如果有任意一个序列成功，返回true
                }
            }
        } else {
            int cur_pos = word[pos] - 'a';  //如果是一个具体的字母，则找到位置
            if (cur_node->next_char[cur_pos] == nullptr) {  //判断该位置是否存在字母
                return false;   //不存在返回false
            } else {    //否则对该子节点继续搜索
                return dfs(word, pos + 1, cur_node->next_char[cur_pos]);
            }
        }
        return false;   //对应于上面为.情况深搜全部失败的情况，返回false
    }

private:
    Node* root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */