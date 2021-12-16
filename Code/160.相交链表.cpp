#include<iostream>
#include<unordered_set>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

// 我的解法=官方解法1，哈希集合，48 ms，16.8 MB
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		ListNode* ptr1 = headA, * ptr2 = headB;
		unordered_set<ListNode*> ptrSet;
		while (ptr1 != nullptr) {
			ptrSet.emplace(ptr1);
			ptr1 = ptr1->next;
		}
		while (ptr2 != nullptr) {
			if (ptrSet.count(ptr2)) return ptr2;
			ptr2 = ptr2->next;
		}
		return ptr2;
	}
};

// 官方解法二：双指针，时间O(m+n) 44 ms，空间O(1) 14.3 MB
// 当链表headA和headB 都不为空时，创建两个指针pA 和pB，初始时分别指向两个链表的头节点headA 和headB，然后将两个指针依次遍历两个链表的每个节点。
// 每步操作需要同时更新指针pA 和pB。
// 如果指针pA 不为空，则将指针pA 移到下一个节点；如果指针pB 不为空，则将指针pB 移到下一个节点。
// 如果指针pA 为空，则将指针pA 移到链表headB 的头节点；如果指针pB 为空，则将指针pB 移到链表 headA 的头节点。
// 当指针pA 和pB 指向同一个节点或者都为空时，返回它们指向的节点或null
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		if (headA == nullptr || headB == nullptr) return nullptr;
		ListNode* ptrA = headA, * ptrB = headB;
		while (ptrA != ptrB) {
			ptrA = ptrA == nullptr ? headB : ptrA->next;
			ptrB = ptrB == nullptr ? headA : ptrB->next;
		}
		return ptrA;
	}
};