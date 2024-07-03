// 哈希map，底层为哈希拉链
// 这里为粗略实现，后续再改进
// https://www.acwing.com/problem/content/842/
#include <iostream>
#include <vector>
#include <sstream>

struct List {
    int key;
    int value;
    List* next;
    List(int k) : key(k), value(1), next(nullptr) {}
};

using namespace std;

const int M = 1e5;
const int C = 1e9;

int main() {
    vector<List*> umap(M, nullptr);
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符

    while (n--) {
        string line;
        getline(cin, line);

        istringstream iss(line);
        char cmd;
        int k;
        iss >> cmd >> k;

        int index = (k + C) % M;
        if (cmd == 'I') {
            if (umap[index] == nullptr) {
                umap[index] = new List(k);
            } else {
                auto temp = umap[index];
                bool found = false;
                while (temp) {
                    if (temp->key == k) {
                        ++temp->value;
                        found = true;
                        break;
                    }
                    if (temp->next == nullptr) { break; }
                    temp = temp->next;
                }
                if (!found) {
                    temp->next = new List(k);
                }
            }
        } else if (cmd == 'Q') {
            bool found = false;
            if (umap[index] != nullptr) {
                auto temp = umap[index];
                while (temp) {
                    if (temp->key == k) {
                        cout << "Yes" << endl;
                        found = true;
                        break;
                    }
                    temp = temp->next;
                }
            }
            if (!found) {
                cout << "No" << endl;
            }
        }
    }

    // 释放动态分配的内存
    for (auto node : umap) {
        while (node) {
            auto temp = node;
            node = node->next;
            delete temp;
        }
    }

    return 0;
}
