// 思路： dfs， 时间Onlgn，空间O1
// 1. 类似trie树，依次遍历每个数，然后向下延伸，直到超过目标值n

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        int num = 1;    //初始值为1
        vector<int> res(n);
        for (int i = 0; i < n; ++ i) {
            res[i] = num;
            if (num * 10 <= n) {    //往后面填0，每次扩展后填入结果，扩展到不能扩展为止
                num *= 10;
            } else {        //不能扩展后，横向递增，直到到达n或者到达当前位数的9为止
                while (num == n || num % 10 == 9) { //除到上一位最高位，如果是9则继续除
                    num /= 10;  //比如199要直接除到2，即除100之后再执行下面的++
                }   //如果是189，就除10后得18，+1后再走19x
                ++ num;     //自然+1
            }
        }
        return res;
    }
};