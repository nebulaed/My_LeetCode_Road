#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一：排序+动态规划，时间 68 ms，空间 13.9 MB
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		sort(coins.begin(), coins.end());
		vector<int> dp(amount + 1, 0);
		for (int i = 1; i <= amount; ++i) {
			int minStep = INT_MAX;
			for (int j = 0; j < coins.size() && i - coins[j] >= 0; ++j) {
				int temp = dp[i - coins[j]];
				if (temp != -1) {
					minStep = min(minStep, temp);
				}
			}
			dp[i] = minStep == INT_MAX ? -1 : minStep + 1;
		}
		return amount == 0 ? 0 : dp[amount];
	}
};

// 我的解法一变式：动态规划，时间 68 ms，空间 14 MB
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount + 1, 0);
		for (int i = 1; i <= amount; ++i) {
			int minStep = INT_MAX;
			for (int j = 0; j < coins.size(); ++j) {
				if (i - coins[j] < 0) continue;
				int temp = dp[i - coins[j]];
				if (temp != -1) {
					minStep = min(minStep, temp);
				}
			}
			dp[i] = minStep == INT_MAX ? -1 : minStep + 1;
		}
		return amount == 0 ? 0 : dp[amount];
	}
};

// 官方解法一：记忆化搜索，时间O(Sn) 80 ms，空间O(S) 15.6 MB
// 定义F(S)为组成金额S所需的最少硬币数量，[c0 ... cn-1]为可选的n枚硬币面额值
// 假定最后一枚硬币面值是C，则转移方程为F(S) = F(S-C) + 1
// 但我们不知道最后一枚硬币C是多少，需要枚举每个硬币面额值c0,c1,...,cn-1并选择其中F(S-C)最小的面额值。
class Solution {
private:
	vector<int> count;

	int dp(const vector<int>& coins, int rem) {
		if (rem < 0) return -1;
		else if (rem == 0) return 0;
		// 若该值已被计算过，只需直接调用count数组里存放的对应该值的硬币数
		if (count[rem - 1] != 0) return count[rem - 1];
		int minNum = INT_MAX;
		for (int coin : coins) {
			int ret = dp(coins, rem - coin);
			if (ret >= 0 && ret < minNum) {
				minNum = ret + 1;
			}
		}
		count[rem - 1] = minNum == INT_MAX ? -1 : minNum;
		return count[rem - 1];
	}
public:
	int coinChange(vector<int>& coins, int amount) {
		if (amount < 1) return 0;
		count.resize(amount);
		return dp(coins, amount);
	}
};

// 官方解法二：动态规划，时间O(Sn) 80 ms，空间O(S) 14 MB
// 采用自下而上的方式思考。F(i)定义与上相同，F(i)的转移方程为
// F(i) = min_(j = 0,...,n-1) (F(i-c_j)) + 1
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		int overVal = amount + 1;
		vector<int> dp(overVal, overVal);
		dp[0] = 0;
		for (int i = 1; i <= amount; ++i) {
			for (int j = 0; j < coins.size(); ++j) {
				if (coins[j] <= i) {
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
				}
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];
	}
};