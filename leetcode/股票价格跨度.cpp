/*
    思路： 单调栈，时间On，空间On
    1. 记录每天的价格，天数作为下标
    2. 利用单调递减栈存储天数下标，对应天数的价格是严格递减的
    3. 碰到更小的值直接插入，因为前面没有更小的
    4. 否则将更小的依次出栈，直到碰到更大的，因为每次都将更小的出来了留下了相对大的，因此出去的那些也一定比现在的价格低（因为更高的都出去了）
    5. 这样当前价格到上一次更大的价格间就都是小的
*/

class StockSpanner {
public:
    StockSpanner() {
        day = 0;    // 记录当前天
    }
    
    int next(int price) {
        prices.emplace_back(price); // 将当前价格插入，下标就是天数
        while (!sta.empty() && prices[sta.top()] <= price) {    // 如果栈不空且栈顶日的价格更小于等于当前日
            sta.pop();  // 持续出栈
        }
        if (sta.empty()) {  // 如果此时栈空，说明前面都是价格更低的，返回该日子
            res = day + 1;
        } else {
            res = day - sta.top();  // 否则计算二者间间隔的天数
        }
        sta.push(day);  // 将当前日子插入
        ++ day; // 天数+1
        return res;
    }
    int day;
    int res;
    vector<int> prices;
    stack<int> sta;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */