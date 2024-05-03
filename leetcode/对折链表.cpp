// 对折链表
// 链表对折：一个有n个节点的单向链表listN，如果n为奇数，则中间节点两边的链表节点反转，中间节点连接反转后的左右部分；如果n为偶数，则左右平分的链表节点反转，然后两边链表连接起来。
// 示例：
// 如果链表为：1->2->3->4->5->6， 对折后链表为3->2->1->6->5->4
// 如果链表为：1->2->3->4->5->6->7，对折后链表为3->2->1->4->7->6->5

// 此题未经过校验，仅提供思路，遍历两边链表，时间On，空间O1
// 思路： 寻找中点，分别翻转链表

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
};

// 翻转链表，利用3个节点翻转一个链表
ListNode* reverse_list(ListNode* h) {
    auto first = h;
    auto second = first->next;
    while (second) {
        auto third = second->next;
        second->next = first;
        first = second;
        second = third;
    }
    h->next = nullptr;
    return first;
}

int main() {
    ListNode* head;
    int cnt = 0;
    // 统计节点个数，可以使用快慢指针找中点
    auto temp = head;
    while (temp) {
        temp = temp->next;
        ++ cnt;
    }

    // 找到前半部分链表的尾巴
    auto tail = head;
    for (int i = 0; i < cnt / 2 - 1; ++ i) {
        tail = tail->next;
    }

    // 找到后半部分的头节点
    auto next_head = tail->next;
    tail->next = nullptr;
    auto mid = new ListNode();
    if (cnt % 2 == 1) {
        mid = next_head;
        next_head = next_head->next;
    }

    // 将两部分翻转
    auto res = new ListNode();
    res->next = reverse_list(head);
    if (cnt % 2 == 1) {
        head->next = mid;
        mid->next = reverse_list(next_head);
    } else {
        tail->next = reverse_list(next_head);
    }
    return 0;
}