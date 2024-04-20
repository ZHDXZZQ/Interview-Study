// 思路： dfs图， 时间On^2，空间On
// 1. 遍历所有城市，对其所有直接相连的城市进行dfs
// 2. 每次dfs可以找到所有属于该省份的城市，记录下来

class Solution {
public:
    unordered_set<int> set; //记录哪些城市已经被遍历过
    int n;  //记录城市总数

    void dfs (int i, vector<vector<int>>& isConnected) {    //找到该省份内的所有城市
        for (int j = 0; j < n; ++ j) {  //遍历这个城市和其他所有城市的关系
            if (isConnected[i][j] == 1) {   //如果有直接相连
                 if (set.find(j) != set.end()) {    //如果相连的城市被遍历过，跳过
                    continue;
                } else {
                    set.insert(j);      //否则的话遍历这个城市
                    dfs(j, isConnected);
                }
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        n = isConnected.size();
        int res = 0;    //记录省份总数
        for (int i = 0; i < n; ++ i) {  //遍历所有城市
            if (set.find(i) != set.end()) { //如果该城市已经被遍历过，则跳过
                continue;
            }
            set.insert(i);      //否则遍历该城市
            ++ res;             //没遍历到一个新的城市，说明之前没有被遍历过，即属于一个新的省份
            dfs(i, isConnected);
        }
        return res;
    }
};