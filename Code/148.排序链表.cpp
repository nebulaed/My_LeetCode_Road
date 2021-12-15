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

// 官方解法二：自底向上归并排序，时间O(n log n) 68 ms，空间O(1) 29.6 MB
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
			}
		}
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
