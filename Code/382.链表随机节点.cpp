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

// �ҵĽⷨ������ĳ����飬�����������ѡ��Ԫ�ط��أ�ʱ��O(n) 24 ms 34.43%���ռ� O(n) 16.3 MB 29.80%
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

// LeetCode 101�ⷨ��ˮ���㷨��ʱ��O(n) 20 ms 71.31%���ռ�O(1) 16.1 MB 92.38%
// ˼·����ͬ�����飬��δ����������ǰ���޷�֪��������ܳ��ȣ�������Բ���ˮ�������
// ���Ƚ�����ĵ�һ���ڵ�ѡΪ�����Ȼ�����һ�������ڱ�������m���ڵ�ʱ����1/m�ĸ���ѡ������ڵ㸲�ǵ�֮ǰѡ��Ľڵ���Ϊ�����
// ���ڶԳ���Ϊn������ĵ�m���ڵ㣬��󱻲����ĳ�Ҫ����������ѡ����֮��Ľڵ㶼û�б�ѡ��
// ������������ĸ�����(1/m)*[m/(m+1)]*[(m+1)/(m+2)]*...*[(n-1)/n] = 1/n
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