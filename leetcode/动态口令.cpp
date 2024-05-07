/*
    思路： 模拟，时间On，空间O1
    1. 把尾部不动的字符放入结果串
    2. 把面前移动的字符插入到结果串后面
*/

class Solution {
public:
    string dynamicPassword(string password, int target) {
        int n = password.size();
        auto res = password.substr(target, n - target);
        for (int i = 0; i < target; ++ i) {
            res += password[i];
        }
        return res;
    }
};