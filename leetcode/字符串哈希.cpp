/*
    思路：字符串哈希，也可以substr更简单。
    时间On， 空间On
    1. 将字符计算前缀值，每个字符按从左往右算位权，基数为131，取2的64次方余数，利用无符号longlong自动取余
    2. 这样在计算区间hash时，通过计算前缀差值的加权值判断是否相同即可
    从左往右为高位到低位
*/

#include <iostream>
#include <vector>
// #include <math.h>

using namespace std;

int n, m;
int l1, r1, l2, r2;
string str;
// const int Q = pow(2, 64);        // 取余
const int p = 131; // or 13331      // 基数
vector<unsigned long long> str_hash;    // 记录前i位字符的哈希值
vector<unsigned long long> power;       // 记录第i位的位权

unsigned long long get(int l, int r) {  // 获取l到r之间的子串的哈希值，要对前面的部分加权，因为对于多位的清空来说，前面的值权值更大，但是对于少位的来说权值更小，要补齐
    return str_hash[r] - str_hash[l - 1] * power[r - l + 1];
}

int main() {
    std::cin >> n >> m;
    std::cin >> str;
    str = ' ' + str;
    str_hash = vector<unsigned long long>(n + 1, 0);
    power = vector<unsigned long long>(n+ 1, 0);
    power[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        str_hash[i] = str_hash[i - 1] * p + str[i]; // 前面的位升权，加上该位值
        power[i] = power[i - 1] * p;    // 更新每位位权
    }
    while (m --) {
        cin >> l1 >> r1 >> l2 >> r2;
        if (get(l1, r1) == get(l2, r2)) {   // 判断二者间的哈希值是否相同
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}