#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// �ٷ��ⷨ1��˳��ϲ�
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
		if ((!a) || (!b)) return a ? a : b;
		ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
		while (aPtr && bPtr) {
			if (aPtr->val < bPtr->val) {
				tail->next = aPtr;
				aPtr = aPtr->next;
			}
			else {
				tail->next = bPtr;
				bPtr = bPtr->next;
			}
			tail = tail->next;
		}
		tail->next = aPtr ? aPtr : bPtr;
		return head.next;
	}

	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode* ans = nullptr;
		for (int i = 0; i < lists.size(); ++i) {
			ans = mergeTwoLists(ans, lists[i]);
		}
		return ans;
	}
};

// �ٷ��ⷨ2�����κϲ�
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
		if ((!a) || (!b)) return a ? a : b;
		ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
		while (aPtr && bPtr) {
			if (aPtr->val < bPtr->val) {
				tail->next = aPtr;
				aPtr = aPtr->next;
			}
			else {
				tail->next = bPtr;
				bPtr = bPtr->next;
			}
			tail = tail->next;
		}
		tail->next = aPtr ? aPtr : bPtr;
		return head.next;
	}

	ListNode* merge(vector<ListNode*>& lists, int l, int r) {
		if (l == r) return lists[l];
		if (l > r) return nullptr;
		// (l + r) >> 1��ʾ(l + r)�Ķ�����������һλ, �൱�ڳ���2
		int mid = (l + r) / 2;
		return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
	}

	ListNode* mergeKLists(vector<ListNode*>& lists) {
		return merge(lists, 0, lists.size() - 1);
	}
};