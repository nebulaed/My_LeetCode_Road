#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using std::swap;
using std::string;
using std::vector;
using std::max;

// 我的解法1：动态规划，时间O(mn) 24 ms 64%，空间 O(mn) 12 MB 30%
class Solution {
public:
	int minDistance(string word1, string word2) {
		size_t m = word1.size(), n = word2.size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		for (size_t i = 1; i <= m; ++i) {
			for (size_t j = 1; j <= n; ++j) {
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		return m + n - 2 * dp[m][n];
	}
};

// 我的解法2：动态规划+滚动数组，时间O(mn) 8 ms 99.19%，空间O(min(m,n)) 6.6 MB 98.27%
class Solution {
public:
	int minDistance(string word1, string word2) {
		size_t m = word1.size(), n = word2.size();
		bool reversed = false;
		if (m < n) {
			swap(m, n);
			reversed = true;
		}
		vector<int> dp(n + 1, 0);
		for (size_t i = 1; i <= m; ++i) {
			int temp = dp[0];
			for (size_t j = 1; j <= n; ++j) {
				int pre = temp;
				temp = dp[j];
				if (reversed ? word1[j - 1] != word2[i - 1] : word1[i - 1] != word2[j - 1]) {
					dp[j] = max(dp[j], dp[j - 1]);
				}
				else {
					dp[j] = pre + 1;
				}
			}
		}
		return m + n - 2 * dp.back();
	}
};