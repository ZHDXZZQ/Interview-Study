/*
    思路： 利用vector存储大数更方便，按乘法规则模拟，时间On^2，空间On（也可以O1）
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    vector<int> res(a.size() + b.size(), 0);    // 结果数组，顺序存储每一位结果值
    int len_a = a.size();
    int len_b = b.size();
    for (int a_ptr = len_a - 1; a_ptr >= 0; --a_ptr) {  // 对于乘法，需要每一位乘上另一个的所有位，同时考虑进位
        for (int b_ptr = len_b - 1; b_ptr >= 0; --b_ptr) {
            res[a_ptr + b_ptr + 1] += (a[a_ptr] - '0') * (b[b_ptr] - '0');  // 两数尾部对齐，开始相乘
            res[a_ptr + b_ptr] += res[a_ptr + b_ptr + 1] / 10;  // 当前位相乘结果进位加到前一位上
            res[a_ptr + b_ptr + 1] %= 10;   // 当前位只保留个位
        }
    }
    string res_num;
    for (int i = 0; i < res.size(); ++i) {  // 遍历所有位
        if (res_num.empty() && res[i] == 0 && i < res.size() - 1) { continue; } // 去掉所有前导0
        res_num += res[i] + '0';    // 把每位存入结果中
    }
    cout << res_num << endl;
    return 0;
}