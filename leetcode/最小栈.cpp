// 思路： 用辅助栈，时间O1，空间On
// 1. 定义一个当前最小值，用于记录当前栈中的最小值
// 2. 定义一个辅助栈，栈大小和原栈相同，栈顶为当前栈中的最小值
// 3. 每插入一个值，辅助栈就插入一个当前栈中的最小值，这样保证任何时候栈顶一定是当前情况的栈中的最小值
// 4. 弹出栈顶的时候，辅助栈和当前最小值同步更新

class MinStack {
public:
    MinStack() {
        cur_min = INT_MAX;      //当前最小值初始化为类型最大值
    }
    
    void push(int val) {
        ans_stack.push(val);        //当前栈插入该值
        cur_min = min(cur_min, val);    //更新当前最小值，并将当前最小值插入辅助栈中
        min_stack.push(cur_min);
    }
    
    void pop() {
        ans_stack.pop();        //辅助栈和当前栈同时弹出栈顶
        min_stack.pop();
        if(!min_stack.empty()) cur_min = min_stack.top();       //更新当前最小值
        else cur_min = INT_MAX;     //如果栈空则重新初始化
    }
    
    int top() {
        return ans_stack.top();     //返回当前栈的栈顶
    }
    
    int getMin() {
        return min_stack.top();     //返回辅助栈的栈顶，即为当前栈的最小值
    }

protected:
    int cur_min;
    stack<int> ans_stack;
    stack<int> min_stack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */