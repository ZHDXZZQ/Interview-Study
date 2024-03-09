// 思路： 回溯，时间（O4^n）/根号n（解的数量级），空间On递归栈空间
// 1. 只需要满足左边括号数一定是大于等于右边括号数，并且左边括号数不超过总对数即可

class Solution {
public:
    vector<string> res;

    void dfs(int l, int r, int& n, string cur_res) {    //l和r分别表示当前字符串中左右括号的数量
        if(r == n) {                //如果右边括号数到达要求对数，则表明左右一定都为n，此时无需继续
            res.push_back(cur_res);
            return;
        }

        if(l == r) dfs(l + 1, r, n, cur_res + '('); //否则的话左右括号数量相等时，只能扩增左边括号
        else if(l > r) {                            //如果左边括号更多，则左右括号都可能加入
            if(l == n) dfs(l, r + 1, n, cur_res + ')'); //如果左边括号数量已经达到上限，则只加入右边括号
            else {              //否则左右括号都加入各自分支继续进行
                dfs(l + 1, r, n, cur_res + '(');
                dfs(l, r + 1, n, cur_res + ')');
            }
        }
    }

    vector<string> generateParenthesis(int n) {
        dfs(0, 0, n, "");
        return res;
    }
};