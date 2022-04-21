#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j) {
            if (i == 0) {
                return false;
            }
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else {
                    if (matches(i, j)) {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};

class Solution {
public:
    bool isMatch(string s, string p) {
        if (s == p) return true;
        int i = 0, j = 0;
        while (i < s.size() && j < s.size()) {
            if (p[j] >= 'a' && p[j] <= 'z') {
                if (s[i] != p[j]) {
                    break;
                }
                ++i;
                ++j;
            }
            else if (p[j] == '.') {
                ++i;
                ++j;
            }
            else (p[j] == '*') {
                if (p[j - 1] == '.') {
                    if (j == p.size()) {
                        i = s.size()
                    }
                    ++j;
                }
            }
        }
    }
};

// LeetCode 101解法：动态规划，时间 4 ms 87.12%，空间 6.6 MB 76.37%
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        // dp[i][j]表示以i截止的字符串是否可以被以j截止的正则表达式匹配
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            // 若p的第i个字符为*，只要以0截止的字符串s能被以i-2截止的正则表达式p匹配，那么s也能被以i截止的p匹配
            if (p[i - 1] == '*') {
                dp[0][i] = dp[0][i - 2];
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // 若p的第j个字符为.，只要以i-1截止的字符串s能被以j-1截止的正则表达式p匹配，那么s也能被以i截止的p匹配
                if (p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                    // 若p的第j个字符不为*也不为.，那么只有当以i-1截止的字符串s能被以j-1截止的正则表达式p匹配，且s的第i个字符和p的第j个字符一致，才能匹配
                else if (p[j - 1] != '*') {
                    dp[i][j] = dp[i - 1][j - 1] & (p[j - 1] == s[i - 1]);
                }
                    // 若p的第j个字符为*，且p的第j-1个字符与s的第i个字符不一致，且p的第j-1个字符不是.，那么s与p是否匹配取决于以i截止的s与以j-2截止的p是否匹配，也就是p的第j-1和j字符：?*匹配了零个元素
                else if ((p[j - 2] != s[i - 1]) & (p[j - 2] != '.')) {
                    dp[i][j] = dp[i][j - 2];
                }
                    // 若p的第j个字符为*，且p的第j-1个字符与s的第i个字符匹配(包括正常匹配或用.匹配)，那么只要以i结尾的s与以j-1结尾的p匹配或以i-1结尾的s能与以j结尾的p匹配或以i结尾的s能与以j-2结尾的p匹配，那么s和p匹配。
                    // 第一种好理解，就是如果ba和ba*比较，如果s[i]=ba和p[j-1]=ba能匹配上，那么s和p能匹配上
                    // 第二种表示，如果aab和c*a*b*比较，s[i]=aa和p[j-1]=c*a匹配不了，如果s[i-1]=a和p[j]=c*a*匹配，那么s=aa和p=c*a*能匹配
                    // 第三种表示，如果ab和abd*比较，s[i]=ab和p[j-2]=ab能匹配，那s=ab和p=abd*也能匹配
                else {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j] | dp[i][j - 2];
                }
            }
        }
        return dp[m][n];
    }
};

int main() {

    string s = "mississippi";
    string p = "mis*is*p*.";

    Solution sol;
    bool ret = sol.isMatch(s, p);
    if (ret) cout << "true" << endl;
    else cout << "false" << endl;

    return 0;
}