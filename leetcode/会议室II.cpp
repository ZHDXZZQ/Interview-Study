/*
    思路： 模拟，时间Onlogn，空间On
    1. 把所有会议的开始时间和结束时间拆分存储，根据时间统一进行排序
    2. 遍历所有时间节点，如果此刻是开始一个会议，那么进行中的会议+1，更新最大同时进行的会议数量
    3. 如果此刻是结束一个会议，那么进行中的会议-1
    也可以使用区间合并的思路，但是比较麻烦
*/

class Solution {
public:
    using pii = pair<int, int>;
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<pii> times;
        for (auto& meeting : intervals) {
            times.push_back({meeting[0], 1});   // 1代表开始，-1代表结束
            times.push_back({meeting[1], -1});
        }
        sort(times.begin(), times.end());   // 按时间排序
        int res = 0;
        int meetings = 0;
        for (auto& meeting : times) {   // 遍历所有时间节点
            if (meeting.second == 1) {  // 开始会议
                ++ meetings;
                res = max(res, meetings);   // 会议数量+1并更新结果
            } else if (meeting.second == -1) {  // 结束会议，数量-1
                -- meetings;
            }
        }
        return res; // 记录了同时进行中的最多的会议数量
    }
};