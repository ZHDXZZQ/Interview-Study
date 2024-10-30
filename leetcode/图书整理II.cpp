/*
    思路： 队列，时间O1，空间On
*/

class CQueue {
private:
    queue<int> q;

public:
    CQueue() {}
    
    void appendTail(int value) {
        q.push(value);
    }
    
    int deleteHead() {
        if (q.empty()) {
            return -1;
        }
        int res = q.front();
        q.pop();
        return res;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */