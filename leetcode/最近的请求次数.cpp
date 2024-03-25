// 思路：设计类，队列， 时间On，空间On
// 具体看注释

class RecentCounter {
public:
    RecentCounter() {
        //构造函数，没啥用
    }
    
    int ping(int t) {   //t时刻插入一个请求
        req_q.push(t);  //将该请求的时间点插入队列
        while (t - req_q.front() > 3000) {  //如果队头的请求时间距离此刻超过了3000ms
            req_q.pop();    //则将超时请求出队
        }
        return req_q.size();    //返回距离此刻3000ms以内的请求数量
    }

private:
    queue<int> req_q;   //队列存储3000ms以内的请求
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */