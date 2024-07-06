/*
    思路：bfs，时间
    注意bfs是每次扩展都是往后走一步，最先到达的就是最短的，直接输出步长即可
    dfs是要每次都走到头，记录当前步数，再依次退回回溯找下一条路，相对耗费时间更长
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using PII = pair<int, int>; // = typedef pair<int, int> PII; = #define PII pair<int, int>

vector<vector<int>> nums;
queue<vector<PII>> q;   // PII也可以用一个vector<int>(2)代替

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int m, n;
int res = -1;   // 步长初始化为-1，因为计算的是从0格到最后格子跳跃的步数，而不是格子数

void bfs() {
    while (!q.empty()) {    // 如果当前队列不空，说明还能遍历
        ++ res; // 步长+1
        auto vec = q.front();   // 取出下一层的全部网格，都是走一步到达的
        q.pop();
        vector<PII> next_vec;
        for (auto& pii : vec) { // 遍历这一步能走到的所有节点
            int x = pii.first;
            int y = pii.second;
            if (x == m - 1 && y == n - 1) { // 如果有一个到达了终点，则直接结束，这就是最短的
                cout << res << endl;
                return;
            }
            for (int k = 0; k < 4; ++ k) {  // 向4个方向遍历
                int i = x + dx[k];
                int j = y + dy[k];
                if (i >= 0 && j >= 0 && i < m && j < n && nums[i][j] == 0) {    // 如果此路可走
                    next_vec.push_back({i, j}); // 则下一步能到达的格子插入这个节点
                    nums[i][j] = 1; // 该格子标记已走过，后续就算别的路能走到也无所谓了，因为这就是最近的能走到这个格子的路径
                }   
            }
        }
        if (!next_vec.empty()) {    // 如果下一层还有能到达的节点，则把下一步能到的所有节点再插入队列。题目规定能走到结尾，所以这个可以不判断
            q.push(next_vec);
        }
    }
}

int main() {
    cin >> m >> n;
    q.push(vector<PII>(1, make_pair(0, 0)));    // 初始化插入0，0点起点
    nums = vector<vector<int>>(m, vector<int>(n));
    for (int i = 0; i < m; ++ i) {  // 初始化构建网格
        for (int j = 0; j < n; ++ j) {
            cin >> nums[i][j];
        }
    }
    nums[0][0] = 1; // 标记0，0已走过
    bfs();
    return 0;
}