#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

// 我的解法：动态规划，时间O(lmn) 352 ms 21.27%，空间O(lmn) 100.3 MB 13.78%
class Solution {
private:
    pair<int, int> count(const string& str) {
        int count0 = str.size(), count1 = 0;
        for (char ch : str) {
            if (ch == '1') {
                ++count1;
                --count0;
            }
        }
        return make_pair(count0, count1);
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int l = strs.size();
        vector<vector<vector<int>>> dp(l + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        for (int i = 1; i <= l; ++i) {
            // 利用C++17的结构化绑定
            auto [count0, count1] = count(strs[i - 1]);
            for (int j = 0; j <= m; ++j) {
                for (int k = 0; k <= n; ++k) {
                    if (j - count0 >= 0 && k - count1 >= 0) {
                        dp[i][j][k] = max(dp[i - 1][j][k], 1 + dp[i - 1][j - count0][k - count1]);
                    }
                    else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }
        return dp[l][m][n];
    }
};

// 我的解法：动态规划+滚动数组+vector，时间O(lmn) 200 ms 53%，空间 O(mn) 9.6 MB 47%
class Solution {
private:
    pair<int, int> count(const string& str) {
        int count0 = str.size(), count1 = 0;
        for (char ch : str) {
            if (ch == '1') {
                ++count1;
                --count0;
            }
        }
        return make_pair(count0, count1);
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (const string& str : strs) {
            auto [count0, count1] = count(str);
            for (int i = m; i >= count0; --i) {
                for (int j = n; j >= count1; --j) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - count0][j - count1]);
                }
            }
        }
        return dp[m][n];
    }
};

// 我的解法：动态规划+滚动数组+new，时间O(lmn) 92 ms 94.73%，空间 O(mn) 9.3 MB 94.76%
class Solution {
private:
    pair<int, int> count(const string& str) {
        int count0 = str.size(), count1 = 0;
        for (char ch : str) {
            if (ch == '1') {
                ++count1;
                --count0;
            }
        }
        return make_pair(count0, count1);
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int** dp = new int* [m + 1];
        for (int i = 0; i <= m; ++i) {
            dp[i] = new int[n + 1]{};
        }
        for (const string& str : strs) {
            auto [count0, count1] = count(str);
            for (int i = m; i >= count0; --i) {
                for (int j = n; j >= count1; --j) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - count0][j - count1]);
                }
            }
        }
        int ret = dp[m][n];
        for (int i = 0; i <= m; ++i) {
            delete[] dp[i];
        }
        delete[] dp;
        return ret;
    }
};

int main() {

    vector<string> strs = { "10","0001","111001","1","0" };
    int m = 5, n = 3;
    Solution s;
    int ret = s.findMaxForm(strs, m, n);

    cout << ret << endl;

    return 0;
}