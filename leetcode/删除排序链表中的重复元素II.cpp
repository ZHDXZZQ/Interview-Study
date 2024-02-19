/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 思路： 模拟，时间On，空间O1
// 1. 首先用一个指针用于记录结果，用一个指针用于遍历链表
// 2. 因为需要删除节点，所以每次去判断的是下一个结点，这样方便删除
// 3. 模拟判断，将所有重复结点删除

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL) return head;       //特判
        auto res = new ListNode(0, head);   //创建返回节点为头结点的前置结点，方便可能删除头结点的情况
        auto last = res;                    //用于遍历链表，方便删除
        while(last->next) {                 //如果下一个节点存在
            bool is_more = false;           //记录是否下一个结点有重复
            auto cur_node = last->next;     //将下一个结点记为当前结点用于判断
            while(cur_node->next && cur_node->next->val == cur_node->val) { //如果结点重复
                cur_node = cur_node->next;  //持续遍历，直到不重复位置
                is_more = true;             //记录有重复结点
            }
            if(is_more) {                   //如果有重复结点，直接将中间所有的重复结点删除
                last->next = cur_node->next;
            } else {
                last = last->next;          //否则的话直接指向下一个结点继续遍历
            }
        }
        return res->next;
    }
};