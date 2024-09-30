/*
    思路：线性筛法：埃拉托斯特尼筛法。时间Ologlogn，空间On
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010; // 最大值，设定素数数组和标记数组的大小

int primes[N], cnt; // primes 数组存储素数，cnt 记录素数的数量
bool st[N];         // st 数组用于标记合数（false 表示是素数，true 表示是合数）

// 获取小于等于 n 的所有素数
void get_primes(int n) {
    for (int i = 2; i <= n; i++) {  // 遍历 2 到 n 的每个数
        if (!st[i]) { // 如果 i 还未被标记，说明 i 是素数
            primes[cnt++] = i; // 将 i 存入 primes 数组，并增加素数计数
        }
        for (int j = 0; primes[j] <= n / i; ++ j) { // 遍历已找到的素数
            st[primes[j] * i] = true; // 标记 i * primes[j] 为合数
            if (i % primes[j] == 0) {   // 如果 i 被 primes[j] 整除，停止当前循环
                break;
            }
        }
    }
}

int main() {
    int n;
    cin >> n; // 输入 n

    get_primes(n); // 获取小于等于 n 的素数

    cout << cnt << endl; // 输出素数的数量

    return 0;
}


/*  
// 思路： 朴素筛法

#include <iostream>
#include <algorithm>

using namespace std;

const int N= 1000010;

int primes[N], cnt;
bool st[N];

void get_primes(int n) {
    for (int i = 2; i <= n; ++ i) {
        if (st[i]) { continue; }
        primes[cnt ++ ] = i;
        for (int j = i + i; j <= n; j += i) {
            st[j] = true;
        }
    }
}

int main() {
    int n;
    cin >> n;

    get_primes(n);

    cout << cnt << endl;

    return 0;
}
*/