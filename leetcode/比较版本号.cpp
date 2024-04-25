// 思路： 双指针， 时间Om+n，空间O1
// 1. 依次找出版本号的每个修订号，依次比较

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int pos1 = 0;   //两个指针，指向两个字符串
        int pos2 = 0;
        int len1 = version1.size();
        int len2 = version2.size();
        while (pos1 < len1 || pos2 < len2) {    //只要有有一个指针还没有指完，则继续指。这样即便对于修订号数量不同的版本号来说，少的那个会直接得0，因此一定会比修订号更多的那个小
            int num1 = 0;   //记录当前的两个修订号
            int num2 = 0;
            while (pos1 < len1 && version1[pos1] != '.') {  //找到第一个修订号
                num1 *= 10;
                num1 += version1[pos1] - '0';   //记录第一个修订号的值
                ++ pos1;
            }
            ++ pos1;    //当前指针指向.或结尾，跳到下一个修订号的开头
            while (pos2 < len2 && version2[pos2] != '.') {  //记录第二个修订号
                num2 *= 10;
                num2 += version2[pos2] - '0';
                ++ pos2;
            }
            ++ pos2;
            if (num1 > num2) {  //判断当前修订号
                return 1;
            } else if (num1 < num2) {
                return -1;
            }
        }   //如果出了while循环，说明二者的版本号相同
        return 0;
    }
};