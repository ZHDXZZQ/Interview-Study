// 思路： 栈/双向队列，时间On，空间On，理论上用/和字符串模拟栈可以达到空间O1的效果，但是不易于理解此处不用。
// 1. 每次跳过/的干扰选择当前目录名，判断是否是.或..，其他情况则作为目录名记录、】
// 2. 要注意最顶层即根目录，不可再往上走

class Solution {
public:
    string simplifyPath(string path) {
        string cur_name;                 // 记录当前目录名
        deque<string> dic;               // 双向队列存储目录，这里方便最终构造，否则可选用栈，或字符串模拟栈（节省空间）
        int n = path.length();          //路径长度
        int i = 0;                      //遍历所有字符
        while (i < n) {               
            while (i < n && path[i] == '/') { ++ i; }       //把每个路径前可能的多余的/全部过滤掉
            if (i == n) { break; }                          //如果已经到达末尾，则最后是/干扰，直接结束循环
            int start = i;                                  //记录当前i为当前目录名的起始位置
            while (i < n && path[i] != '/') {               //找到当前目录名的末尾位置
                ++ i;
            }
            cur_name = path.substr(start, i - start);       //将当前目录名记录
            if (cur_name == ".") { continue; }              //如果当前目录名为.，则不做任何处理，跳过本次循环
            else if (cur_name == "..") {                    //如果当前目录名为..，则要向上弹出一个目录
                if (dic.empty()) { continue; }              //如果此时目录为空，即已经在根目录无法往上，则跳过本次循环
                else {
                    dic.pop_back();                         //否则返回一个目录
                }
            } else {
                dic.push_back(cur_name);                    //如果当前目录名不是.和..，则存储起来
            }
        }
        if(dic.empty()) { return "/"; }                     //如果路径为空，则返回根目录
        string res;
        while (dic.size()) {                                //否则的话构造结果
            res += '/' + dic.front();                       //对于每层目录都是/+目录名
            dic.pop_front();                                //从队头往后遍历，每遍历一个目录则弹出一个目录
        }
        return res;
    }
};