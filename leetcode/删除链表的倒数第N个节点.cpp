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
// 思路： 双指针法，时间On，空间O1
// 1. 一个指针用来指结尾，一个指针用来指倒数第n个节点
// 2. 从开头就让一个指针和另一个指针相隔n个节点
// 3. 这样两个指针同时往结尾走，当靠前的指针指向结尾时，后面的指针指向的就是倒数第n个节点
// 4. 删除该节点即可

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto left = head, right = head; //left为靠近开头的指针，right为靠近结尾的指针
        while(n --) {               //先将right向前走n步
            right = right->next;
            if(right == NULL) {     //因为n小于等于链表长度，所以过程中right不会遍历完链表
                return head->next;  //当向前走n步之后，如果right为空，表明我们要删掉头节点即可
            }
        }
        while(right) {          //然后right持续遍历，直到结尾
            right = right->next;
            if(right == NULL) break;    //此时left所指即为要删除的节点的上一个节点
            left = left->next;            
        }
        auto need_del = left->next;
        left->next = left->next->next;  //将该节点删除即可
        delete(need_del);       //释放被删除节点的空间，可以不写
        return head;
    }
};