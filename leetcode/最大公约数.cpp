/*
    欧几里得算法：辗转相除法
    时间Ologn，空间Ologn
    证明略
*/

#include <iostream>

using namespace std;

int get_gcd(int a, int b) { // 初始 a 和 b 都是正整数
    if (b == 0) {
        return a;
    }
    return get_gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);
    while (n --) {
        int a, b;
        cin >> a >> b;
        cout << get_gcd(a, b) << endl;
    }
    return 0;
}