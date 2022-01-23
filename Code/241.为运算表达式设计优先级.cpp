#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<unordered_map>

using std::vector;
using std::string;
using std::unordered_map;
using std::stoi;
using std::istringstream;

// LeetCode 101解法：分治，时间 8 ms 25.28%，空间 11.4 MB 19.46%
// 思路：以符号为中心，先处理两侧的数学表达式，再处理此运算符号。
// 边界情况为字符串内无运算符号，只有数字
class Solution {
public:
	vector<int> diffWaysToCompute(string expression) {
		vector<int> ret;
		for (int i = 0; i < expression.size(); ++i) {
			char ch = expression[i];
			if (ch == '+' || ch == '-' || ch == '*') {
				vector<int> left = diffWaysToCompute(expression.substr(0, i));
				vector<int> right = diffWaysToCompute(expression.substr(i + 1));
				for (int lnum : left) {
					for (int rnum : right) {
						switch (ch) {
						case '+':
							ret.emplace_back(lnum + rnum);
							break;
						case '-':
							ret.emplace_back(lnum - rnum);
							break;
						case '*':
							ret.emplace_back(lnum * rnum);
							break;
						}
					}
				}
			}
		}
		if (ret.empty()) ret.emplace_back(stoi(expression));
		return ret;
	}
};

// 我的解法：分治+记忆化，时间 0 ms 100%，空间 7 MB 85.69%
class Solution {
private:
	unordered_map<string, vector<int>> record;
	vector<int> divide(const string& expression) {
		auto it = record.find(expression);
		if (it != record.end()) return it->second;
		vector<int> ret;
		for (int i = 0; i < expression.size(); ++i) {
			char ch = expression[i];
			if (ch == '+' || ch == '-' || ch == '*') {
				vector<int> left = divide(expression.substr(0, i));
				vector<int> right = divide(expression.substr(i + 1));
				for (int lnum : left) {
					for (int rnum : right) {
						switch (ch) {
						case '+':
							ret.emplace_back(lnum + rnum);
							break;
						case '-':
							ret.emplace_back(lnum - rnum);
							break;
						case '*':
							ret.emplace_back(lnum * rnum);
							break;
						}
					}
				}
			}
		}
		if (ret.empty()) ret.emplace_back(stoi(expression));
		record.emplace(expression, ret);
		return ret;
	}
public:
	vector<int> diffWaysToCompute(string expression) {
		return divide(expression);
	}
};

// LeetCode 101解法：自下而上的动态规划，时间 0 ms 100%，空间 6.3 MB 98.26%
class Solution {
public:
	vector<int> diffWaysToCompute(string expression) {
		vector<int> data;
		vector<char> ops;
		int num = 0;
		char op = ' ';
		istringstream ss(expression + "+");
		while (ss >> num && ss >> op) {
			data.emplace_back(num);
			ops.emplace_back(op);
		}
		int n = data.size();
		vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>()));
		for (int i = 0; i < n; ++i) {
			for (int j = i; j >= 0; --j) {
				if (i == j) {
					dp[i][j].emplace_back(data[i]);
				}
				else {
					for (int k = j; k < i; ++k) {
						for (int left : dp[j][k]) {
							for (int right : dp[k + 1][i]) {
								int val = 0;
								switch (ops[k]) {
								case '+': val = left + right; break;
								case '-': val = left - right; break;
								case '*': val = left * right; break;
								}
								dp[j][i].emplace_back(val);
							}
						}
					}
				}
			}
		}
		return dp[0][n - 1];
	}
};