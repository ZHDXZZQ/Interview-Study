// 思路： 双指针法，时间On，空间O1
// 1. 目标指针按序指向s的每个字符
// 2. 用一个指针遍历t的每个字符
// 3. 每当有一个字符匹配，则令目标指针右移
// 4. 每步都右移遍历t的指针。如果目标指针移到s的结尾，则存在
// 5. 如果遍历完t串后，目标指针还没移动到最后，则失败

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if(s.size() == 0) return true;      //如果s为空串，直接匹配
        int target = 0;     //目标指针，指向需要在t中寻找的s的字符
        int ptr = 0;        //遍历t的指针
        while(ptr < t.size()) {
            if(s[target] == t[ptr]) {       //如果匹配
                ++ target;                  //目标指针后移
                if(target == s.size()) {    //如果目标指针已经移动到最后，则包含
                    return true;
                }
            }           
            ++ ptr;             //每步都移动遍历t的指针
        }
        return false;       //遍历完了t，说明不包含
    }
};