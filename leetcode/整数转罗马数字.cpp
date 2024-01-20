//思路： 模拟或者硬编码，时间O1，空间O1
// 1. 没有什么巧妙的方法，把所有情况列举出来枚举即可
// 2. 按从大到小的顺序，每种情况枚举到尽头

class Solution {
public:
    int values[13] = {    
        1000,
        900, 500, 400, 100,
        90, 50, 40, 10,
        9, 5, 4, 1
    };  //使用两个数组来列举所有组合情况，因为这里要按序减
    string reps[13] = {
        "M",
        "CM", "D", "CD", "C",
        "XC", "L", "XL", "X",
        "IX", "V", "IV", "I",
    };

    string intToRoman(int num) {
        string res;
        for (int i = 0; i < 13; i ++ ) {    //从大到小每种情况减到尽头
            while (num >= values[i]) {
                num -= values[i];
                res += reps[i];
            }
        }
        return res;
    }
};