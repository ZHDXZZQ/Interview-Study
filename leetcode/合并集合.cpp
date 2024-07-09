/*
    思路： 并查集，时间On，空间On
    1. 每个集合都算作一个树，选择一个节点作为根，根据上级判断该节点是否在同一个集合
*/

#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int pre[N];     // 该节点的父节点
int height[N];  // 以该节点为根的集合的树的高度

void init(int n) {
    for (int i = 0; i <= n; ++ i) {
        pre[i] = i; // 初始化，自己为自己的上级，即为根
        height[i] = 1;  // 高度为1
    }
}

int find(int x) {
    if (pre[x] == x) {  // 如果找到了自己即为自己，则为根
        return x;
    }
    return find(pre[x]);    // 递归查找
}

void is_connection(int x, int y) {
    if (find(x) == find(y)) {   // 如果两节点的根相同，则在一个集合中
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

void join(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {   // 如果两节点在一个集合中，不管
        return;
    }
    if (height[x] > height[y]) {    // 否则判断两个节点所在的集合的高度
        pre[y] = x; // 将矮的插到高的里面，这样避免高度一直增加
    } else {    // x的高度小于或等于y的高度
        if (height[x] == height[y]) {   // 高度相同
            ++ height[y];   // 选择一个集合插入，该集合高度+1
        }
        pre[x] = y; // x接到y下
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    init(n);
    while (m--) {
        string cmd, a, b;
        cin >> cmd >> a >> b;
        int num_a = stoi(a);
        int num_b = stoi(b);
        if (cmd == "M") {
            join(num_a, num_b);
        } else if (cmd == "Q") {
            is_connection(num_a, num_b);
        }
    }
    return 0;
}