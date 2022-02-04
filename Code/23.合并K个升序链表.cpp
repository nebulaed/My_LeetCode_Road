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

// LeetCode 101�ⷨ�����ȶ��У�ʱ�� 20 ms 80.19%���ռ� 13 MB 60.08%
// �����е�����洢��һ�����ȶ����У�ÿ����ȡ��������ͷ���ڵ�ֵ��С���Ǹ��ڵ㣬ֱ��������������ȡ��Ϊֹ��ע����ΪComp ����Ĭ���Ƕ����ѽ��бȽϲ�ά�ֵ�����ϵ�����������Ҫ��ȡ��С�Ľڵ�ֵ����������Ҫʵ��һ����С�ѣ���˱ȽϺ���Ӧ��ά�ֵݼ���ϵ������operator() �з���ʱ�ô��ںŶ����ǵ�����ϵʱ��С�ںŽ��бȽϡ�
class Comp {
public:
	bool operator() (ListNode* lhs, ListNode* rhs) {
		return lhs->val > rhs->val;
	}
};

class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.empty()) return nullptr;
		// ����С����
		priority_queue<ListNode*, vector<ListNode*>, Comp> q;
		// ����������Ŀ�ͷ�ŵ����ȶ����У����Զ�����ֵ�Ĵ�С����
		for (ListNode* list : lists) {
			if (list) {
				q.emplace(list);
			}
		}
		// ����ͷ�ڵ㣬����ѭ��
		ListNode* dummy = new ListNode(0), * cur = dummy;
		while (!q.empty()) {
			// �����ȶ�����ȡ��ֵ��С�Ľڵ�q.top()�ӵ�cur����
			cur->next = q.top();
			q.pop();
			cur = cur->next;
			// ��cur->next�ǿգ�˵�����������滹�нڵ㣬��cur->next�Ż����ȶ����а�ֵ��С����С����
			if (cur->next) {
				q.emplace(cur->next);
			}
		}
		return dummy->next;
	}
};