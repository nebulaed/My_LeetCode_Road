#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ����̬�滮��ʱ��O(n) 0 ms���ռ�O(n) 7.6 MB
class Solution {
public:
	int rob(vector<int>& nums) {
		const size_t n = nums.size();
		if (n == 1) return nums[0];
		if (n == 2) return max(nums[0], nums[1]);
		vector<int> dp(n);
		dp[0] = nums[0];
		dp[1] = nums[1];
		dp[2] = nums[0] + nums[2];
		int maxMoney = dp[2] > dp[1] ? dp[2] : dp[1];
		for (size_t i = 3; i < n; ++i) {
			dp[i] = max(dp[i - 2], dp[i - 3]) + nums[i];
			maxMoney = max(dp[i], maxMoney);
		}
		return maxMoney;
	}
};

// �ҵĽⷨ����̬�滮+�������飬ʱ��O(n) 0 ms���ռ�O(1) 7.4 MB
class Solution {
public:
	int rob(vector<int>& nums) {
		const size_t n = nums.size();
		if (n == 1) return nums[0];
		if (n == 2) return max(nums[0], nums[1]);
		int first = nums[0], second = nums[1], third = nums[0] + nums[2];
		int maxMoney = max(third, second);
		for (size_t i = 3; i < n; ++i) {
			int temp = third;
			third = max(first, second) + nums[i];
			maxMoney = max(third, maxMoney);
			first = second;
			second = temp;
		}
		return maxMoney;
	}
};

// �ٷ��ⷨ����̬�滮+�������飬ʱ��O(n) 4 ms���ռ�O(1) 7.4 MB
class Solution {
public:
	int rob(vector<int>& nums) {
		const size_t size = nums.size();
		if (size == 1) return nums[0];
		int first = nums[0], second = max(nums[0], nums[1]);
		for (size_t i = 2; i < size; ++i) {
			int temp = second;
			second = max(first + nums[i], second);
			first = temp;
		}
		return second;
	}
};