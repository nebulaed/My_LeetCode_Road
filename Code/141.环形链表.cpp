#include<iostream>
#include<unordered_set>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

// �ҵĽⷨ1����ϣ��ʱ��O(n) 20 ms���ռ�O(n) 10.2 MB
class Solution {
public:
	bool hasCycle(ListNode* head) {
		unordered_set<ListNode*> nodeList;
		while (head != nullptr) {
			if (nodeList.count(head)) return true;
			else nodeList.emplace(head);
			head = head->next;
		}
		return false;
	}
};

// �ҵĽⷨ2���ƻ��������ݣ�ʱ��O(n) 8 ms���ռ�O(1) 8 MB
class Solution {
public:
	bool hasCycle(ListNode* head) {
		while (head != nullptr) {
			if (head->val == 1e7) return true;
			head->val = 1e7;
			head = head->next;
		}
		return false;
	}
};

// �ٷ��ⷨ2(����˼·��д�汾)������ָ��(Floyd��Ȧ�㷨)��ʱ��O(n) 12 ms���ռ�O(1) 7.9 MB
class Solution {
public:
	bool hasCycle(ListNode* head) {
		if (head == nullptr) return false;
		ListNode* slow = head, * fast = head->next;
		while (slow != fast) {
			if (fast == nullptr) return false;
			slow = slow->next;
			fast = !fast->next ? nullptr : fast->next->next;
		}
		return true;
	}
};

// �ٷ��ⷨ2(�ٷ��汾)������ָ��(Floyd��Ȧ�㷨)��ʱ��O(n) 12 ms���ռ�O(1) 7.9 MB
class Solution {
public:
	bool hasCycle(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return false;
		}
		ListNode* slow = head;
		ListNode* fast = head->next;
		while (slow != fast) {
			if (fast == nullptr || fast->next == nullptr) {
				return false;
			}
			slow = slow->next;
			fast = fast->next->next;
		}
		return true;
	}
};

int main() {

	ListNode* node0 = new ListNode(3);
	ListNode* node1 = new ListNode(2);
	ListNode* node2 = new ListNode(0);
	ListNode* node3 = new ListNode(-4);
	node0->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node1;

	Solution s;
	bool ret = s.hasCycle(node0);
	cout << ret << "\n";

	system("pause");
	return 0;
}