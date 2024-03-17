// 思路：栈模拟，需要考虑多种细节，时间On，空间On
// 1. 具体看注释，代码没有优化，优化版本在后面。每种情况都是考虑之后加上去的，俗称屎山代码

class Solution {
public:
    void calc() {       //计算一次
        if (op.empty() || op.top() == '(') { return; }  //如果操作符栈为空或者栈顶是左括号，此处的数字为第一个数字，无需计算
        int num2 = res.top();           //取出两个数字
        res.pop();
        int num1 = res.top();
        res.pop();
        char opsign = op.top();         //取出操作符
        op.pop();
        if (opsign == '+') {            //进行运算
            num1 += num2;
        } else {
            num1 -= num2;
        }
        res.push(num1);                 //将结果存回栈
    }

    int calculate(string s) {
        string formula;                 //记录真实公式，不包含空格
        for(auto& c : s) {
            if(c != ' ') {              //将原本s中所有非空格的字符放入新字符串中
                formula += c;
            }
        }
        int n = formula.size();
        int i = 0;
        while (i < n) {             
            if (formula[i] == '-') {    //每次循环首先读当前数字，然后再读取操作符，然后将指针指向下一个数字的头部
                res.push(0);            //如果此时指向的是一个符号，又因为不可能有两个操作符连续，因此他只可能是开头的-5，或-（2+3）之类的情况
                op.push('-');           //因此看作是0-5，先插入被减数0，再插入减符号
                ++ i;
                continue;               //此时还在取操作数的过程中，这里并没有取完当前操作数，只是取了符号，因此跳过后续填充下一个操作符的步骤
            } else if (formula[i] == '(') { //如果此时是左括号，则只将左括号入栈，不进行任何操作
                op.push('(');               //同理，当前还在取操作数的过程中，该操作数并没取出，因此不进行后续操作
                ++ i;
                continue;
            } else {                    //其余情况，则当前指针一定是数字，那么就要截取这个数字
                int start = i;
                while(i < n && (formula[i] <= '9' && formula[i] >= '0')) {  //指针指向第一个非数字的位置
                    ++ i;
                }
                string num_str = formula.substr(start, i - start);      //将这段数字截取，转换成int类型存入res中
                int num = stoi(num_str);
                res.push(num);
                calc();                 //因此存入了一个数字，所以要进行计算，如果是第一个数字，计算会直接return，其余情况一定可以和前一个数进行计算
            }

            if (i < n) {                //当前数字插入并计算完毕，插入这个数尾部的操作符
                if (formula[i] == ')') {    //如果是右括号
                    while (formula[i] == ')') { //则要考虑多种右括号重叠的情况
                        op.pop();       //把所有右括号出来，并且计算当前括号内的结果
                        ++ i;
                        calc();
                    }
                    if (i < n) {        //所有右括号出来后，如果指针还没有指向末尾，则右口号的后边一定是一个操作符
                        op.push(formula[i]);    //将这个操作符入栈，结束本次循环
                        ++ i;
                    }
                } else {            //如果不是右括号，则一定是操作符，此时将操作符入栈，结束本次循环
                    op.push(formula[i]);
                    ++ i;
                }
            }
        }
        return res.top();       //结尾的时候一定保证了操作符栈为空，运算数的栈只剩一个最终结果
    }

private:
    stack<int> res;     //存储运算数
    stack<char> op;     //存储操作符
};



// 官方更新的优化版简洁代码，时空复杂度相同，运行起来效率会高不少
// class Solution {
// public:
//     int calculate(string s) {
//         stack<int> ops;
//         ops.push(1);
//         int sign = 1;

//         int ret = 0;
//         int n = s.length();
//         int i = 0;
//         while (i < n) {
//             if (s[i] == ' ') {
//                 i++;
//             } else if (s[i] == '+') {
//                 sign = ops.top();
//                 i++;
//             } else if (s[i] == '-') {
//                 sign = -ops.top();
//                 i++;
//             } else if (s[i] == '(') {
//                 ops.push(sign);
//                 i++;
//             } else if (s[i] == ')') {
//                 ops.pop();
//                 i++;
//             } else {
//                 long num = 0;
//                 while (i < n && s[i] >= '0' && s[i] <= '9') {
//                     num = num * 10 + s[i] - '0';
//                     i++;
//                 }
//                 ret += sign * num;
//             }
//         }
//         return ret;
//     }
// };