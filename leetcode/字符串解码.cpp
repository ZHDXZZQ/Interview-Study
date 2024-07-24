/*
    思路： dfs，时间Ores，空间On，其中res为结果的长度，空间为最坏情况下无限嵌套，即字符串s的长度
    1. 对于每个[]区间内的数字，仅有两种情况，纯字母或者嵌套子区间
    2. 因此对于每次dfs，我们都判断是否碰到数字，碰到数字则递归进入下一个子区间，返回时要返回子区间内的字符重复n次的结果
    3. 对于总的区间来说是一样的，我们要么遍历到尾部，要么遍历到]，就可以结束本区间的遍历，计算好子串后跳回到外层
    4. 如果没碰到数字，我们就直接把字母返回；如果碰到数字，就直接计算子区间的字符串，最小的区间一定就是纯字符串
    5. 然后每层出来去计算n次这个子串，最后到最外层。
*/

class Solution {
public:
    string decodeString(string s) {
        int pos = 0;
        string res = dfs(pos, s);
        return res;
    }

    string dfs(int &pos, string &s) {  //递归解决，当前遍历的可能只是一个纯字符的小区间，也可能嵌套区间
        string res;
        while(pos < s.size() && s[pos] != ']') {   //当前区间没到右括号，或者s没到头就循环  
            if(s[pos] >= 'a' && s[pos] <= 'z' || s[pos] >= 'A' && s[pos] <= 'Z') {   //如果没碰到数字，就往res里加
                res += s[pos];
                ++ pos;
            } else if(s[pos] >= '0' && s[pos] <= '9') {  //碰到数字要计算循环次数，因为即将进入一个子区间
                int k = pos;
                while(s[k] != '[') {
                    ++ k;
                }
                int cnt = stoi(s.substr(pos, k - pos));  //当前数字后面的区间的循环次数
                pos = k + 1;  //跳过左括号
                string tmp = dfs(pos, s);  //对小区间递归，小区间内可能还要递归
                ++ pos;  //递归结束跳过小区间的右括号，不然无法到达小区间的后面部分了
                while(cnt --) {
                    res += tmp;  //对于小区间循环cnt次
                }
            }
        }
        return res;
    }
};