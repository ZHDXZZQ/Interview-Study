/*
    把一个数N写成：N = (p1^x1)(p^x2)(p3^x3)…(pk^xk)，其中pi为质数。
    则N的约数个数为：(x1+1)(x2+1)(x3+1)…(xk+1)
    比如12，可以写成1*2*2*3 = 2^2 * 3^1，拆分因数即为1，2，3，4，6，12
    可以理解成算组合，比如1*2=2，2*2=4，2*3=6，2*2*3=12，1，2，3也分别是因数
    时间On根号n，空间On，不用理解了，直接记住吧
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>

const int mod = 1e9 + 7;

using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<int, int> primes;     // key为一个质数，value为这个质数的指数，即出现的次数
    while (n --) {
        int x;
        cin >> x;

        for (int i = 2; i <= x / i; ++ i) { // 记录当前数字的质数
            while (x % i == 0) {
                x /= i;
                ++ primes[i];
            }
        }

        if (x > 1) {    // 大质数
            ++ primes[x];
        }
    }

    long long res = 1;
    for (auto& prime : primes) {
        res  = res * (prime.second + 1) % mod;  // 将所有数的乘积的所有质数的指数相乘，即为答案
    }
    cout << res;
    return 0;
}