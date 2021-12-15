#include<iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		bool flag = false;
		ListNode* result = new ListNode;
		ListNode* temp = new ListNode;
		for (ListNode* it = result; l1 != temp || l2 != temp || flag; l1 = l1->next == nullptr ? temp : l1->next, l2 = l2->next == nullptr ? temp : l2->next, it->next = (l1 != temp || l2 != temp || flag) ? new ListNode : nullptr, it = it->next) {
			it->val = flag ? l1->val + l2->val + 1 : l1->val + l2->val;
			if (it->val > 9) {
				it->val -= 10;
				flag = true;
			}
			else {
				flag = false;
			}
		}
		return result;
	}
};


int main()
{
	ListNode l1(2);
	ListNode l1_2(4);
	ListNode l1_3(3);
	l1.next = &l1_2;
	l1_2.next = &l1_3;
	ListNode l2(5);
	ListNode l2_2(6);
	ListNode l2_3(4);
	l2.next = &l2_2;
	l2_2.next = &l2_3;

	Solution s;
	ListNode* result = s.addTwoNumbers(&l1, &l2);
	while (result != nullptr)
	{
		cout << result->val << " ";
		result = result->next;
	}
	cout << endl;

	system("pause");
	return 0;
}