#include<iostream>
#include<vector>

using std::vector;
using std::swap;
using std::move;

// LeetCode 101�ⷨһ��Fisher-Yatesϴ���㷨������ϴ�ƣ�ʱ�� 112 ms 36.93%���ռ� 88.1 MB 65.02%
// ԭ����ͨ���������λ����ʵ���������
class Solution {
private:
	vector<int> memory;
public:
	Solution(vector<int>& nums) : memory(nums) {}
	// ʹ��std::move�ܰ�ʱ��ӿ쵽96 ms 77.71%
	//Solution(vector<int>& nums) : memory(move(nums)) {}

	vector<int> reset() {
		return memory;
	}

	vector<int> shuffle() {
		if (memory.empty()) return {};
		vector<int> shuffled(memory);
		int n = memory.size();
		// ����ϴ��
		for (int i = 0; i < n; ++i) {
			int pos = rand() % (n - i);
			swap(shuffled[i], shuffled[i + pos]);
		}
		return shuffled;
	}
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */

// LeetCode 101�ⷨ����Fisher-Yatesϴ���㷨������ϴ�ƣ�ʱ�� 116 ms 29.94%���ռ� 88 MB 83.66%
class Solution {
private:
	vector<int> memory;
public:
	Solution(vector<int>& nums) : memory(nums) {}
	// ʹ��std::move��ʱ�� 100 ms 67.10%���ռ� 88.2 MB 22.06%
	//Solution(vector<int>& nums) : memory(move(nums)) {}

	vector<int> reset() {
		return memory;
	}

	vector<int> shuffle() {
		if (memory.empty()) return {};
		vector<int> shuffled(memory);
		int n = memory.size();
		// ����ϴ��
		for (int i = n - 1; i >= 0; --i) {
			swap(shuffled[i], shuffled[rand() % (i + 1)]);
		}
		return shuffled;
	}
};
