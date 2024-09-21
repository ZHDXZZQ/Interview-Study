/*
    思路： 差分矩阵，时间Omn，空间Omn
    1. 差分矩阵是原矩阵的前缀和逆矩阵，即原矩阵是差分矩阵的前缀和
    2. 即对于ij来说，将0~i，0~j上的所有数字相加，得到的就是原矩阵该位置的数字
    3. 因此我们只需要维护差分矩阵就可以求出原矩阵
*/

#include <iostream>
#include <vector>

using namespace std;

// 定义全局变量 n, m, q 分别表示矩阵的行数、列数和操作次数
int n, m, q;

// 定义二维数组 nums 用于存储初始矩阵，premix 用于存储二维差分矩阵
vector<vector<int>> nums;
vector<vector<int>> premix;

// 插入函数：用于在二维差分矩阵中对指定区域进行加减操作
void insert(int& x1, int& y1, int& x2, int& y2, int& c) {
    // 在左上角 (x1, y1) 位置加上 c
    premix[x1][y1] += c;    // 代表x1往下，y1往右的右下方块的值全部+c
    
    // 在 (x2 + 1, y1) 位置减去 c，防止超出 x2 区域
    premix[x2 + 1][y1] -= c;    // 超出范围的部分-c
    
    // 在 (x1, y2 + 1) 位置减去 c，防止超出 y2 区域
    premix[x1][y2 + 1] -= c;    // 超出范围的部分-c
    
    // 在 (x2 + 1, y2 + 1) 位置加上 c，抵消两次减去的部分
    premix[x2 + 1][y2 + 1] += c;    // 最右下角被连续减去两次，加回来一次，这样相当于非目标区域内，值不变
}

int main() {
    // 输入 n (行数), m (列数), q (操作数)
    cin >> n >> m >> q;

    // 初始化 nums 和 premix 为 (n + 2) * (m + 2) 的二维数组，防止越界操作
    nums = vector<vector<int>>(n + 2, vector<int>(m + 2, 0));
    premix = vector<vector<int>>(n + 2, vector<int>(m + 2, 0));

    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> nums[i][j];      // 输入初始矩阵的每个元素，存储到 nums 中
            insert(i, j, i, j, nums[i][j]);     // 将初始矩阵的每个值通过差分法插入到 premix 中
        }
    }

    // 处理 q 次区间加法操作，更新差分矩阵
    while (q--) {
        int x1, y1, x2, y2, c;
        // 输入操作的左上角坐标 (x1, y1)，右下角坐标 (x2, y2) 和增量 c
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        // 在差分矩阵中进行区间更新
        insert(x1, y1, x2, y2, c);
    }

    // 通过差分矩阵 premix 还原出结果矩阵
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // 根据二维前缀和公式进行累加
            premix[i][j] += premix[i - 1][j] + premix[i][j - 1] - premix[i - 1][j - 1];
            // 输出每个位置的最终值
            cout << premix[i][j] << " ";
        }
        cout << endl; // 输出每行后换行
    }    

    return 0;
}
