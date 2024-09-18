/*
    思路： 并查集+路径压缩，时间On，空间On
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> father, dist;
int n, k;
int d, x, y;

int find(int x) {
    if (father[x] != x) {   // 如果当前存储的father不是根节点，表明被接入了其他集合
        int root = find(father[x]);     // 找到现在真实的根
        dist[x] += dist[father[x]]; // 加上原根到新根的距离
        father[x] = root;   // 路径压缩，直接指向新根
    }
    return father[x];   // 返回新根
}

int main() {
    cin >> n >> k;
    father = vector<int>(n + 1);
    dist = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++ i) {
        father[i] = i;
    }

    int res = 0;
    while (k --) {
        cin >> d >> x >> y;
        if (x > n || y > n) {   // 超过范围直接错
            ++ res;
            continue;
        }
        int root_x = find(x);   // 找到两个的根
        int root_y = find(y);
        if (d == 1) {
            if (root_x == root_y && (dist[x] - dist[y]) % 3 != 0) { // 如果根相同，且距离不差3的倍数，错误
                ++ res;
                continue;
            }
            if (root_x != root_y) { // 如果根不同，说明前没出现过这两个节点的关系，那么默认是对的，构造他们的关系
                father[root_x] = root_y;    // x的根指向y的根
                dist[root_x] = dist[y] - dist[x];   // 更新x到根节点的距离，让x和y是类节点，即相差模3为0
                // 为什么不能是dist[x] - dist[y]？因为是x接到y上，x要计算这个距离，而不是y计算
            }
        } else if (d == 2) {    // 如果是x吃y
            if (root_x == root_y && (dist[x] - dist[y] - 1) % 3 != 0) { // 如果在一个集合中，但是不符合关系，错误
                ++ res;
                continue;
            }
            if (root_x != root_y) { // 如果不是一个根，说明之前没有二者的关系，构造关系
                father[root_x] = root_y;
                dist[root_x] = dist[y] - dist[x] + 1;   // 保证x能吃y，即x到新根的距离比y到新根的距离的差模3为1
                // (dist[x] + n - dist[y] - 1) % 3 == 0 
                // n = dist[y] + 1 - dist[x]
            }
        }
    }
    cout << res << endl;
    return 0;
}