#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 自己解法： 64 ms，27.3 MB
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j) {
            if (i == 0) {
                return false;
            }
            if (p[j - 1] == '?') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        // 参考答案指点部分
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*') {
                f[0][i] = true;
            }
            else {
                break;
            }
        }
        //
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    if (i > 0) {
                        f[i][j] |= f[i - 1][j];
                        if (j > 1) {
                            // 参考答案指点部分
                            // if(matches(i, j-1)){
                            f[i][j] |= f[i][j - 1];
                            // }
                        }
                        else f[i][j] = true;
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

// 官方解法1：动态规划 O(mn) 64 ms，O(mn) 27.1 MB
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*') {
                dp[0][i] = true;
            }
            else {
                break;
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

// 官方解法2：贪心算法 渐进时间复杂度O(mn)，平均时间复杂度O(mlog n) 8 ms，6.4 MB
class Solution {
public:
    bool isMatch(string s, string p) {
        // 检查str在[left,right)内是否都为*
        auto allStars = [](const string& str, int left, int right) {
            for (int i = left; i < right; ++i) {
                if (str[i] != '*') {
                    return false;
                }
            }
            return true;
        };
        // 检查u和v是否匹配
        auto charMatch = [](char u, char v) {
            return u == v || v == '?';
        };

        // 若s、p的长度不为0，且p的最后一个字符不为*，判断s和p的结尾字符是否匹配，是则将s和p的结尾一同逐字符删去，否则匹配失败
        while (s.size() && p.size() && p.back() != '*') {
            if (charMatch(s.back(), p.back())) {
                s.pop_back();
                p.pop_back();
            }
            else {
                return false;
            }
        }
        // 若p为空，则s为空时匹配成功，否则匹配失败
        if (p.empty()) {
            return s.empty();
        }

        // index从0开始，sRecord从-1开始，若p第一个字符是*，sRecord和pRecord才从pIndex开始，否则要逐一匹配字符直到p的第一个*
        int sIndex = 0, pIndex = 0;
        int sRecord = -1, pRecord = -1;
        while (sIndex < s.size() && pIndex < p.size()) {
            if (p[pIndex] == '*') {
                ++pIndex;
                sRecord = sIndex;
                pRecord = pIndex;
            }
            else if (charMatch(s[sIndex], p[pIndex])) {
                ++sIndex;
                ++pIndex;
            }
            else if (sRecord != -1 && sRecord + 1 < s.size()) {
                ++sRecord;
                sIndex = sRecord;
                pIndex = pRecord;
            }
            else {
                return false;
            }
        }
        return allStars(p, pIndex, p.size());
    }
};

int main() {
    string s = "aa";
    string p = "*";

    Solution sol;
    bool ret = sol.isMatch(s, p);

    cout << ret << endl;

    return 0;
}