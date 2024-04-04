// 思路： 字典树+dfs剪枝+回溯， 时间Om*n*3^l， 空间Ok*l，其中，l为最长单词的长度，k为单词库中的单词个数
// 1. 构建字典树（具体的请参考Trie树的题目），插入每个列表中给定的单词到字典树中
// 2. 遍历每个格子，进行dfs，如果该字母有对应节点，则深度搜索
// 3. 碰到某个节点为单词结尾时，插入该单词，并标记该单词已被插入过，防止重复插入
// 4. 继续dfs，直到所有节点都不存在于树中，再开始下一个节点的搜索。具体看注释

class Solution {
public:
    struct Node {
        Node() {    //构造函数
            is_inserted = false;
            for (int i = 0; i < 26; ++ i) {
                son[i] = nullptr;
            }
        }
        bool is_inserted;   //标记是否被插入过
        string word;        //标记该节点为某个单词的结尾，并记录该单词
        Node* son[26];      //标记下一个字符节点
    };

    vector<string> res;     //存储结果
    int dx[4] = {0, 0, 1, -1};  //格子中的四个方向
    int dy[4] = {1, -1, 0, 0};
    int m, n;               //记录格子大小

    void dfs(int x, int y, vector<vector<char>>& board, Node* t) {
        char c = board[x][y];       //记录该格子的字符，方便回溯
        if (t->son[c - 'a'] == nullptr) {   //如果该字符不在链路中，则剪枝
            return;
        }
        auto cur_node = t->son[c - 'a'];    //如果存在则记录找到的节点
        if (!cur_node->word.empty() && !cur_node->is_inserted) {    //如果该节点为某个单词的结尾且该单词没有被插入过
            cur_node->is_inserted = true;
            res.push_back(cur_node->word);  //将该单词插入并记为已插入过
        }
        board[x][y] = '.';                  //将当前节点先擦掉，以免反复遍历
        for (int k = 0; k < 4; ++ k) {      //遍历该格子的四周
            int i = x + dx[k];
            int j = y + dy[k];
            if (i >= 0 && j >= 0 && i < m && j < n && board[i][j] != '.') {
                dfs(i, j, board, cur_node); //如果符合要求，则深搜
            }
        }
        board[x][y] = c;                //回溯
        return; 
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        root = new Node();  //创建根节点，根节点不代表任何字符
        for (auto& word : words) {      //遍历所有已知单词
            auto cur_node = root;       //用于记录节点
            for (auto& c : word) {      //遍历该单词的每个字符
                if (cur_node->son[c - 'a'] == nullptr) {    //如果该单词字符不在链路中存在
                    cur_node->son[c - 'a'] = new Node();    //则构造该节点
                }
                cur_node = cur_node->son[c - 'a'];          //将节点记录，遍历完整个单词
            }
            cur_node->word = word;      //当前节点为单词的最后一个字符，记录下来这个单词，方便后面记录结果
        }
        m = board.size();               //记录网格大小
        n = board[0].size();
        for (int i = 0; i < m; ++ i) {  //遍历每个格子
            for (int j = 0; j < n; ++ j) {
                dfs(i, j, board, root); //进行深搜
            }
        }
        return res;
    }

private:
    Node* root;     //根节点
};