/*
    思路： 二维前缀和，除去初始化矩阵的时间和空间后，时间Oq，空间O1
    1. 初始化记录每个格子为从最左上角格子开始，到本格子围成的长方形的的全部的格子的和
    2. 只需要利用左上、上、左三个已经计算过的格子就能算出
    3. 每次查询时，只需要利用这四个点的格子和的数量关系，直接加减即可
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> nums(n+ 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            int x;
            cin >> x;
            nums[i][j] = x + nums[i - 1][j] + nums[i][j - 1] - nums[i - 1][j - 1];
        }
    }
    int x1, x2, y1, y2;
    while (q --) {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << nums[x2][y2] - nums[x1 - 1][y2] - nums[x2][y1 - 1] + nums[x1 - 1][y1 - 1] << endl;
    }
    return 0;
}