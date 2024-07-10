/*
    思路： 单链表，可以用数组记录，也可以用umap记录，时间O1，空间On
*/

#include <iostream>
#include <unordered_map>

using namespace std;

struct node {
    node* next;
    int val;
    node() : next(nullptr), val(-1) {}
    node(int v) : next(nullptr), val(v) {}
    node(node* t, int v) : next(t), val(v) {}
}*head; // 头节点
int pos = 1;    // 记录当前插入的节点是第几个
unordered_map<int, node*> umap; // 记录每个插入的几点的编号

void H(int value) {
    auto new_node = new node(value);    // 创建新节点
    umap[pos] = new_node;
    ++ pos;
    auto next = head->next; // 插入到头节点之后，头插法，倒链
    head->next = new_node;
    new_node->next = next;
}

void D(int k) {
    auto k_node = umap[k];  // 找到第k个插入的节点，删除后面的节点
    auto next = k_node->next;
    k_node->next = next->next;
    delete next;
}

void I(int k, int x) {
    auto k_node = umap[k];  // 找到第k个插入的节点，在其后面插入值为x的新节点
    auto next = k_node->next;
    auto new_node = new node(next, x);
    umap[pos] = new_node;
    ++ pos;
    k_node->next = new_node;
}

int main() {
    head = new node();
    umap[0] = head;
    int m;
    cin >> m;
    string cmd;
    while(m --) {
        cin >> cmd;
        if (cmd == "H") {
            string num;
            cin >> num;
            int k = stoi(num);
            H(k);
        } else if (cmd == "D") {
            string num;
            cin >> num;
            int k = stoi(num);
            D(k);
        } else if (cmd == "I") {
            string num1, num2;
            cin >> num1 >> num2;
            int k = stoi(num1);
            int x = stoi(num2);
            I(k, x);
        }
    }
    while (head->next) {
        cout << head->next->val << " ";
        head = head->next;
    }
    return 0;
}