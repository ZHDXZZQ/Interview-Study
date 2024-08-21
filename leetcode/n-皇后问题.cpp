// 思路： 回溯，时间On！，空间On
// 1. 搜索每个位置，只需要考虑当前位置的行、列和斜线上是否有已被占位
// 2. 我们可以按行搜，每行必有一个棋子；每行按列搜，因此只需要考虑其对角线和列上是否有棋子即可
// 3. 第一行搜n个，第二行搜n-1个位置，第三行搜n-2个位置，因此时间On！
// 4. 对于如何存储某一斜线上是否有棋子，可以假设数组是一个坐标系，利用y=x+k和y=-x+k两条直线可以表示所有的斜线。
// 对于斜率为1的直线要考虑截距为负的情况，因此计算时可以统一加一个偏移量

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
vector<bool> inf_col;       // 该列是否有棋子
vector<bool> postive_k;     // 该斜率为正的斜线上是否有棋子
vector<bool> negative_k;    // 该斜率为负的斜线上是否有棋子
// 以0，0为原点，向右为x轴，向下为y轴，做直线
vector<string> res;     // 当前棋盘的情况

void dfs(int row) { // 计算每行的情况，dfs并回溯
    if (row == n) { // 本轮计算完毕
        for (auto& str : res) { // 打印结果
            cout << str << endl;
        }
        cout << endl;
        return ;
    }

    for (int i = 0; i < n; ++ i) {  // 遍历该行的每一列
        if (!inf_col[i] && !postive_k[row + i] && !negative_k[row - i + n]) {   // 如果该格子所在的列即两方向的斜线都没有棋子
            inf_col[i] = postive_k[row + i] = negative_k[row - i + n] = true;   // 摆上棋子
            res[row][i] = 'Q';  
            dfs(row + 1);           // 继续搜索后面的行
            res[row][i] = '.';      // 回溯
            inf_col[i] = postive_k[row + i] = negative_k[row - i + n] = false;  // 拿走棋子，开始遍历本行的下一列的情况
        }
    }
}

int main() {
    cin >> n;
    inf_col = vector<bool>(n, false);
    postive_k = vector<bool>(n, false);
    negative_k = vector<bool>(n, false);
    res = vector<string>(n, string(n, '.'));    // 初始化棋盘和各位情况
    dfs(0);
    return 0;
}