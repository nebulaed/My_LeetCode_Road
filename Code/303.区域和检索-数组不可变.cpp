#include<iostream>
#include<vector>
#include<numeric>

using std::vector;
using std::partial_sum;

// �ҵĽⷨ��ǰ׺�ͣ�ʱ�� 20 ms 78.90%���ռ� 16.7 MB 31.61%
class NumArray {
private:
	vector<int> prefixSum;
public:
	NumArray(vector<int>& nums) : prefixSum(nums) {
		int n = prefixSum.size();
		for (int i = 1; i < n; ++i) {
			prefixSum[i] += prefixSum[i - 1];
		}
	}

	int sumRange(int left, int right) {
		return prefixSum[right] - (left == 0 ? 0 : prefixSum[left - 1]);
	}
};

// LeetCode 101�ⷨ��ǰ׺�ͣ�ʱ�� 24 ms 51.90%���ռ� 16.7 MB 17.46%
class NumArray {
private:
	vector<int> prefixSum;
public:
	NumArray(vector<int>& nums) : prefixSum(nums.size() + 1, 0) {
		partial_sum(nums.begin(), nums.end(), prefixSum.begin() + 1);
	}

	int sumRange(int left, int right) {
		return prefixSum[right + 1] - prefixSum[left];
	}
};