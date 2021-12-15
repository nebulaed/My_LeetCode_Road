#include<iostream>
#include<unordered_set>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

// �ҵĽⷨһ����ϣ��ʱ��O(n) 16 ms���ռ�O(n) 9.4 MB
//class Solution {
//public:
//	ListNode* detectCycle(ListNode* head) {
//		unordered_set<ListNode*> nodeSet;
//		while (head != nullptr) {
//			if (nodeSet.count(head)) return head;
//			nodeSet.emplace(head);
//			head = head->next;
//		}
//		return nullptr;
//	}
//};


// �ٷ��ⷨ��(���ݹٷ�˼·��д)������ָ�룬ʱ��O(n) 8 ms���ռ�O(1) 7.4 MB
class Solution {
public:
	ListNode* detectCycle(ListNode* head) {
		if (head == nullptr || head->next == nullptr) return nullptr;
		ListNode* slow = head, * fast = head;
		do {
			if (fast == nullptr) return nullptr;
			slow = slow->next;
			fast = fast->next == nullptr ? nullptr : fast->next->next;
		} while (slow != fast);
		ListNode* ptr = head;
		while (slow != ptr) {
			slow = slow->next;
			ptr = ptr->next;
		}
		return ptr;
	}
};

// �ٷ��ⷨ��(�ٷ��汾)������ָ�룬ʱ��O(n) 8 ms���ռ�O(1) 7.6 MB
//class Solution {
//public:
//	ListNode* detectCycle(ListNode* head) {
//		ListNode* slow = head, * fast = head;
//		while (fast != nullptr) {
//			slow = slow->next;
//			if (fast->next == nullptr) {
//				return nullptr;
//			}
//			fast = fast->next->next;
//			if (fast == slow) {
//				ListNode* ptr = head;
//				while (ptr != slow) {
//					ptr = ptr->next;
//					slow = slow->next;
//				}
//				return ptr;
//			}
//		}
//		return nullptr;
//	}
//};

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
	ListNode* ret = s.detectCycle(node0);
	cout << ret->val << "\n";

	system("pause");
	return 0;
}