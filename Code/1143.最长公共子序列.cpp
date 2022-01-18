#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::string;
using std::vector;
using std::max;
using std::swap;

// LeetCode 101�ⷨ����̬�滮��ʱ�� O(mn) 24 ms 54.19%���ռ� O(mn) 12.7 MB 65.98%
// ˼·������һ��dp���飬����dp[i]��ʾ��λ��iΪֹ�������е����ʣ������в�����i��β��
// dp[i][j]��ʾ����һ���ַ���λ��iΪֹ�����ڶ����ַ���λ��jΪֹ����Ĺ��������г��ȡ�
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

// �����Ż�����̬�滮+�������飬ʱ�� O(mn) 16 ms 90.22%���ռ� O(min{m,n}) 6.3 MB 96.07%
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
			// temp�ȼ�¼��dp[i][0]������
			int temp = dp[0];
			for (int j = 1; j <= n; ++j) {
				// ��preָ��tempҲ����dp[i-1][j-1]
				int pre = temp;
				// ��tempָ��dp[i-1][j]
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

// ���۽ⷨ������300�⣺����������е�LIS���⣬ʱ�� 4 ms 99.98%���ռ� 6.5 MB 94.59%
// �ڳ��ִ����ظ��ַ�ʱ���Ը��ⲻ�ʺ�ʹ��
class Solution {
public:
	int longestCommonSubsequence(string text1, string text2) {
		// ����һ��vector<int>�����飬�൱��array<vector<int>, 26>
		vector<int> record[26];
		// ��¼�¶�ʮ������ĸ'a'-'z'������text2�е�����λ��
		for (int i = 0; i < text2.size(); ++i)
		{
			record[text2[i] - 'a'].emplace_back(i);
		}

		// ��¼�����ȹ��������е�ĩβ�±꣨text2�е��±꣩
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