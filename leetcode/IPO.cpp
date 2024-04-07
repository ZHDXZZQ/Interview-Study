// 思路： 贪心+堆，时间Onlogn，空间On
// 1. 银行家算法，利用大根堆维护当前可购买的所有股票的利润，堆顶即为本次所有可购买的股票的最大利润
// 2. 每次记录本金，判断哪些股票可购买，把能购买的股票加入堆中

typedef pair<int, int> PII;
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        // k是购买个数，w是本金，profits是利润，capital是购买价格
        vector<PII> stock;  //记录股票，first为购买价，second为利润
        int n = profits.size();
        for (int i = 0; i < n; ++ i) {
            stock.push_back(make_pair(capital[i], profits[i])); //存储股票
        }
        sort(stock.begin(), stock.end());   //按购买价格排序
        priority_queue<int, vector<int>, less<int>> heap;   //默认大根堆，此时后两个可以缺省
        int i = 0;
        while (k --) {      //购买k次
            while (i < n && stock[i].first <= w) {  //每次从股票中取出所有的当前本金可购买的股票
                heap.push(stock[i].second);         //将他们的利润放入大根堆中
                ++ i;
            }
            if (heap.empty()) {             //如果堆为空，则无法购买任何股票，返回即可
                break;
            }
            w += heap.top();        //如果堆不为空，则购买堆顶的股票，其利润就加入到了本金之中
            heap.pop();             //堆顶股票购买完成，出对
        }
        return w;       //每轮的本金即能购买的所有股票的最大利润和
    }
};