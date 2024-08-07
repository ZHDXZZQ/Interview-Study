/*
    思路： 对于上一题约数个数，每个约数都是由选择多个质数与另外的质数相乘构成的
    因此每次计算每个质数的所有可能的数值，相加起来，再乘起来，就构成了所有可能的集合
    比如 N = (p1^x1)(p2^x2)(p3^x3)…(pk^xk)
    其所有的质数即为每个数字p1和p2等等，选择n个相乘
    举例(p1^0 + p1^1 + p1^2) * (p2^0 + p2^1 + p2^2)就是每种组合都包含
    所以对于每个质数都求n次方的和再全部相乘即可
    时间On根号n，空间On
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <math.h>

const int mod = 1e9 + 7;

using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> primes;
    long long res = 1;
    while (n --) {  // 求所有数的质数及其个数
        int x;
        cin >> x;
        for (int i = 2; i <= x / i; ++ i) {
            while (x % i == 0) {
                x /= i;
                ++ primes[i];
            }
        }
        if (x > 1) {
            ++ primes[x];
        }
    }
    for (auto& it : primes) {   // 计算每个质数的n次方的和再相乘
        long long temp = 0;
        int cnt = it.second;
        int num = it.first;
        long long power = 1;
        for (int i = 0; i <= cnt; ++ i) {
            temp = (temp + power) % mod;    //不能用pow，因为返回的是double，变成long long会损失精度
            power = (power * num) % mod;
        }
        res = res * temp % mod;
    }
    cout << res;
    return 0;
}