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

/*
    思路： 快慢双指针，找规律，时间On，空间O1
    1. 利用快慢指针，快指针每次走2个，慢指针每次走1个机制，可以快速定位到中间节点
    2. 看一下哪种情况可以定位到中间节点的前一个结点，因为删除节点而不能断链
*/

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* fast = head ->next;   // 快指针开头指向第二个节点，这个可以自己找一个地方，只要能方便找目标节点就可以
        auto slow = head;   // 慢指针从头开始
        if (fast == nullptr) {  // 如果只有一个节点，直接返回空
            return nullptr;
        }
        while (fast->next && fast->next->next) {    // 如果快指针当前节点或下一个节点不是尾节点的话
            slow = slow->next;  // 慢指针移动，快指针也移动
            fast = fast->next->next;
        }
        slow->next = slow->next->next;  // 此时慢指针指向应删除节点的前一个结点，直接删除下一个节点即可
        return head;
    }
};