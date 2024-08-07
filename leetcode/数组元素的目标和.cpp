/*
    思路： 双指针夹逼，时间Om+n，空间O1
    1. 一个数组从小往大遍历，一个数组从大往小遍历
    2. 优先移动大到小的指针，因为小的变大，加大的只会更大
    3. 当两数之和小于等于目标值时，判断是否为目标值
    4. 然后移动小的指针变大，再继续移动大指针判断
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<int> A(n);
    vector<int> B(m);
    for (int i = 0; i < n; ++ i) {
        cin >> A[i];
    }
    for (int i = 0; i < m; ++ i) {
        cin >> B[i];
    }
    for (int ptr_a = 0, ptr_b = m - 1; ptr_a < n; ++ ptr_a) {
        while (ptr_b >= 0 && A[ptr_a] + B[ptr_b] > x) { // 先移动大的
            -- ptr_b;
        }
        if (ptr_b >= 0 && A[ptr_a] + B[ptr_b] == x) {   // 判断是否为答案
            cout << ptr_a << ' ' << ptr_b;
            return 0;
        }
    }    
    return 0;
}