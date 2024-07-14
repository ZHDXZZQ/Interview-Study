/*
    质数：素数：在大于1的整数中，只包含1和本身这两个约数
    思路： 试除法，时间On√n，空间O1
*/

#include <iostream>

using namespace std;

void is_prime(int& num) {
    if (num < 2) {  // 1不是质数
        cout << "No" << endl;
        return;
    }
    for (int i = 2; i <= num / i; ++ i) {   // 从2开始，一直到根号num，因为再往上就是重复计算，这样写避免溢出，比sqrt快
        if (num % i == 0) { // 如果有数能除尽，则不是质数
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;  // 否则是质数
}

int main() {
    int n;
    cin >> n;
    while (n --) {
        int num;
        cin >> num;
        is_prime(num);
    }
    return 0;
}