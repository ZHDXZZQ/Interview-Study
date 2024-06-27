/*
    思路： 字典树，时间On，空间On
    1. 构建字典树节点类型，根据字母，包含26个子节点
    2. 利用一个int类型来记录以该节点为单词结尾的该单词的个数
*/

#include <iostream>

using namespace std;

struct node {
    node* son[26];
    int count;
    node () : count(0) {    // 列表初始化最好和声明结构顺序相同，这样写可能会有问题
        for (int i = 0; i < 26; ++ i) {
            son[i] = nullptr;
        }
    }
} *Trie;

void insert(string& word) {
    auto temp = Trie;
    for (auto& c : word) {
        int pos = c - 'a';
        if (temp->son[pos] == nullptr) {
            temp->son[pos] = new node();
        }
        temp = temp->son[pos];
    }
    ++ temp->count;
}

void find(string& word) {
    auto temp = Trie;
    for (auto& c : word) {
        int pos = c - 'a';
        if (temp->son[pos] == nullptr) {
            cout << '0' << endl;
            return;
        }
        temp = temp->son[pos];
    }
    cout << temp->count << endl;
}

int main() {
    Trie = new node();
    int n;
    cin >> n;
    // cin.ignore();  // 忽略输入流中的换行符，避免getline()
    char type;
    string cmd;
    while (n --) {
        // string line;
        // getline(cin, line);  // 读取整行输入
        // type = line[0];  // 读取操作类型
        // cmd = line.substr(2);  // 读取操作字符串

        cin >> type >> cmd;

        // cmd需要改成char cmd[10010];
        // scanf(" %c %s", &type, cmd);  
        // 注意前面的空格来忽略前一个输入的换行符，cmd不能作为string输出，并且不建议scanf/printf和cin/cout混用
        if (type == 'I') {
            insert(cmd);
        } else if (type == 'Q') {
            find(cmd);
        }
    }
    return 0;
}