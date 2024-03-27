// 思路： 贪心+双指针， 时间Oslogs+glogg，空间Ologs+logg，分别是排序两个数组所用的时间和空间
// 1. 将两个数组排序，都按从小到大的顺序增长
// 2. 如果饼干大小满足孩子，则喂给当前的孩子
// 3. 如果当前饼干大小不满足孩子，则给当前孩子找更大的饼干。因为后面的孩子要求只会更大
// 4. 只要有一边已经遍历全部，则结束

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());   //排序
        sort(s.begin(), s.end());
        int child_size = g.size();  //记录孩子和饼干的数量
        int cookie_size = s.size();
        int child_ptr = 0;          //双指针，分别指当前孩子和当前饼干
        int cookie_ptr = 0;
        int res = 0;
        while (child_ptr < child_size && cookie_ptr < cookie_size) {    //两边指针不越界
            if (s[cookie_ptr] >= g[child_ptr]) {    //如果饼干满足要求
                ++ res;             //配对成功+1
                ++ cookie_ptr;      //饼干和孩子的指针分别后移
                ++ child_ptr;
            } else {                //饼干小了，不满足需求
                ++ cookie_ptr;      //试图寻找更大的饼干
            }
        }
        return res;
    }
};