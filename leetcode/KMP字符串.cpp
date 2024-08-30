// 思路： KMP算法， 时间Om+n，空间On，其中n为模式串的长度，m为主串的长度

#include <cstring>
#include <iostream>

using namespace std;

const int N = 100010, M = 1000010;

int n, m;
char s[M], p[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1;    // 字符串前面留一格
    int next[N];
    memset(next, 0, N);
    // next 数组用于记录模式串中每个位置之前的字符串的最长相同前后缀长度。
    // 初始化变量 i 从 2 开始，j 初始化为 0，j 表示当前匹配的前缀长度。
    // 当 p[i] != p[j + 1] 时，不匹配，则 j 回退到 next[j]。
    // 当 p[i] == p[j + 1] 时，表示匹配，则 j 递增，表示当前匹配长度增加。
    // 更新 next[i] 为 j，即模式串第 i 位之前的最长相同前后缀长度。

    // 计算next数组
    for (int i = 2, j = 0; i <= n; ++ i) {
        while (j && p[i] != p[j + 1]) {
            j = next[j];    // // 回退到上一个最长前后缀的位置
        }
        if (p[i] == p[j + 1]) {
            ++ j;    // 匹配成功，j增加
        }
        next[i] = j;    // // 记录前i个字符的最长相同前后缀长度
    }
    // 遍历主串，使用变量 i 表示当前主串的位置，j 表示当前模式串的位置。
    // 如果当前字符不匹配 s[i] != p[j + 1]，模式串的 j 根据 next 数组回退，减少重复比较。
    // 如果匹配 s[i] == p[j + 1]，则 j 递增，继续比较下一个字符。
    // 当 j == n 时，说明模式串完全匹配，输出匹配起始位置 i - n。
    // 然后 j 根据 next[j] 回退，继续下一轮匹配。
    for (int i = 1, j = 0; i <= m; ++ i) {
        while (j && s[i] != p[j + 1]) {
            j = next[j];     // 如果不匹配，模式串回退
        }
        if (s[i] == p[j + 1]) {
            ++ j;   // 匹配成功，j增加
        }
        if (j == n) {   // 匹配成功，输出位置
            printf("%d ", i - n);
            j = next[j];    // 模式串回退
        }
    }

    return 0;
}