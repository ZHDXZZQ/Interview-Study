/*
    会超时，但是思路同编辑距离一致，懒得改了，后面附正确答案
    
    思路： 动态规划， 时间Omn，空间Omn
    dp[i][j]表示word1的前i个字符构成的子串变化成word2的前j个字符构成的子串所需要的步数
    1. 变化的方法就三种，可以大致划分为两种
    2. 第一种为增减行为，即通过加一个字符或者减一个字符可以得到
    3. 第二种为替换行为，即替换一个字符即可得到
    4. 直接对三种的结果取min即可
*/

// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>

// using namespace std;

// bool get_distance(string& a, string& b, int& cnt) {
//     int n = a.size(), m = b.size();
//     a = " " + a;
//     b = " " + b;
//     vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));
//     for (int i = 0; i <= n; ++ i) { // 初始化dp数组，从i个字符变为0个字符肯定是需要删减i步
//         dp[i][0] = i;
//     }
//     for (int j = 0; j <= m; ++ j) { // 从0个字符变成j个字符需要增加j步
//         dp[0][j] = j;
//     }
//     for (int i = 1; i <= n; ++ i) {
//         for (int j = 1; j <= m; ++ j) {
//             dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1; // 判断是删一个和增一个那个更快
//             if (a[i] != b[j]) { // 如果当前位置字符不一样
//                 dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1); // 在上一位都搞好的情况下需要改变一下
//             } else {
//                 dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]); // 否则无需改变
//             }
//         }
//     }
//     return cnt >= dp[n][m];
// }

// void process(int& cnt, vector<string>& strs, string& b) {
//     int res = 0;
//     for (auto& str : strs) {
//         if (get_distance(str, b, cnt)) {
//             ++ res;
//         }
//     }
//     cout << res << endl;
//     return;
// }

// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<string> strs(n);
//     for (int i = 0; i < n; ++ i) { cin >> strs[i]; }
//     for (int i = 0; i < m; ++ i) {
//         string str;
//         int cnt;
//         cin >> str >> cnt;
//         process(cnt, strs, str);
//     }
//     return 0;
// }


#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int N = 15, M = 1010;

int n, m;
int f[N][N];
char str[M][N];

int edit_distance(char a[], char b[])
{
    int la = strlen(a + 1), lb = strlen(b + 1); // 写法，代表记录第一个字符之后的字符串的长度

    for (int i = 0; i <= lb; i ++ ) f[0][i] = i;
    for (int i = 0; i <= la; i ++ ) f[i][0] = i;

    for (int i = 1; i <= la; i ++ )
        for (int j = 1; j <= lb; j ++ )
        {
            f[i][j] = min(f[i - 1][j] + 1, f[i][j - 1] + 1);
            f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[i] != b[j]));
        }

    return f[la][lb];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++ ) scanf("%s", str[i] + 1);  // 写法，代表写到第一个字符之后，即保留一个前置空格

    while (m -- )
    {
        char s[N];
        int limit;
        scanf("%s%d", s + 1, &limit);

        int res = 0;
        for (int i = 0; i < n; i ++ )
            if (edit_distance(str[i], s) <= limit)
                res ++ ;

        printf("%d\n", res);
    }

    return 0;
}