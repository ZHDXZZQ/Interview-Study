/*
    思路： 并查集，时间Onm，空间On
*/

#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> root;   // 负数代表这目前是该集合的根节点，绝对值代表集合的节点数量
// 正数代表的是其集合中的父节点
int a, b;

int find(int x) {
    // 路径压缩：让所有访问的节点直接连接到根节点
    if (root[x] < 0) {  // x就是根节点
        return x;
    }
    return find(root[x]);   // 递归查找
}

void add(int a, int b) {
    int root_a = find(a);   // 找到a和b的集合根节点
    int root_b = find(b);
    
    // 按秩合并：将较小集合合并到较大集合中
    if (root_a != root_b) { // 如果根节点相同，无需add
        if (root[root_a] < root[root_b]) {  // 看看哪个集合的节点数更少
            root[root_a] += root[root_b];   // 节点数量先加过去
            root[root_b] = root_a;  // 将节点数更少的节点融合到另一个集合中
        } else {
            root[root_b] += root[root_a];
            root[root_a] = root_b;
        }
    }
}

void is_together(int a, int b) {
    if (find(a) == find(b)) {   // 判断a和b是否同属于一个根节点
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

void get_cnt(int x) {
    // 输出当前集合的大小
    cout << -root[find(x)] << endl; // 根节点的绝对值就是集合的节点数
}

int main() {
    cin >> n >> m;
    root = vector<int>(n + 1, -1);
    while (m--) {
        string ops;
        cin >> ops;
        if (ops == "C") {
            cin >> a >> b;
            add(a, b);
        } else if (ops == "Q1") {
            cin >> a >> b;
            is_together(a, b);
        } else if (ops == "Q2") {
            cin >> a;
            get_cnt(a);
        }
    }
    return 0;
}
