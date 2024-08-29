/*
    思路： bfs，时间O9！，约36w，即10的5次方；空间O9！，队列最坏情况需要都存储。
    具体看注释
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

const int dx[4] = {1, -1, 0, 0};    // 存储x可移动的四个方向
const int dy[4] = {0, 0, 1, -1};

int bfs(string start) {
    queue<string> q;
    unordered_map<string, int> dist;    // 存储每个当前字符串由开始变化来花费的次数

    q.push(start);
    dist[start] = 0;
    string end = "12345678x";   // 目标串
    
    while (q.size()) {
        string state = q.front();
        q.pop();
        if (state == end) { // 如果当前队头就是目标串，返回当前队头所用的距离
            return dist[state];
        }
        int distance = dist[state]; // 记录当前步数
        int pos = state.find('x');  // 找到x所在下标
        int x = pos / 3;    // 抽象成3x3的棋盘的位置坐标
        int y = pos % 3;

        for (int i = 0; i < 4; ++ i) {
            int a = x + dx[i];  // 往四个方向交换
            int b = y + dy[i];
            if (a >= 0 && b >= 0 && a < 3 && b < 3) {
                swap(state[a * 3 + b], state[pos]); // 交换位置，将坐标变成一维序列
                if (!dist.count(state)) {   // 如果这种情况以前还没有出现过
                    dist[state] = distance + 1; // 将其存入队列进行bfs，记录这个情况的步数
                    q.push(state);
                }
                swap(state[a * 3 + b], state[pos]); // 交换回来，开启下一轮交换
            }
        }
    }
    return -1;  // 到不了结果，返回-1
}

int main() {
    char c[2];
    string start;
    for (int i = 0; i < 9; ++ i) {  // 输入初始状态的9个字符
        cin >> c;
        start += *c;
    }
    cout << bfs(start) << endl;
    return 0;
}