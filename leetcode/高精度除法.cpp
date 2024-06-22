/*
    思路： 模拟除法，b是整型，每次求商可以先得0，后面再去除前导0，时间On，空间On
    （可以优化为O1，不利用额外存储，每次输出当前商并考虑前导0）
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a;
    int b;
    cin >> a >> b;
    vector<int> res;
    int len_a = a.size();
    int r = 0;  // 当前余数
    for (int i = 0; i < len_a; ++ i) {
        int num = a[i] - '0';   // 取出当前数字
        r = r * 10 + num;   // 余数加上当前数一起与b做除法
        res.push_back(r / b);   // 当前结果存入，如果O1空间此时直接输出，记得用一个标志记录前导0
        r %= b; // 求当前余数
    }
    string res_str;  // 可以不用string存储逐个输出
    for (int i = 0; i < res.size(); ++ i) {
        if (res_str.empty() && res[i] == 0 && i < res.size() - 1) { continue; } // 去除前导0
        res_str += res[i] + '0';    // 把商记下来
    }
    cout << res_str << endl << r << endl;   // 同时输出余数
    return 0;
}