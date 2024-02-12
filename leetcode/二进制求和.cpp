// 思路： 模拟，高精度加法。时间On，空间O1
// 1. 每位相加，判断进位，确定当前位的值，直到结束即可
// 2. 额外需要注意最后的进位是否满足要求

class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());    //反转，保证从左往右相同位权值相同，方便计算
        reverse(b.begin(), b.end());
        int i = 0;                      //当前计算的位
        int m = a.size(), n = b.size();
        int cf = 0;                     //进位标志位
        string res;     
        while(i < m || i < n) {         //只要两个数还有一个没遍历完，就继续遍历
            int num1 = 0;               //表示当前位两个进行相加的数
            int num2 = 0;
            if(i < m) {                 //如果当前数没有遍历完，则更新当前位，否则位0参与计算
                num1 = a[i] - '0';
            }
            if(i < n) {
                num2 = b[i] - '0';
            }
            int cur_sum = num1 + num2 + cf; //计算当前位的值
            if(cur_sum >= 2) {          //判断是否需要进位
                cf = 1;
                cur_sum -= 2;           //更改当前位进位后的值
            } else {
                cf = 0;
            }
            res += to_string(cur_sum);  //插入当前位
            ++ i;                       //位置后移
        }
        if(cf == 1) res += '1';         //全部计算完成之后如果还有进位，则再填一个1
        reverse(res.begin(), res.end());    //反转答案，则为左大右小的权值顺序
        return res;
    }
};