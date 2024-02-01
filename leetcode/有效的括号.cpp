// 思路： 栈，时间On，空间On
// 1. 只要遇到左括号就进栈
// 2. 遇到右括号就和栈顶比较，如果不匹配，则不行
// 3. 如果匹配，则栈顶左括号出栈，相当于消除一对
// 4. 全部遍历完后如果栈中全部抵消完，则全部匹配。否则不行

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (auto& c : s) {
            if (c == '(' || c == '[' || c == '{') { //左括号进栈
                st.push(c);
            } else {
                if (c == ')') { //碰到右括号去和栈顶比较
                    if (st.empty() || st.top() != '(') {    //栈空或栈顶不为匹配的左括号都不行
                        return false;
                    } else {    //如果匹配直接左括号出栈
                        st.pop();
                    }
                } else if (c == ']') {
                    if(st.empty() || st.top() != '[') {
                        return false;
                    } else {
                        st.pop();
                    }
                } else if (c == '}') {
                    if(st.empty() || st.top() != '{') {
                        return false;
                    } else {
                        st.pop();
                    }
                }
            }
        }
        if(st.empty()) return true; //如果全部比较完后栈空，表明全部匹配
        return false;
    }
};