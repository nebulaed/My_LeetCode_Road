#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// �ҵĽⷨһ��vector�������ڵ㣬�������ӣ�ʱ�� O(n) 4 ms���ռ� O(n) 8.3 MB
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == nullptr) return head;
		ListNode* dummy = new ListNode(0, head);
		ListNode* ptr = dummy;
		vector<ListNode*> nodeVec;
		while (ptr->next != nullptr) {
			nodeVec.emplace_back(ptr->next);
			ptr = ptr->next;
		}
		ptr = dummy;
		size_t nodeNum = nodeVec.size();
		ptr->next = nodeVec[nodeNum - 1];
		nodeVec[0]->next = nullptr;
		for (size_t i = nodeNum - 1; i > 0; --i) {
			nodeVec[i]->next = nodeVec[i - 1];
		}
		return dummy->next;
	}
};

// �ҵĽⷨ��������ָ�룬ʱ��O(n) 4 ms���ռ�O(1) 8 MB
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == nullptr) return head;
		ListNode* tail = head, * prev = nullptr, * ptr = head, *nex;
		while (tail->next != nullptr) tail = tail->next;
		while (prev != tail) {
			nex = ptr->next;
			ptr->next = prev;
			prev = ptr;
			ptr = nex;
		}
		return tail;
	}
};

// �ٷ��ⷨһ��������ʱ��O(n) 0 ms���ռ�O(1) 8 MB
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr, * curr = head;
		while (curr) {
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		return prev;
	}
};


// �ٷ��ⷨ�����ݹ飬ʱ��O(n) 4 ms���ռ�O(n) 8.3 MB
// ��������뵽β�ڵ㣬Ȼ���ڵݹ������ߵĹ��������򽫽ڵ����һ���ڵ��nextָ��ָ��ǰ�ڵ�
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* newHead = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return newHead;
	}
};