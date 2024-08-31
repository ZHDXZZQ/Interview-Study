/*
    思路： 递归的写法，时间On，空间On栈空间
    也可以用遍历存储后翻转的方法
*/

/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> res;
    void func(ListNode* t) {
        if (t == nullptr) {
            return; // 如果到尾巴了，结束
        }
        func(t->next);  // 否则就调用下一个节点
        res.push_back(t->val);  // 往回返回的时候插入值
    }
    vector<int> printListFromTailToHead(ListNode* head) {
        func(head);
        return res;
    }
};
