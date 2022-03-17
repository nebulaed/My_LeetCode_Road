#include<iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// �ٷ��ⷨһ���Զ����¹鲢����ʱ��O(n log n) 68 ms���ռ�O(log n) 29.6 MB
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

// �ٷ��ⷨ�����Ե����Ϲ鲢����ʱ��O(n log n) 72 ms���ռ�O(1) 29.8 MB
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

// �ҵĽⷨ���ο��ٷ��ⷨһ��ʱ�� O(n log n) 80 ms 85.56%���ռ� O(log n) 47.4 MB 38.95%
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

// �ҵĽⷨ���ο��ٷ��ⷨ�����Ե����Ϲ鲢����ʱ�� O(n log n) 72 ms 96.45%���ռ� O(1) 31.7 MB 62.41%
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
		// ���������ܳ���
		while (node != nullptr) {
			++length;
			node = node->next;
		}
		ListNode* dummy = new ListNode(0, head);
		for (int subLength = 1; subLength < length; subLength <<= 1) {
			ListNode* prev = dummy, * curr = dummy->next;
			while (curr != nullptr) {
				// ��subLength���ȵ�������1���зָ�
				ListNode* head1 = curr;
				for (int i = 1; i < subLength && curr->next != nullptr; ++i) {
					curr = curr->next;
				}
				// ��subLength���ȵ�������2���зָ�
				ListNode* head2 = curr->next;
				curr->next = nullptr;
				curr = head2;
				// �ҵ�������2�����һ���ڵ�
				for (int i = 1; i < subLength && curr && curr->next; ++i) {
					curr = curr->next;
				}
				// ��¼��curr->next����2 * subLength���Ⱥ�ĵ�һ���ڵ�
				ListNode* next = nullptr;
				if (curr) {
					next = curr->next;
					curr->next = nullptr;
				}
				// �ϲ�������������
				ListNode* merged = merge(head1, head2);
				// ֮ǰ�����һ���ڵ��뵱ǰ�����������һ���ڵ����
				prev->next = merged;
				// ��curr��Ϊ�գ�prevֱ������curr�������һ���ڵ����
				if (curr) prev = curr;
				// �ҵ���ǰ�����һ���ڵ㣬����prev
				while (prev->next) {
					prev = prev->next;
				}
				curr = next;
			}
		}
		return dummy->next;
	}
};