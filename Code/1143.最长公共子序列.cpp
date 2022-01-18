#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::string;
using std::vector;
using std::max;
using std::swap;

// LeetCode 101解法：动态规划，时间 O(mn) 24 ms 54.19%，空间 O(mn) 12.7 MB 65.98%
// 思路：定义一个dp数组，其中dp[i]表示到位置i为止的子序列的性质，子序列不必以i结尾。
// dp[i][j]表示到第一个字符串位置i为止，到第二个字符串位置j为止，最长的公共子序列长度。
class Solution {
public:
	int longestCommonSubsequence(string text1, string text2) {
		size_t m = text1.size(), n = text2.size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		for (size_t i = 1; i <= m; ++i) {
			for (size_t j = 1; j <= n; ++j) {
				if (text1[i - 1] == text2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		return dp[m][n];
	}
};

// 评论优化：动态规划+滚动数组，时间 O(mn) 16 ms 90.22%，空间 O(min{m,n}) 6.3 MB 96.07%
class Solution {
public:
	int longestCommonSubsequence(string text1, string text2) {
		size_t m = text1.size(), n = text2.size();
		bool reversed = false;
		if (m < n) {
			swap(m, n);
			reversed = true;
		}
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= m; ++i) {
			// temp先记录下dp[i][0]的数据
			int temp = dp[0];
			for (int j = 1; j <= n; ++j) {
				// 将pre指向temp也就是dp[i-1][j-1]
				int pre = temp;
				// 将temp指向dp[i-1][j]
				temp = dp[j];
				if (reversed ? text1[j - 1] != text2[i - 1] : text1[i - 1] != text2[j - 1]) {
					dp[j] = max(dp[j], dp[j - 1]);
				}
				else {
					dp[j] = pre + 1;
				}
			}
		}
		return dp[n];
	}
};

// 评论解法：类似300题：最长递增子序列的LIS问题，时间 4 ms 99.98%，空间 6.5 MB 94.59%
// 在出现大量重复字符时，对该题不适合使用
class Solution {
public:
	int longestCommonSubsequence(string text1, string text2) {
		// 建立一个vector<int>的数组，相当于array<vector<int>, 26>
		vector<int> record[26];
		// 记录下二十六个字母'a'-'z'出现在text2中的所有位置
		for (int i = 0; i < text2.size(); ++i)
		{
			record[text2[i] - 'a'].emplace_back(i);
		}

		// 记录各长度公共子序列的末尾下标（text2中的下标）
		vector<int> tails;  
		for (auto ch : text1)
		{
			auto& idxs = record[ch - 'a'];
			if (idxs.empty())
				continue;

			if (tails.empty() || idxs.back() > tails.back())
			{
				tails.emplace_back(idxs.back());
			}

			int pos = tails.size();
			for (int i = idxs.size() - 1; i >= 0; i--)
			{
				while (pos > 0 && tails[pos - 1] >= idxs[i]) --pos;
				tails[pos] = idxs[i];
			}
		}
		return tails.size();
	}
};