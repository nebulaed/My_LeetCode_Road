#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;

// 官方解法一：回溯+剪枝，时间O(n×2^n) 4 ms，空间O(n^2) 7.5 MB
class Solution {
private:
	vector<string> ret;

	void dfs(string str, int start, int leftRemove, int rightRemove) {
		if (leftRemove == 0 && rightRemove == 0) {
			if (isValid(str)) {
				ret.emplace_back(str);
			}
			return;
		}
		for (int i = start; i < str.size(); ++i) {
			// 遇到连续相同字符，只需搜索一次即可
			if (i != start && str[i] == str[i - 1]) {
				continue;
			}
			// 若剩余字符无法满足删除的数量要求，直接返回
			if (leftRemove + rightRemove > str.size() - i) {
				return;
			}
			// 尝试去掉一个左括号
			if (leftRemove > 0 && str[i] == '(') {
				dfs(str.substr(0, i) + str.substr(i + 1), i, leftRemove - 1, rightRemove);
			}
			// 尝试去掉一个右括号
			if (rightRemove > 0 && str[i] == ')') {
				dfs(str.substr(0, i) + str.substr(i + 1), i, leftRemove, rightRemove - 1);
			}
		}
	}

	inline bool isValid(const string& str) {
		int cnt = 0;

		for (char c : str) {
			if (c == '(') {
				++cnt;
			}
			else if (c == ')') {
				--cnt;
				if (cnt < 0) {
					return false;
				}
			}
		}
		return cnt == 0;
	}
public:
	vector<string> removeInvalidParentheses(string s) {
		int leftRemove = 0;
		int rightRemove = 0;

		// 遍历后得知应该删除的左括号、右括号数量
		for (char c : s) {
			if (c == '(') {
				++leftRemove;
			}
			else if (c == ')') {
				if (leftRemove == 0) {
					++rightRemove;
				}
				else {
					--leftRemove;
				}
			}
		}
		dfs(s, 0, leftRemove, rightRemove);
		return ret;
	}
};

// 官方解法二：BFS，时间O(n×2^n) 64 ms，空间O(n×C^(n/2)_n) 24.3 MB
// 思路：进行BFS时每轮删除字符串中的1个括号，直到出现合法匹配的字符串为止，此时进行轮转的次数即为最少需要删除括号的个数
// 进行BFS时，每次保存上一轮搜索的结果，然后对上一轮已经保存的结果中每一个字符串尝试所有可能的删除一个括号的方法
// 然后将保存的结果进行下一轮搜索。保存结果时可以利用哈希表去重
class Solution {
private:
	inline bool isValid(const string& str) {
		int cnt = 0;

		for (char c : str) {
			if (c == '(') {
				++cnt;
			}
			else if (c == ')') {
				--cnt;
				if (cnt < 0) {
					return false;
				}
			}
		}
		return cnt == 0;
	}
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> ret;
		unordered_set<string> currSet;

		currSet.emplace(s);
		while (true) {
			for (const auto& str : currSet) {
				if (isValid(str)) {
					ret.emplace_back(str);
				}
			}
			if (ret.size() > 0) return ret;
			unordered_set<string> nextSet;
			for (const auto& str : currSet) {
				for (size_t i = 0; i < str.size(); ++i) {
					if (i > 0 && str[i] == str[i - 1]) {
						continue;
					}
					if (str[i] == '(' || str[i] == ')') {
						nextSet.emplace(str.substr(0, i) + str.substr(i + 1, str.size()));
					}
				}
			}
			currSet = nextSet;
		}
	}
};