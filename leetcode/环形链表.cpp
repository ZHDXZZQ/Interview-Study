/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

 // 思路： 双指针法，时间On，空间O1。空间换时间选哈希表，但收益不大
 // 1. 快指针一次走两个，慢指针一次走一个，如果有环，快指针一定会追上慢指针
 // 2. 否则，无环。其他特殊情况，特殊判断

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;
        ListNode *slow = head, *fast = head->next;
        while(fast) {       //如果快指针为空，表示到头，则无环
            if(slow == fast) return true;   //如果快慢指针一样，表示环内相遇
            fast = fast->next;      //否则快慢指针各进一步
            slow = slow->next;
            if(!fast) return false;     //如果快指针到头，则无环
            else fast = fast->next;     //否则快指针再走一步
        }
        return false;
    }
};