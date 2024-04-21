// 从字符串中找出OvO组合的个数，下标不重复，可能有问号，?可以代表任意字符
// 例如，OvO=1，OOvOO=4，O?vOO=6，?????=10

// 思路： 数学思维，时间On，空间On
// 1. 通过观察不难发现OOvOO其实就是前面的2种搭配后面的2种
// 2. 因此，对于每个v，只需要计算他前面的o的个数和后面的o的个数相乘即可
// 3. 对于每个为v或者？的位置，统计前后O和？的个数
// 4. 就可以保证下标不重复的找出所有ovo的组合个数

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {   //O?vOO
    string s = "?????";
    int n = s.size();
    int cnt = 0;
    for (int i = 0; i < n; ++ i) {
        char& c = s[i];
        if (c == '?' || c == 'O') {
            ++ cnt;             //先统计所有O和？的个数
        }
    }
    vector<int> record_left(n, 0);  //记录当前位置左边的O和？的个数
    vector<int> record_right(n, 0); //记录当前位置右边的0和？的个数，这个其实可以不要
    record_left[0] = s[0] == 'O' || s[0] == '?' ? 1 : 0;
    record_right[0] = cnt - record_left[0];
    for (int i = 1; i < n; ++ i) {
        char& c = s[i];
        if (c == 'O' || c == '?') { //更新当前位置前面的o和？的个数
            record_left[i] = record_left[i - 1] + 1;
        } else {
            record_left[i] = record_left[i - 1];
        }
        record_right[i] = cnt - record_left[i]; //更新后面的o和？的个数
    }
    long long res = 0;
    for (int i = 0; i < n; ++ i) {
        if (s[i] == 'v') {  //如果当前位置是v，则计算当前组合的结果
            res += (record_left[i]) * record_right[i];
        } else if (s[i] == '?') {   //如果是问号，要把当前位置的问号减去再计算
            res += (record_left[i] - 1) * (record_right[i]);
        }
    }
    cout << res << endl;
    return 0;
}