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

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable; // 哈希函数构建的map
		for (int i = 0; i < nums.size(); i++) {
			unordered_map<int, int>::iterator it = hashtable.find(target - nums[i]); // 查找 target - nums[i]，找到为所在的迭代器，找不到为末尾迭代器
			if (it != hashtable.end()) {
				return { it->second, i };
			}
			hashtable.insert(pair<int, int>(nums[i], i)); // 若未找到则插入当前nums[i]
		}
		return {}; // 未找到则返回空
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

//int main() {
//	vector<int> input = { 0,4,3,0 };
//	vector<int> output;
//	int target = 0;
//
//	Solution s;
//	output = s.twoSum(input, target);
//
//	for (int i = 0; i < output.size(); i++) {
//		printf("%d ", output[i]);
//	}
//	printf("\n");
//
//	system("pause");
//	return 0;
//}