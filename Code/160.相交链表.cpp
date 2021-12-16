#include<iostream>
#include<unordered_set>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

// �ҵĽⷨ=�ٷ��ⷨ1����ϣ���ϣ�48 ms��16.8 MB
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

// �ٷ��ⷨ����˫ָ�룬ʱ��O(m+n) 44 ms���ռ�O(1) 14.3 MB
// ������headA��headB ����Ϊ��ʱ����������ָ��pA ��pB����ʼʱ�ֱ�ָ�����������ͷ�ڵ�headA ��headB��Ȼ������ָ�����α������������ÿ���ڵ㡣
// ÿ��������Ҫͬʱ����ָ��pA ��pB��
// ���ָ��pA ��Ϊ�գ���ָ��pA �Ƶ���һ���ڵ㣻���ָ��pB ��Ϊ�գ���ָ��pB �Ƶ���һ���ڵ㡣
// ���ָ��pA Ϊ�գ���ָ��pA �Ƶ�����headB ��ͷ�ڵ㣻���ָ��pB Ϊ�գ���ָ��pB �Ƶ����� headA ��ͷ�ڵ㡣
// ��ָ��pA ��pB ָ��ͬһ���ڵ���߶�Ϊ��ʱ����������ָ��Ľڵ��null
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