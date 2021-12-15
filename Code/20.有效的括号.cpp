#include<iostream>
#include<stack>
#include<unordered_map>
using namespace std;

// 我的解法
class Solution {
public:
	bool isValid(string s) {
		stack<char> stk;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
				stk.push(s[i]);
			}
			else if (s[i] == ')') {
				if (!stk.empty() && stk.top() == '(') {
					stk.pop();
				}
				else return false;
			}
			else if (s[i] == ']') {
				if (!stk.empty() && stk.top() == '[') {
					stk.pop();
				}
				else return false;
			}
			else if (s[i] == '}') {
				if (!stk.empty() && stk.top() == '{') {
					stk.pop();
				}
				else return false;
			}
			else return false;
		}
		if (stk.empty()) return true;
		else return false;
	}
};

// 官方解法(思路相同，有小优化)
class Solution {
private:
	unordered_map<char, char> pairs = {
		{')','('},
		{']','['},
		{'}','{'}
	};
public:
	bool isValid(string s) {
		int n = s.size();
		if (n % 2 == 1) return false;
		stack<char> stk;
		for (int i = 0; i < s.size(); ++i) {
			if (pairs.count(s[i])) {
				if (stk.empty() || stk.top() != pairs[s[i]]) {
					return false;
				}
				stk.pop();
			}
			else {
				stk.push(s[i]);
			}
		}
		return stk.empty();
	}
};

int main() {
	string s = "([)]";

	Solution sol;
	bool ret = sol.isValid(s);

	cout << ret << endl;
	system("pause");
	return 0;
}