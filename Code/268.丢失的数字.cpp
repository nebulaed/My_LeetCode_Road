#include<iostream>
#include<vector>
#include<numeric>

using std::vector;
using std::accumulate;

// �ҵĽⷨһ����˹��͹�ʽ��ʱ�� O(n) 16 ms 74.93%���ռ� O(1) 17.5 MB 58.55%
class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int n = nums.size();
		int expectedSum = (1 + n) * n / 2;
		int realSum = accumulate(nums.begin(), nums.end(), 0);
		return expectedSum - realSum;
	}
};

// �ҵĽⷨ����λ����-���ʱ�� O(n) 12 ms 93.25%���ռ� O(1) 17.4 MB 91.53%
class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int n = nums.size(), ret = 0;
		for (int num : nums) {
			ret ^= num;
		}
		for (int i = 0; i <= n; ++i) {
			ret ^= i;
		}
		return ret;
	}
};