/*
    思路： 快慢指针+数学，时间On，空间O1
    使用两个指针fast 与 slow。它们起始都位于链表的头部。
    随后，slow 指针每次向后移动一个位置，而 fast 指针向后移动两个位置。
    如果链表中存在环，则 fast 指针最终将再次与 slow 指针在环中相遇。
    此时，slow一定还没有走完一遍环。
    假设此时快指针走了a+x+y+x，其中a为环前的长度，x为slow在环中走过的长度，y为环剩余的长度，即x+y要等于环长
    此时假设快指针走过了n遍环，当然也可以时一圈，即快指针走过了a+n(x + y)+x
    慢指针走过了a + x，而快指针速度时慢指针的两倍，因此有a + nx + ny + x = 2a + 2x
    因此有a + x = nx + ny，即(n - 1)x + ny = a，即(n - 1)(x + y) + y = a
    因此可以得出，走n-1圈环，最后再走y步，才和环前的长度相等
    假设环很长，远长于a，那么n一定等于1，此时y=a，所以我们一个指针从头开始走，另一个指针从相遇点走，碰到的地方恰好就是长度为a的环的起始点
    假设环很短，远小于a，那么在走完多圈之后，我们还是需要走y步才等于啊，此时相遇点再走y步也到达a的环的起始点
    即从相遇点到入环点的距离加上 n−1 圈的环长，恰好等于从链表头部到入环点的距离。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) {
            return nullptr;
        }
        auto fast = head;
        auto slow = head;
        while (fast && fast->next) {    // 快慢指针找到相遇点
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) { break; }
        }
        if (!fast || !fast->next) { // 如果没有相遇，则无环
            return nullptr;
        }
        slow = head;
        while (slow != fast) {  // 否则令一个指针从头走，一个指针继续走，相遇点即为环开头
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};