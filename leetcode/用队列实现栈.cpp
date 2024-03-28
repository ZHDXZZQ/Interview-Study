// 思路： 模拟， 时间On，空间On
// 1. 用一个队列模拟栈（相似题目为用两个栈模拟队列）
// 2. 每次插入时，现将元素插入队尾，再将前面元素依次移动到后面
// 3. 此时，队头到队尾的顺序即为栈顶到栈尾的顺序
// 4. 其他操作直接进行即可

class MyStack {
public:
    MyStack() {

    }
    
    void push(int x) {
        int n = q.size();   //记录当前队列中的元素个数
        q.push(x);      //插入该元素
        while (n --) {  //将前面所有元素依次移动到队尾
            int& top = q.front();
            q.pop();
            q.push(top);
        }
    }
    
    int pop() {     //直接出队
        int& res = q.front();
        q.pop();
        return res;
    }
    
    int top() { //返回队头
        return q.front();
    }
    
    bool empty() {  //判空
        return q.empty();
    }
private:
    queue<int> q;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */