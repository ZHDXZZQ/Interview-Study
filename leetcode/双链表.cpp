/*
    思路： 双链表，时间On，空间On
    1. 用umap存储每个节点是第几个插入的
    2. 利用双链表的定义，需要有一个初始的左右端点
*/

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    Node* perv; // 左右指针
    Node* next;
    int val;    // 当前节点的值
    Node(int v) : perv(nullptr), next(nullptr), val(v) {}
};

int main() {
    int cnt = 1;    // 当前是第几个插入的
    unordered_map<int, Node*> umap; // 也可以用一个tag标记是第几个插入的，但是遍历比较慢
    auto L = new Node(0);
    auto R = new Node(0);
    L->next = R;    // 初始化左右端点
    R->perv = L;
    int n;
    cin >> n;
    cin.ignore();
    while (n--) {   // 输入n条命令
        string cmd;
        getline(cin, cmd);
        int len = cmd.size(); 
        int i = 0;
        while (i < len && cmd[i] != ' ') { ++ i; }  // 找到命令的字符
        string op = cmd.substr(0, i);
        int j = i + 1;
        while (j < len && cmd[j] != ' ') { ++ j; }  // 找到第一个数字
        if (j == len) { // 如果已经读完命令，说明命令是L,R,D的一种
            int num = stoi(cmd.substr(i + 1));  // 获取这个数字
            if (op == "L") {    // 左端插入一个新节点
                auto new_node = new Node(num);
                umap[cnt] = new_node;
                ++ cnt;
                auto first_node = L->next;
                L->next = new_node;
                new_node->perv = L;
                first_node->perv = new_node;
                new_node->next = first_node;
            } else if (op == "R") { // 右端插入一个新节点
                auto new_node = new Node(num);
                umap[cnt] = new_node;
                ++ cnt;
                auto last_node = R->perv;
                R->perv = new_node;
                new_node->next = R;
                last_node->next = new_node;
                new_node->perv = last_node;
            } else {    // 删除第k个节点，需要找到这个节点
                auto del_node = umap[num];
                auto perv_node = del_node->perv;
                auto next_node = del_node->next;
                perv_node->next = next_node;
                next_node->perv = perv_node;
                delete del_node;
            }
        } else {    // 否则的话就是两组数字，指令为IL或IR
            int k = stoi(cmd.substr(i + 1, j - i - 1)); // 获取第一个数字
            int num = stoi(cmd.substr(j + 1));  // 获取第二个数字
            if (op == "IL") {   // 找到第k个节点，在左边插入
                auto cur_node = umap[k];
                auto left_node = cur_node->perv;
                auto new_node = new Node(num);
                umap[cnt] = new_node;
                ++ cnt;
                left_node->next = new_node;
                new_node->perv = left_node;
                cur_node->perv = new_node;
                new_node->next = cur_node;
            } else {    // 在右边插入
                auto cur_node = umap[k];
                auto right_node = cur_node->next;
                auto new_node = new Node(num);
                umap[cnt] = new_node;
                ++ cnt;
                right_node->perv = new_node;
                new_node->next = right_node;
                cur_node->next = new_node;
                new_node->perv = cur_node;
            }
        }
    }
    auto temp = L->next;
    while (temp->next != nullptr) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    return 0;
}