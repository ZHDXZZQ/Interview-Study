/*
    思路： 分解质因数，时间On根号x，空间O1
*/

#include <iostream>

using namespace std;

void divide(int x) {
    for (int i = 2; i <= x / i; ++ i) { // 从2开始，到根号即可
        if (x % i == 0) {   // 如果当前数字使其一个因数，它也一定是一个质数，因为从2开始，每个质数的倍数都已经被除完了
            int cnt = 0;
            while (x % i == 0) {    // 将其所有的该质因子除尽
                x /= i;
                ++ cnt;     // 记录个数
            }
            cout << i << " " << cnt << endl;
        }
    }
    if (x > 1) {    // 如果剩余的数字不是1，则这是其一个质因数
        cout << x << " 1" << endl;
    }
    return;
}

int main() {
    int n;
    cin >> n;
    while (n --) {
        int num;
        cin >> num;
        divide(num);
        cout << endl;
    }
    return 0;
}