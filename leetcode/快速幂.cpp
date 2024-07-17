//思路： 基础算法：快速幂qmi， 时间Ologn，空间O1
//1. 如果要求x的19次，我们可以理解为求 x的16次* x的2次* x，而原本我们需要乘19次
//2. 对于n，我们拆分成2进制，每次需要乘的时候乘入即可
//3. 举例，求3的19次，其实我们只需要3的16次，3的2次和3的1次
//4. 因此，我们对19拆分成二进制10011，第一次我们x3，然后3x3=9
//5. 第二次，我们x9，然后9x9=81
//6. 第三次，二进制为0，不乘，但是基数再平方，即81x81=3^8
//7. 第四次，二进制还是为0，不乘，基数平方，得3^16
//8. 第五次，二进制为1，乘3^16，结束
// 性质：(a * b) % p = ((a % p) * (b % p)) % p 
// (a ^ b) % p = ((a % p) ^ b) % p

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    long long a, b, p;
    while (n --) {
        cin >> a >> b >> p;
        long long res = 1;
        for (int i = b; i > 0; i /= 2) {
            if (i & 1 == 1) {
                res = res * a % p;  // 不能写成res *= a % p，会优先计算后面的部分再计算*=
            }
            a = a * a % p;  // 这里取模竟然不影响结果。
        }
        cout << res << endl;
    }
    return 0;
}