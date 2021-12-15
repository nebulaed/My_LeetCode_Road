#include<iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

// 我的解法：超时
class Solution {
public:
	bool dfs(const unordered_multimap<int, int>& wordMap, int cur, int end) {
		if (cur == end) return true;
		int nums = wordMap.count(cur);
		if (!nums) return false;
		auto it_range = wordMap.equal_range(cur);
		for (auto it = it_range.first; it != it_range.second; ++it) {
			bool ret = dfs(wordMap, it->second, end);
			if (ret) return ret;
		}
		return false;
	}

	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_multimap<int, int> wordMap;
		bool ret = false;
		for (const auto& word : wordDict) {
			size_t begin = 0;
			while ((begin = s.find(word, begin)) != string::npos) {
				wordMap.emplace(begin, begin + word.size());
				if (!ret && begin + word.size() == s.size()) ret = true;
				++begin;
			}
		}
		if (!ret) return false;
		ret = dfs(wordMap, 0, s.size());
		return ret;
	}
};

// 官方解法一：动态规划，时间O(n^2) 12 ms，空间O(n) 13 MB
class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
		int length = s.size();
		bool* dp = new bool[length + 1]();
		dp[0] = true;
		for (int i = 1; i <= length; ++i) {
			for (int j = 0; j < i; ++j) {
				if (dp[j] && wordSet.count(s.substr(j, i - j))) {
					dp[i] = true;
					break;
				}
			}
		}
		return dp[length];
	}
};