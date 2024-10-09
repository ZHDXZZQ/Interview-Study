/*
    思路： 这个版本只对奇数位置的数字进行异或，判断是否有胜利的策略。时间On，空间O1
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;  // 定义常量 N，表示输入数字的最大数量

int main() {
    int n;
    scanf("%d", &n);  // 输入 n，表示输入的数字个数

    int res = 0;  // 初始化异或结果
    for (int i = 1; i <= n; ++ i) {  // 循环遍历 n 个数
        int x;
        scanf("%d", &x);  // 读取每个数字 x
        if (i & 1) {
            res ^= x;  // 只对奇数位置的数字进行异或运算
        }
    }

    // 判断异或结果并输出相应结果
    if (res) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}
