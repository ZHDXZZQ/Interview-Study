/*
    思路： 根据性质模拟，时间Onlogn，空间On
    1. 中序遍历是左根右，后序遍历是左右根，因此左和右的部分一定是顺序一致的
    2. 利用栈和队列模拟过程，判断
*/

class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int n = sequence.size();
        if (n == 0) {   // 特判
            return false;
        }
        queue<int> q;   // 队列，存储后序遍历的结果
        for (auto& x : sequence) {
            q.push(x);
        }
        sort(sequence.begin(), sequence.end()); // 对入参的后序遍历排序，变成顺序的，即二叉搜索树的中序遍历
        stack<int> sta; // 利用栈判断
        int pos = 0;    // 记录当前在中序遍历中的位置
        while (pos < n) {
            sta.push(sequence[pos]);    // 中序遍历的当前头部插入
            while (sta.size() && sta.top() == q.front()) {  // 如果栈不空，且栈顶和队头一致，则出队出栈
            // 在合理的序列的情况下，左和右部分一定是同时出的，仅仅会保留中序遍历的根节点，这个在后序遍历到根的时候也会弹出
            // 但凡有弹不出的，那就不是合理序列
                q.pop();
                sta.pop();
            }
            ++ pos;
        }
        if (sta.empty() && q.empty()) { // 如果两边都弹出完了，则正确
            return true;
        }
        return false;
    }
};