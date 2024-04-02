// 思路： 回溯，时间On！，空间On
// 1. 搜索每个位置，只需要考虑当前位置的行、列和斜线上是否有已被占位
// 2. 我们可以按行搜，每行必有一个棋子；每行按列搜，因此只需要考虑其对角线和列上是否有棋子即可
// 3. 第一行搜n个，第二行搜n-1个位置，第三行搜n-2个位置，因此时间On！

class Solution {
public:
    vector<bool> col, k1, k2;   //col为判断每列是否已有棋子
    //对于任意一个位置，其对角线的方程可以表示成y = x + k和y = -x + k
    //因此对于正向的斜对角线，其k可以写成y - x，但是可能为负数，所以+n
    //对于负向的斜对角线，k可以写成x + y，每个位置都表示该对角线是否有棋子
    int res = 0;
    int cnt;
    
    int totalNQueens(int n) {
        cnt = n;
        col = vector<bool>(n, false);   //初始化标记数组
        k1 = vector<bool>(2 * n, false);
        k2 = vector<bool>(2 * n, false);
        dfs(0); //dfs
        return res;
    }

    void dfs(int raw) {
        if (raw == cnt) {   //如果已经搜完了最后一行，则获得一个答案
            ++ res;
            return;
        }
        for (int i = 0; i < cnt; ++ i) {    //否则的话遍历该行的每列
            if (!col[i] && !k1[raw - i + cnt] && !k2[raw + i]) {
                //针对该位置判断其列和两个斜对角线上是否有棋子，如果没有则进入
                col[i] = k1[raw - i + cnt] = k2[raw + i] = true;
                //将其都置为有，然后dfs
                dfs(raw + 1);
                // 回溯
                col[i] = k1[raw - i + cnt] = k2[raw + i] = false;
            }
        }
    }
};