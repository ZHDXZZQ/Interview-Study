/*
    解法1： dfs，时间On*2^n，空间On
    1. 每次插入一个数字，然后以这个数字为基准深度搜索
    2. 将这个数字弹出，再插入下一个数字，深度遍历
*/

class Solution {
public:
    vector<vector<int>> res;
    vector<int> temp;
    int n;

    void dfs(int pos, vector<int>& nums) {
        res.push_back(temp);    // 将当前集合插入结果
        if (pos >= n) { // 如果已经超出范围，无需遍历，这句话可以不要
            return;
        }
        for (int i = pos; i < n; ++ i) {    // 从这个数字往后遍历，依次插入，深搜，弹出，避免重复
            temp.push_back(nums[i]);
            dfs(i + 1, nums);
            temp.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        n = nums.size();
        dfs(0, nums);
        return res;
    }
};


/*
    解法2
    思路： 位图的思想，时间O2^n*logn，空间On
    1. 将n个数展开到n位，利用一个数字的二进制表示所有情况，每位的1或0表示当前这个数字选择或不选择
    2. 遍历这个二进制数，插入对应位置的数字
    3. 依次遍历0-2^n的所有二进制数的所有情况，每个数字对应一种组合
*/

// class Solution {
// public:
//     //利用二进制的思想
//     vector<vector<int>> subsets(vector<int>& nums) {
//         vector<vector<int>> res;
//         int n = nums.size();
//         int bin = pow(2, n);
//         for(int i = 0; i < bin; i ++) {  
//             //遍历一遍2的n次，每次换成二进制数，有1的地方代表这次加入这个值
//             int j = i;
//             vector<int> temp;  //暂存结果
//             int cur = 0;  //转换二进制时的当前位置
//             while(j) {
//                 int k = j % 2;  //除二取余法
//                 if(k != 0) {
//                     temp.push_back(nums[cur]);  //当前位为1，插入
//                 }
//                 ++ cur;  //下一个位置
//                 j /= 2;
//             }
//             res.push_back(temp);  //插入当前结果
//         }
//         return res;
//     }
// };