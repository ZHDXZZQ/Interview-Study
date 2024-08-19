/*
    思路： 贪心，时间On²，空间On
    1. 先按照身高排序
    2. 然后依次根据前面的人头将每个人放到合适的位置
*/

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int n = people.size();
        sort(people.begin(), people.end());
        vector<vector<int>> res(n, vector<int>(2, -1));
        for (int i = 0; i < n; ++ i) {  // 从身高低到高遍历每个人
            int& height = people[i][0]; // 当前人的身高以及前面应该有的各自更高的人的数目
            int& before_cnt = people[i][1];
            int people_cnt = 0; // 用于记录当前前面的情况
            int insert_pos = 0;
            while (people_cnt <= before_cnt) {  // 当前面人数还不够现在的要求时，循环
                if (res[insert_pos][0] == -1 && people_cnt == before_cnt) { // 如果当前位置没人，且前面应该有的人和现在的前面人数相同
                    res[insert_pos] = people[i];    // 将这个人插入到这里，开启下一个人
                    break;
                }   // 如果当前位置无法插入
                if (res[insert_pos][0] == -1 || res[insert_pos][0] == height) { // 如果当前位置为空或当前位置的人的身高和目前待插入者身高相同
                    ++ people_cnt;  // 那么前面的人数+1，因为后面遍历的人身高一定大于等于当前人身高，所以空位也算1个人，身高相同也算一个人，因为前面已插入的人身高不可能比现在的高，所以只考虑相等的情况
                }   // 如果这个位置的有人且个子更低，则不计入
                ++ insert_pos;  // 待插入位置+1，无论任何情况都要+1，因为本位不能插入
            }
        }
        return res;
    }
};