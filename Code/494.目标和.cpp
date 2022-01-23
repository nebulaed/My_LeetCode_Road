#include<iostream>
#include<vector>
#include<numeric>

using std::vector;
using std::accumulate;

// 我的解法一参考官方思路：0-1背包问题，动态规划，时间O(n*neg) 16 ms 52.24%，空间 O(n*neg) 11.8 MB 24.13%
class Solution {
public:
	int findTargetSumWays(vector<int>& nums, int target) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		int neg = sum - target;
		if (neg < 0 || (neg & 1)) return 0;
		neg >>= 1;
		int n = nums.size();
		vector<vector<int>> dp(n + 1, vector<int>(neg + 1, 0));
		dp[0][0] = 1;

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= neg; ++j) {
				if (j < nums[i - 1]) {
					dp[i][j] = dp[i - 1][j];
				}
				else {
					dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
				}
			}
		}
		return dp[n][neg];
	}
};