#include<iostream>
#include<stack>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// �ҵĽⷨ=�ٷ��ⷨ1������������
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		int length = 0;
		ListNode* p, * q;
		p = head;
		while (p) {
			p = p->next;
			++length;
		}
		cout << length << endl;
		int pos_n = length + 1 - n;
		cout << pos_n << endl;
		int i = 1;
		p = head;
		while (p && i < pos_n - 1) {
			p = p->next;
			++i;
		}
		cout << i << endl;
		if (i > pos_n - 1) {
			return head->next;
		}
		q = p->next;
		p->next = q->next;
		return head;
	}
};

// �ٷ��ⷨ2��ջ
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// ����һ��ͷ���
		ListNode* dummy = new ListNode(0, head);
		stack<ListNode*> stk;
		ListNode* cur = dummy;
		while (cur) {
			stk.push(cur);
			cur = cur->next;
		}
		for (int i = 0; i < n; ++i) {
			stk.pop();
		}
		ListNode* prev = stk.top();
		ListNode* temp = prev->next;
		prev->next = prev->next->next;
		ListNode* ans = dummy->next;
		delete dummy, temp;
		return ans;
	}
};

// �ٷ��ⷨ3��˫ָ��(����ָ��)
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* dummy = new ListNode(0, head);
		ListNode* first = head;
		ListNode* second = dummy;
		for (int i = 0; i < n; ++i) {
			first = first->next;
		}
		while (first) {
			first = first->next;
			second = second->next;
		}
		ListNode* temp = second->next;
		second->next = second->next->next;
		ListNode* ans = dummy->next;
		delete dummy, temp;
		return ans;
	}
};

// �ҵĵڶ��νⷨ������ָ�룬ʱ�� 4 ms 77.33%���ռ� 10.5 MB 13.80%
class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (!head->next) return nullptr;
		ListNode* dummy = new ListNode(0, head);
		ListNode* slow = dummy, * fast = head;
		while (n--) {
			fast = fast->next;
		}
		while (fast) {
			slow = slow->next;
			fast = fast->next;
		}
		ListNode* temp = slow->next;
		slow->next = slow->next->next;
		delete temp;
		return dummy->next;
	}
};

int main() {

}