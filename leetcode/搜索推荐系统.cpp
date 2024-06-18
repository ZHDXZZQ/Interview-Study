/*
    思路： 字典树Trie， 时间OLlog3+S，空间O3L，其中L为所有products中的字符串的长度之和，S为searchword的长度，常数可省略
    1. 首先构建字典树，将每个单词的路打通，利用优先队列存储当前前缀字典序的3个单词
    2. 依次遍历每个单词的每个字母，对相同前缀的单词在每个节点存储下来，只存储3个
*/

class Solution {
public:
    struct node {
        priority_queue<string, vector<string>, less<string>> words; // 按字典序存储当前前缀相同的单词
        // priority_queue<string> words; 即可，less大根堆是默认的，greater是小根堆
        node* son[26];  // 在当前前缀的基础上，下个字母的节点
        node() {
            for (int i = 0; i < 26; ++ i) {
                son[i] = nullptr;
            }
        }
    };

    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        auto root = new node();
        vector<vector<string>> res;
        for (auto& word : products) {   // 遍历每个单词
            auto temp = root;
            for (auto& c : word) {  // 遍历每个字母
                auto pos = c - 'a'; // 当前字母的相对位置
                if (temp->son[pos] == nullptr) {    // 如果当前路径没有节点，则新建一个
                    temp->son[pos] = new node();
                }
                temp = temp->son[pos];
                temp->words.push(word); // 将当前单词插入到当前节点的同前缀词库中
                if (temp->words.size() > 3) {   // 如果大于3个，则堆顶弹出，此时是大根堆，弹出的是字典序靠后的单词
                    temp->words.pop();
                }
            }
        }
        auto search_ptr = root;
        bool flag = false;
        for (auto& c : searchWord) {    // 遍历每个字母
            auto pos = c - 'a';
            if (search_ptr->son[pos] == nullptr) {  // 如果当前节点为空，则后面都不会存在单词
                flag = true;    // 设置标记
            }
            if (flag) { // 后续所有的字母无需查找，直接插入空
                res.emplace_back();
                continue;
            }
            if (search_ptr->son[pos] != nullptr) {  // 否则的话如果当前节点存在
                vector<string> cur_res;
                search_ptr = search_ptr->son[pos];
                while (search_ptr->words.size()) {  // 则把当前前缀的单词取出，此时为逆序，最多3个
                    cur_res.push_back(search_ptr->words.top());
                    search_ptr->words.pop();
                }
                reverse(cur_res.begin(), cur_res.end());    // 翻转，此时为字段序
                res.push_back(cur_res); // 插入本轮查找的结果中
            }
        }
        return res;
    }
};