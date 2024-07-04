/*
    思路： bfs，时间On，空间On
    1. 存储已经开启的房间和现在拥有的未开启的房间的钥匙
    2. 依次用每个钥匙开启每个房间，并把新获得的钥匙存起来
*/

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool> is_entry(n, false);    // 存储每个房间是否已打开
        queue<int> keys;    // 存储现在拥有的未打开的房间的钥匙
        for (auto& key : rooms[0]) {    // 把0号房间的钥匙存起来
            keys.push(key);
        }
        is_entry[0] = true; // 标记0号房间可进入
        while (keys.size()) {   // 只要还有钥匙，就去看看
            int room = keys.front();    // 打开第一个钥匙的房间门
            keys.pop();
            is_entry[room] = true;  // 该房间已进入
            auto& next_keys = rooms[room];  // 获取该房间内的钥匙
            for (auto& next_key : next_keys) {
                if (is_entry[next_key] == false) {  // 如果这个房间没有开启，则把钥匙存入
                    keys.push(next_key);
                }
            }
        }
        for (auto pass : is_entry) {    // 遍历看看还有没有房间没有进入
            if (pass == false) {
                return false;
            }
        }
        return true;

    }
};