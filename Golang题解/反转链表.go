/*
	思路： 递归，时间On，空间On
	1. 获取一个节点，这个节点应该是其后链表的反转后的头节点
	2. 将当前节点的next节点的next指向当前节点，其实就是指针变向
	3. 再令当前链表的next指空，再上一次递归中，这个指针会指向前一个节点，这里主要是为当前头节点做考虑的，因为递归的写法无法方便操作原始头节点
	4. 返回新的头节点，作为前一个节点的后边的链表反转后的链表的头节点
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
 func reverseList(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {	// 链表为空或者到达尾部，无需反转直接返回尾节点
        return head
    }
    new_head := reverseList(head.Next)	// 获取后边链表的反转后的头节点
    head.Next.Next = head  	// 将指针反转，当前节点即接入了后半部分反转后的链表，成为了新的尾节点
    head.Next = nil	// 当前节点置空，在上一层递归会指向前置节点
    return new_head	// 返回新的头节点，其实就是原始尾节点
}
