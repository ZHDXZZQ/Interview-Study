// 思路：小根堆优先队列，归并原理，k长度的优先队列插入删除Ologk，总共时间复杂度Onklogk，空间复杂度Ok
// 1. 构建一个小根堆，将每个链表的头节点入堆
// 2. 堆顶为当前各链表头节点的最小元素，每次摘出堆顶到答案
// 3. 摘出后如果该节点所在链表还有后续节点，就让后续节点入堆

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		struct cmp {
			bool operator()(ListNode* a, ListNode* b) {
				return a->val > b->val;  //这里，左大于右是小根堆，反过来是大根堆
			}
		};  //优先队列的比较类：重载()运算符通过仿函数实现小根堆
		priority_queue<ListNode*, vector<ListNode*>, cmp> rec;
		//不加cmp默认构造int型大根堆。第一个参数为该优先队列的类型；第二个参数为存储第一个参数类型所用的容器且必须是vector或queue等数组实现的容器；第三个参数是比较方式，比如less<int>（less是默认的大根堆）或greater<int>或者这种非int型要用cmp类构造。
		//优先队列的操作类似栈，push，top，pop
		ListNode* head = new ListNode();
		auto tail = head;
		for(auto x: lists) if(x) rec.push(x);  //各链表头入堆自动排序，堆顶为最小
		while(rec.size()) {  //只要堆不空
			tail->next = rec.top();  //将堆顶的最小元素接到答案数组
			tail = tail->next;  
			auto cur = rec.top();  //取出最小元素
			rec.pop();
			if(cur->next) rec.push(cur->next);  //如果该最小元素所在链表还没完，则把该最小元素的下一个节点入堆排序，有点像归并
		}
		auto res = head->next;
		return res;
	}
};