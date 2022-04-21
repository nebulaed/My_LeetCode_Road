#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

// 官方解法1：动态规划
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxLen = 0, n = s.size();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                }
                else if(i - dp[i-1] > 0 && s[i-dp[i-1]-1]=='('){
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                if (dp[i] > maxLen) maxLen = dp[i];
            }
        }
        return maxLen;
    }
};

// 官方解法2：栈
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = 0;
        int maxLen = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ')') {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                }
                else {
                    len = i - stk.top();
                    if (len > maxLen) maxLen = len;
                }
            }
            else {
                stk.push(i);
            }
        }
        return maxLen;
    }
};

// 官方解法3：left、right双计数器
class Solution {
public:
    int longestValidParentheses(string s) {
        int left = 0, right = 0, maxLen = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                ++left;
            }
            else {
                ++right;
            }
            if (left == right) {
                if (2 * right > maxLen) maxLen = 2 * right;
            }
            else if (right > left) {
                left = right = 0;
            }
        }
        left = right = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == '(') {
                ++left;
            }
            else {
                ++right;
            }
            if (left == right) {
                if (2 * right > maxLen) maxLen = 2 * right;
            }
            else if (left > right) {
                left = right = 0;
            }
        }
        return maxLen;
    }
};

int main() {

    string s = ")()())";

    Solution sol;

    int ret = sol.longestValidParentheses(s);
    cout << ret << endl;

    return 0;
}