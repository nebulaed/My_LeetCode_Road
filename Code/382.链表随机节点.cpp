#include<iostream>
#include<vector>

using std::vector;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：链表改成数组，在数组中随机选择元素返回，时间O(n) 24 ms 34.43%，空间 O(n) 16.3 MB 29.80%
class Solution {
private:
	vector<int> nums;
public:
	Solution(ListNode* head) {
		while (head != nullptr) {
			nums.emplace_back(head->val);
			head = head->next;
		}
	}

	int getRandom() {
		return nums[rand() % nums.size()];
	}
};

// LeetCode 101解法：水库算法，时间O(n) 20 ms 71.31%，空间O(1) 16.1 MB 92.38%
// 思路：不同于数组，在未遍历完链表前，无法知道链表的总长度，这里可以采用水库采样：
// 首先将链表的第一个节点选为结果，然后遍历一次链表，在遍历到第m个节点时，有1/m的概率选择这个节点覆盖掉之前选择的节点作为结果。
// 由于对长度为n的链表的第m个节点，最后被采样的充要条件是它被选择，且之后的节点都没有被选择。
// 这种情况发生的概率是(1/m)*[m/(m+1)]*[(m+1)/(m+2)]*...*[(n-1)/n] = 1/n
class Solution {
private:
	ListNode* listHead;
public:
	Solution(ListNode* head) : listHead(head) {}

	int getRandom() {
		int ret = listHead->val;
		ListNode* node = listHead->next;
		int i = 2;
		while (node) {
			if (rand() % i == 0) {
				ret = node->val;
			}
			++i;
			node = node->next;
		}
		return ret;
	}
};