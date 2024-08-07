/*
    思路： 双指针法，时间On+m，空间O1
    1. 两个数组都从头遍历
    2. 只要碰到一致的字符，就共同+1
    3. 否则只给b的指针+1
    4. 因为都是按序来的，所以遍历到的相同的字符也是按序来的
    5. 如果遍历完全了a数组，则是子序列，否则不是。
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; ++ i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++ i) {
        cin >> b[i];
    }
    int ptr_a = 0, ptr_b = 0;
    while (ptr_a < n && ptr_b < m) {
        if (a[ptr_a] == b[ptr_b]) { // 如果当前位置两个字符相同
            ++ ptr_a;   // a中匹配一个
        }
        ++ ptr_b;   // b每次都移动
    }
    if (ptr_a == n) {   // 如果a遍历完全，则是子序列
        cout << "Yes";
    } else {
        cout << "No";
    }
    return 0;
}