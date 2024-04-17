// 思路： 贪心 时间On，空间On
// 1. 每次判断当前字符大小是否小于前一个字符，如果是，则删掉前一个字符，将当前字符进入队列
// 2. 相当于维护了一个单调栈
// 3. 遍历完之后，队列中是一个递增的数字，此时如果k还不为0，则把队尾的k个数字删掉
// 4. 把前导0删掉，返回结果

class Solution {
public:
    string removeKdigits(string num, int k) {
        int len = num.size();
        if (len == k) { return "0"; }   //如果长度和数量相等，返回0
        deque<char> deq;
        deq.push_back(num[0]);      //首先将第一个字符插入
        for (int i = 1; i < len; ++ i) {    //遍历所有字符
            while (deq.size() && num[i] < deq.back() && k) {    //如果当前字符小于队尾字符，则删掉，除非已删除k个，或者当前队列为空，或者当前队列已单调不递减为止
                deq.pop_back();
                -- k;
            }
            deq.push_back(num[i]);  //将当前字符入队
        }
        while (k --) {
            deq.pop_back(); //还能删k个，把队尾的k个删掉
        }
        string res;
        bool zero = true;
        for (auto& x : deq) {   //将队列中的字符加入答案中
            if (x == '0') { //判断不加入前导0
                if (zero) {
                    continue;
                }
            }
            zero = false;
            res += x;
        }
        if (res.empty()) { return "0"; }    //如果此时都被删完了，则返回0
        return res;
    }
};