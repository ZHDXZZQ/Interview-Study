// 思路： 双指针模拟滑动窗口，时间On，空间On
// 1. 将两个指针之间的内容当作窗口内的内容，这块也可以用双端队列来模拟
// 2. 用umap记录窗口内各字符出现的次数
// 3. 每次将字符加入窗口，如果该字符的次数没有超过1次，则更新答案
// 4. 否则从前面往出拿字符，直到这个重复的字符被拿出后，再重复3

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, right = 0;
        int n = s.length();
        int res = 0;
        unordered_map<char, int> c_cnt;
        int flag = 0;
        while (right < n) {     //如果right到达了尾部，则不继续，无论最后一个字符是否重复
            if(flag == 0) {     //flag为0表示加入字符
                if (++ c_cnt[s[right ++]] == 1) {   //如果该字符加入后其数量为1
                    res = max(res, right - left);   //更新答案  //todo：可以减少更新次数，每次遍历到重复再更新
                } else {
                    flag = 1;           //否则往出拿字符
                }
            } else {
                while (-- c_cnt[s[left ++]] != 1);     
                //如果拿出字符后数量不为1，说明拿出的不是重复的字符，一直取直到取出重复的字符为止
                //这里无需考虑左指针超过右指针，因为不可能发生这种情况
                flag = 0;       //目前窗口内已无重复字符，开始往里加，此时无需更新答案，因为肯定不是最大
            }
        }
        return res;
    }
};