/*
    思路： 博弈论， 时间On，空间O1
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;  // 定义常量 N，表示输入数字的最大数量

int main() {
    int n;
    scanf("%d", &n);  // 输入 n，表示输入的数字个数

    int res = 0;
    // 遍历每个数字，执行异或运算
    while (n --) {
        int x;
        scanf("%d", &x);  // 输入每个数字 x
        res ^= x;  // 将每个数字 x 和结果 res 执行异或运算
    }

    // 输出结果：如果异或结果不为 0，输出 "Yes"；否则输出 "No"
    if (res) {
        puts("Yes");
    } else {
        puts("No");
    }

    return 0;
}
