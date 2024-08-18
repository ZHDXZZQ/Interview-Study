/*
    思路： 佛洛依德算法，以中间节点查找最短路径
    时间On^3，空间On^2
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
const int INF = 1e9;


void init(vector<vector<int>>& dis) {   // 初始化，同节点间距离为0，不同节点间初始化为正无穷
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i == j) {
                dis[i][j] = 0;
            } else {
                dis[i][j] = INF;
            }
        }
    }
}

void floyd(vector<vector<int>>& dis) {  // 以最外层为中间节点，遍历最短路径
    for (int mid = 0; mid < n; ++ mid) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                dis[i][j] = min(dis[i][j], dis[i][mid] + dis[mid][j]);
            }
        }
    }
}

int main() {
    cin >> n >> m >> k;
    vector<vector<int>> dis(n, vector<int>(n));
    init(dis);
    while(m --) {
        int a, b, w;
        cin >> a >> b >> w;
        dis[a - 1][b - 1] = min(dis[a - 1][b - 1], w);  // 更新某一结点的权值
    }
    floyd(dis);
    while (k --) {
        int a, b;
        cin >> a >> b;
        int res = dis[a - 1][b - 1];
        if (res >= INF / 2) {   // 如果为正无穷则无路
            puts("impossible");
        } else {
            printf("%d\n", res);
        }
    }
    return 0;
}