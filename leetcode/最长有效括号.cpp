/*
    思路： 栈，时间On，空间On
    1. 对于遇到的每个 ‘(’ ，我们将它的下标放入栈中
    2. 对于遇到的每个 ‘)’ ，我们先弹出栈顶元素表示匹配了当前右括号：
    3. 如果栈为空，说明当前的右括号为没有被匹配的右括号，我们更新新的开头
    4. 如果栈不为空，当前右括号的下标减去栈顶元素即为「以该右括号为结尾的最长有效括号的长度」
    5. 利用一个变量记录当前有效括号的开头，最开始为-1，每次遇到多余的右括号则更新为其下标
*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        stack<int> rec;
        int cur = -1;   // 记录当前情况的合法括号的开头位置
        for (int i = 0; i < s.size(); ++ i) {
            if (s[i] == '(') {      // 左括号直接记录其下标
                rec.push(i);
            } else {        // 右括号
                if (rec.empty()) {  // 如果里面没有左括号
                    cur = i;    // 这个右括号是非法的，后面所有的合法括号都会被这里截断，新的合法括号至少是从下一个位置开始的
                } else {        // 如果栈中有左括号
                    rec.pop();  // 弹出左括号，这一对是合法的
                    if (rec.size()) {   // 如果还有左括号在前面
                        res = max(res, i - rec.top());  // 这个左括号这个右括号之间的所有括号都是合法的，但是这个左括号可能还不合法
                    } else {        // 如果前面已经没有左括号了
                        res = max(res, i - cur);    // 这个右括号前面的应该都合法，但是有可能前面还有非法的右括号，所以要从上一个右括号或开头开始记录
                    }
                }
            }
        }
        return res;
    }
};

// 更优的时间On，空间O1解法
// 我们利用两个计数器 left 和 right 。首先，我们从左到右遍历字符串，对于遇到的每个 ‘(’，我们增加 left 计数器，对于遇到的每个 ‘)’ ，我们增加 right 计数器。
// 每当 left 计数器与 right 计数器相等时，我们计算当前有效字符串的长度，并且记录目前为止找到的最长子字符串。
// 当 right 计数器比 left 计数器大时，我们将 left 和 right 计数器同时变回 0。

// 这样的做法贪心地考虑了以当前字符下标结尾的有效括号长度，每次当右括号数量多于左括号数量的时候之前的字符我们都扔掉不再考虑，重新从下一个字符开始计算
// 但这样会漏掉一种情况，就是遍历的时候左括号的数量始终大于右括号的数量，即 (() ，这种时候最长有效括号是求不出来的。

// 解决的方法也很简单，我们只需要从右往左遍历用类似的方法计算即可，只是这个时候判断条件反了过来：
// 当 left 计数器比 right 计数器大时，我们将 left 和 right 计数器同时变回 0
// 当 left 计数器与 right 计数器相等时，我们计算当前有效字符串的长度，并且记录目前为止找到的最长子字符串

// class Solution {
// public:
//     int longestValidParentheses(string s) {
//         int left = 0, right = 0, maxlength = 0;
//         for (int i = 0; i < s.length(); i++) {   // 从左往右遍历
//             if (s[i] == '(') {
//                 left++;
//             } else {
//                 right++;
//             }
//             if (left == right) {
//                 maxlength = max(maxlength, 2 * right);
//             } else if (right > left) {
//                 left = right = 0;
//             }
//         }
//         left = right = 0;
//         for (int i = (int)s.length() - 1; i >= 0; i--) { // 从右往左遍历
//             if (s[i] == '(') {
//                 left++;
//             } else {
//                 right++;
//             }
//             if (left == right) {
//                 maxlength = max(maxlength, 2 * left);
//             } else if (left > right) {
//                 left = right = 0;
//             }
//         }
//         return maxlength;
//     }
// };
