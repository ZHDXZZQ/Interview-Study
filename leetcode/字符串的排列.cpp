/*
    思路： DFS回溯全排列，时间On！，空间On！
*/

class Solution {
public:
    string str; // 输入
    int n;  // 字符串数量
    string temp;    // 暂存结果
    vector<string> res; // 结果
    unordered_set<string> res_set;  // 结果去重
    unordered_map<char, int> used;  // 过程字符记录是否使用过
    
    void dfs(int pos) {
        if (pos == n) { // 如果全部插入完毕
            if (res_set.find(temp) == res_set.end()) {
                res.push_back(temp);    // 去重的插入结果
                res_set.insert(temp);
                return ;
            }
        }
        for (int i = 0; i < n; ++ i) {  // 对于当前位置，判断哪个字符可以插入
            if(used[str[i]] > 0) {  // 如果没用完
                -- used[str[i]];
                temp.push_back(str[i]); // 插入dfs
                dfs(pos + 1);
                temp.pop_back();    // 回溯
                ++ used[str[i]];
            }
        }
    }

    vector<string> Permutation(string s) {
        str = s;
        for (auto& c : s) {
            ++ used[c];
        }
        n = str.size();
        dfs(0);
        return res;
    }
};