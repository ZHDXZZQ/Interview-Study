#include <iostream>

struct ListNode {
    int value;
    ListNode* next;
    
    ListNode(int val) : value(val), next(nullptr) {}
};

// 将链表按基准值分为三部分，小于、等于、大于
void partition(ListNode* head, ListNode* pivot, ListNode** lessHead, ListNode** equalHead, ListNode** greaterHead) {
    *lessHead = *equalHead = *greaterHead = nullptr;
    ListNode *lessTail = nullptr, *equalTail = nullptr, *greaterTail = nullptr;
    
    while (head != nullptr) {
        if (head->value < pivot->value) {
            if (*lessHead == nullptr) {
                *lessHead = lessTail = head;
            } else {
                lessTail->next = head;
                lessTail = lessTail->next;
            }
        } else if (head->value == pivot->value) {
            if (*equalHead == nullptr) {
                *equalHead = equalTail = head;
            } else {
                equalTail->next = head;
                equalTail = equalTail->next;
            }
        } else {
            if (*greaterHead == nullptr) {
                *greaterHead = greaterTail = head;
            } else {
                greaterTail->next = head;
                greaterTail = greaterTail->next;
            }
        }
        head = head->next;
    }
    
    if (lessTail) lessTail->next = nullptr;
    if (equalTail) equalTail->next = nullptr;
    if (greaterTail) greaterTail->next = nullptr;
}

// 合并三个部分
ListNode* concatenate(ListNode* less, ListNode* equal, ListNode* greater) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    
    if (less) {
        head = less;
        while (less->next) {
            less = less->next;
        }
        tail = less;
    }
    
    if (equal) {
        if (head == nullptr) {
            head = equal;
        } else {
            tail->next = equal;
        }
        tail = equal;
        while (tail->next) {
            tail = tail->next;
        }
    }
    
    if (greater) {
        if (head == nullptr) {
            head = greater;
        } else {
            tail->next = greater;
        }
    }
    
    return head;
}

// 快速排序主函数
ListNode* quickSort(ListNode* head) {
    if (!head || !head->next) return head;  // 递归终止条件
    
    ListNode* lessHead = nullptr;
    ListNode* equalHead = nullptr;
    ListNode* greaterHead = nullptr;
    
    partition(head, head, &lessHead, &equalHead, &greaterHead);  // 按基准值分割链表
    
    lessHead = quickSort(lessHead);       // 递归排序小于基准值的部分
    greaterHead = quickSort(greaterHead); // 递归排序大于基准值的部分
    
    return concatenate(lessHead, equalHead, greaterHead);  // 将三部分合并
}

// 打印链表
void printList(ListNode* head) {
    while (head) {
        std::cout << head->value << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // 创建示例链表
    ListNode* head = new ListNode(3);
    head->next = new ListNode(7);
    head->next->next = new ListNode(8);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next = new ListNode(1);
    head->next->next->next->next->next->next = new ListNode(9);
    head->next->next->next->next->next->next->next = new ListNode(6);
    
    std::cout << "排序前链表: ";
    printList(head);
    
    // 执行快速排序
    head = quickSort(head);
    
    std::cout << "排序后链表: ";
    printList(head);
    
    return 0;
}
