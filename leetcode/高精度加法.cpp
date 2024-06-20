/*
    思路： 高精度计算，因为int无法存储，需要对每一位单独计算，特别注意计算规则即可，时间On，空间O1
*/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;  // 输入两个数a和b
    string res;
    int m = a.size();
    int n = b.size();
    int a_ptr = m - 1;  // 对两个数从后往前对其逐位进行加法
    int b_ptr = n - 1;
    int CF = 0; // 是否进位标志
    while (a_ptr >= 0 || b_ptr >= 0) {  // 如果两个数还有没相加完的
        int num_a = 0;      // 初始化为0，如果有一个数当前位为空，直接按0计算即可
        int num_b = 0;
        if (a_ptr >= 0) {        // 找到a和b的最低位，即对其末位相加，只有当前还没加完时，才赋值
            num_a = a[a_ptr --] - '0';
        }
        if (b_ptr >= 0) {
            num_b = b[b_ptr --] - '0';
        }
        int num = num_a + num_b;    // 计算当前位的和
        if (CF == 1) {  // 如果上一位有进位，此时+1，num最大9+9+1=19
            ++ num;
        }
        if (num >= 10) {    // 如果本位和大于9，则进位
            CF = 1;
            num -= 10;
        } else {    // 否则下一位加法不进位
            CF = 0;
        }
        res += num + '0';   // 将本位和加入结果中
    }
    if (CF == 1) {  // 如果全部加完后，还有1个进位，则额外补充1个1
        res += '1';
    }
    reverse(res.begin(), res.end());    // 将结果翻转，即为正常顺序
    cout << res << endl;
    return 0;
}