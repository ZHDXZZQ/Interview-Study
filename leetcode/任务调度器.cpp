/*
    思路： 巧妙思路，时间Om，空间Om，m为任务数量
    1. 先计算出同种任务的最多出现次数
    2. 再计算出出现次数最多的任务的个数
    3. 计算最基本的排列方法
    4. 如果有更多的任务，则直接继续往后顺序排列即可，即如果任务数多余当前排列的数量，则取任务个数即可
*/

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int all_task_cnt = tasks.size();
        unordered_map<char, int> task2cnt;
        int max_task_cnt = 0;
        int max_task_species = 0;
        for (auto& task : tasks) {
            ++ task2cnt[task];
            max_task_cnt = max(max_task_cnt, task2cnt[task]);   // 计算任务出现最多的次数
        }
        for (auto& it : task2cnt) {
            if (it.second == max_task_cnt) {
                ++ max_task_species;    // 找出出现次数最多的任务的个数
            }
        }
        int res = (max_task_cnt - 1) * (n + 1) + max_task_species;  // 将这些任务按相隔n个排列，最后一列排出这些次数最多的任务个数
        // 如果还有更多的任务，无论这些任务是否是个数最多的任务，都在现有基础上继续往后排列即可，一定能满足条件
        return max(all_task_cnt, res);
    }
};