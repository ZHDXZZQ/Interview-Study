/*
    思路： 模拟，插入删除时间O1，空间On
    1. 栈1用于入队，只要插入节点，直接存入栈1
    2. 栈2用于出队，为入队的逆序，当要出队时，如果栈2为空，则把栈1依次出栈并插入栈2，这样栈2的顶部就是队头
    3. 如果栈2有元素，则栈2的栈顶依然是队头，直接出栈即可，直到出完，再执行第二步
    平均下来，n个元素只需要移动n次到栈2，入队恒定O1，出队平均下来O1
*/

class Solution {
public:
    void push(int node) {
        stack1.push(node);  // 无脑入队
    }

    int pop() {
        if (stack2.empty()) {   // 栈2为空时，先把栈1所有元素反向挪过来
            while (stack1.size()) {
                int num = stack1.top();
                stack1.pop();
                stack2.push(num);
            }
        }
        int res = stack2.top(); // 栈2顶即队头
        stack2.pop();
        return res;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};