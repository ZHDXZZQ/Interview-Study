// 思路： 一次遍历结束，时间On，空间O1
// 1. 尝试每个加油站作为起点，但是有选择的跳过。假设i到j可达，但是到j + 1不可达，则说明从i到j之间任一加油站开始，到j + 1都不可达，
//  （因为i到j之间任一点开始时，起始汽油都是0，而刚刚从i到j经过该点时，汽油必定大于等于0），所以下次直接以j + 1作为起点尝试即可，最多遍历两边数组，时间On
// 2. 从每个起点开始，往后走n个加油站，如果能走完，则该起点可以达到目标
// 3. 如果中间某点汽油用完，则从下一个站点作为起点开始模拟

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start = 0, step = 0;        //strat代表本次模拟的起点，step表示本次模拟已走过的加油站个数
        int n = gas.size();             //n表示加油站总数
        while(start < n) {         
            int gas_remain = 0;         //汽油剩余量
            for(step = 0; step < n; ++ step) {      //每次模拟起点最多需要走n个加油站
                int pos = (start + step) % n;       //当前起点和步数下，所到达的加油站下标
                gas_remain += gas[pos];             //新站点汽油加入油箱
                gas_remain -= cost[pos];            //前往下一个站点，扣除相应汽油
                if(gas_remain < 0) {                //如果油已经耗完，选取下一个站点作为起点，视为当前情况下，本站点到下一个站点不可达
                    start += step + 1;              //注意不可以用pos + 1，否则可能死循环
                    break;
                }
            }
            if(step == n) return start;             //如果step为n，说明从当前start开始已经走了一圈，可以实现
        }
        return -1;
    }
};