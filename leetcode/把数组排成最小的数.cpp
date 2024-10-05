/*
    思路： 类冒泡排序，时间On²，空间On
    1. 将数字转换为字符串
    2. 比较两个数字的不同拼接方法哪个更小，将更小的组合放到前面
    3. 每次比较到头
*/

class Solution {
public:
    static bool cmp(string& x, string& y) {
        return x + y < y + x;
    }
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param numbers int整型vector 
     * @return string字符串
     */
    string PrintMinNumber(vector<int>& numbers) {
        // write code here
        string res;
        if (numbers.empty()) {
            return res;
        }
        vector<string> nums;
        for (auto& x : numbers) {
            nums.push_back(to_string(x));
        }

        sort(nums.begin(), nums.end(), cmp);    // 比较字符串的两种组合顺序哪种更小，更小的放前面

        for (auto& str : nums) {
            res += str;
        }
        return res;
    }
};