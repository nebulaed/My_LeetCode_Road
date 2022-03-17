#include<iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 官方解法一：自顶向下归并排序，时间O(n log n) 68 ms，空间O(log n) 29.6 MB
class Solution {
public:
	ListNode* sortList(ListNode* head) {
		return sortList(head, nullptr);
	}

	ListNode* sortList(ListNode* head, ListNode* tail) {
		if (head == nullptr) {
			return head;
		}
		if (head->next == tail) {
			head->next = nullptr;
			return head;
		}
		ListNode* slow = head, * fast = head;
		while (fast != tail) {
			slow = slow->next;
			fast = fast->next;
			if (fast != tail) {
				fast = fast->next;
			}
		}
		ListNode* mid = slow;
		return mergeTwoLists(sortList(head, mid), sortList(mid, tail));
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) {
			return l2;
		}
		else if (l2 == nullptr) {
			return l1;
		}
		else if (l1->val < l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}
};

// 官方解法二：自底向上归并排序，时间O(n log n) 72 ms，空间O(1) 29.8 MB
class Solution {
public:
	ListNode* sortList(ListNode* head) {
		if (head == nullptr) return head;
		int length = 0;
		ListNode* node = head;
		while (node != nullptr) {
			++length;
			node = node->next;
		}
		ListNode* dummy = new ListNode(0, head);
		for (int subLength = 1; subLength < length; subLength <<= 1) {
			ListNode* prev = dummy, * curr = dummy->next;
			while (curr != nullptr) {
				ListNode* head1 = curr;
				for (int i = 1; i < subLength && curr->next != nullptr; ++i) {
					curr = curr->next;
				}
				ListNode* head2 = curr->next;
				curr->next = nullptr;
				curr = head2;
				for (int i = 1; i < subLength && curr != nullptr && curr->next != nullptr; ++i) {
					curr = curr->next;
				}
				ListNode* next = nullptr;
				if (curr != nullptr) {
					next = curr->next;
					curr->next = nullptr;
				}
				ListNode* merged = mergeTwoLists(head1, head2);
				prev->next = merged;
				while (prev->next != nullptr) {
					prev = prev->next;
				}
				curr = next;
			}
		}
		return dummy->next;
	}

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) {
			return l2;
		}
		else if (l2 == nullptr) {
			return l1;
		}
		else if (l1->val < l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}
};

// 我的解法：参考官方解法一，时间 O(n log n) 80 ms 85.56%，空间 O(log n) 47.4 MB 38.95%
class Solution {
private:
	ListNode* merge(ListNode* l1, ListNode* l2) {
		ListNode* dummy = new ListNode(), * node = dummy;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				node->next = l1;
				l1 = l1->next;
			}
			else {
				node->next = l2;
				l2 = l2->next;
			}
			node = node->next;
		}
		node->next = l1 ? l1 : l2;
		return dummy->next;
	}
public:
	ListNode* sortList(ListNode* head, ListNode* tail = nullptr) {
		if (!head) return head;
		if (head->next == tail) {
			head->next = nullptr;
			return head;
		}
		ListNode* slow = head, * fast = head;
		while (fast != tail) {
			slow = slow->next;
			fast = fast->next;
			if (fast != tail) {
				fast = fast->next;
			}
		}
		ListNode* mid = slow;
		return merge(sortList(head, mid), sortList(mid, tail));
	}
};

// 我的解法：参考官方解法二，自底向上归并排序，时间 O(n log n) 72 ms 96.45%，空间 O(1) 31.7 MB 62.41%
class Solution {
private:
	ListNode* merge(ListNode* l1, ListNode* l2) {
		ListNode* dummy = new ListNode(), * node = dummy;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				node->next = l1;
				l1 = l1->next;
			}
			else {
				node->next = l2;
				l2 = l2->next;
			}
			node = node->next;
		}
		node->next = l1 ? l1 : l2;
		return dummy->next;
	}
public:
	ListNode* sortList(ListNode* head) {
		int length = 0;
		ListNode* node = head;
		// 计算链表总长度
		while (node != nullptr) {
			++length;
			node = node->next;
		}
		ListNode* dummy = new ListNode(0, head);
		for (int subLength = 1; subLength < length; subLength <<= 1) {
			ListNode* prev = dummy, * curr = dummy->next;
			while (curr != nullptr) {
				// 对subLength长度的子链表1进行分割
				ListNode* head1 = curr;
				for (int i = 1; i < subLength && curr->next != nullptr; ++i) {
					curr = curr->next;
				}
				// 对subLength长度的子链表2进行分割
				ListNode* head2 = curr->next;
				curr->next = nullptr;
				curr = head2;
				// 找到子链表2的最后一个节点
				for (int i = 1; i < subLength && curr && curr->next; ++i) {
					curr = curr->next;
				}
				// 记录下curr->next，即2 * subLength长度后的第一个节点
				ListNode* next = nullptr;
				if (curr) {
					next = curr->next;
					curr->next = nullptr;
				}
				// 合并两个有序链表
				ListNode* merged = merge(head1, head2);
				// 之前的最后一个节点与当前已排序链表第一个节点接上
				prev->next = merged;
				// 若curr不为空，prev直接跳到curr，离最后一个节点更近
				if (curr) prev = curr;
				// 找到当前的最后一个节点，赋给prev
				while (prev->next) {
					prev = prev->next;
				}
				curr = next;
			}
		}
		return dummy->next;
	}
};