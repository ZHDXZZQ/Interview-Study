/*
    思路： bfs，时间Omn，空间Omn
    1. 利用队列广度优先搜索，先到边界的就是最近的路，返回层数即为步数
*/

class Solution {
public:
    using PII = pair<int, int>;
    int dx[4] = {0, 0, 1, -1};  // 四个方向
    int dy[4] = {1, -1, 0, 0};
    
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();
        queue<PII> q;
        q.push({entrance[0], entrance[1]}); // 插入起点
        maze[entrance[0]][entrance[1]] = '+';   // 将起点变为不可达，避免二次访问重复路径
        int res = -1;   // 起点为初始，因此设为-1
        while (q.size()) {  // 没有遍历完，则进入该层遍历
            ++ res;
            int cnt = q.size(); // 记录当前层的节点数
            while (cnt --) {    // 当前只走了一步，仅遍历该层
                int i = q.front().first;    // 每次取出一个节点
                int j = q.front().second;
                if ((i == 0 || j == 0 || i == m - 1 || j == n - 1) && res > 0) {    // 如果到了边界且不是起点，则这就是最短路径
                    return res;
                }
                q.pop();
                for (int k = 0; k < 4; ++ k) {  // 否则对该节点的四个方向做判断
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && y >= 0 && x < m && y < n && maze[x][y] == '.') {  // 如果没有越界且不是墙，则把下一层可走的路径插入队列中
                        maze[x][y] = '+';   // 将其变成墙
                        q.push(make_pair(x, y));
                    }
                }
            }
        }
        return -1;
    }
};