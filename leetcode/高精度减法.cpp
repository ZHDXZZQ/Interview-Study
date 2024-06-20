/*
    思路： 高精度减法，主要注意减法的规则即可，同时注意字符和数字之间的转换，时间On，空间O1（不包含结果存储）
    1. 相较于高精度加法，这里需要额外注意判断两个数的大小并调换顺序，实现大减小，最后再确定符号
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    string res;
    int SF = 0; // 正负号
    int CF = 0; // 借位
    if (a.length() < b.length()) {  // 判断a和b的大小关系，为什么这里字符串的正整数比较不能直接比呢
        SF = 1;     // 如果b更大，则置结果符号为负，并交换a和b，保证a-b是正数
        swap(a, b);
    } else if (a.length() == b.length()) {  // 如果二者长度一样，则要逐位比较大小
        int len = a.length();
        for (int i = 0; i < len; i++) {
            if (a[i] < b[i]) {  // 如果每位都相同，则要一直比到底。直到不同的那位
                SF = 1; // 如果不同的这位是a的小，那么交换二者，并置负号
                swap(a, b);
                break;
            } else if (a[i] > b[i]) {   // 如果不同的这位是b更小，那么无需继续比较，也无需变换，继续比较则可能出错
                break;
            }
        }
    }
    int len_a = a.size();
    int len_b = b.size();
    int a_ptr = len_a - 1;  // 从后往前减，保证末位对齐
    int b_ptr = len_b - 1;
    while (a_ptr >= 0) {  // 如果a还没减完，则继续，先减完的那个一定是b，按0算
        int num_a = a[a_ptr --] - '0';    // a一定没减完，字符转数字，记得-'0
        int num_b = b_ptr >= 0 ? b[b_ptr --] - '0' : 0; // 如果b先减完了，则按0算
        int num = num_a - num_b - CF;   // 计算当前位的差，CF是借位，如果有则-1
        if (num < 0) {  // 如果当前位小于0，则要借位，最小为0被借位1，再-9，则为-10
            num += 10;
            CF = 1; // 向前借位1
        } else {
            CF = 0; // 否则的话不借位
        }
        res.push_back(num + '0');   // 插入当前位结果，注意此时结果顺序相反，对于字符的处理都要+-'0
    }
    while (res.back() == '0' && res.length() > 1) { // 去除前导0，但如果全0要保留1个0
        res.pop_back();
    }
    if (SF == 1) {  // 如果是负数，则加个负号，此时可以满足小数-大数的结果
        res += '-';
    }
    reverse(res.begin(), res.end());    // 反转结果，因为是从后往前减，所以结果是反的
    cout << res << endl;
    return 0;
}