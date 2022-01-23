#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;

// �ҵĽⷨ�ο�һ��ٷ�˼·����̬�滮��ʱ�� 0 ms 100%���ռ� 7.7 MB 36%
// ˼·����i=0��n-1��198��ķ�����dp�������һ�Σ��ٽ�i=1��n�������198�ⷽ����dp�������һ�Σ�ȡ�������ֵ
class Solution {
public:
	int rob(vector<int>& nums) {
		const size_t n = nums.size();
		if (n == 1) return nums[0];
		if (n == 2) return max(nums[0], nums[1]);
		vector<int> dp(n - 1);
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);
		for (size_t i = 2; i < n - 1; ++i) {
			dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
		}
		int ret = dp.back();
		dp[0] = nums[1];
		dp[1] = max(nums[1], nums[2]);
		for (size_t i = 2; i < n - 1; ++i) {
			dp[i] = max(dp[i - 2] + nums[i + 1], dp[i - 1]);
		}
		return max(ret, dp.back());
	}
};
// ���������Ż��棺ʱ�� 0 ms 100%���ռ� 7.8 MB 17%
class Solution {
public:
	int rob(vector<int>& nums) {
		const size_t n = nums.size();
		int nums0 = nums.front();
		if (n == 1) return nums0;
		int nums1 = nums[1];
		if (n == 2) return max(nums0, nums1);
		vector<int> dp(n - 1);
		int first = nums0, second = max(nums0, nums1);
		for (size_t i = 2; i < n - 1; ++i) {
			int temp = second;
			second = max(first + nums[i], second);
			first = temp;
		}
		int ret = second;
		first = nums1;
		second = max(nums1, nums[2]);
		for (size_t i = 2; i < n - 1; ++i) {
			int temp = second;
			second = max(first + nums[i + 1], second);
			first = temp;
		}
		return max(ret, second);
	}
};