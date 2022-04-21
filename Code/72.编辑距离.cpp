#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        if (m * n == 0) return m + n;

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 0; i < m + 1; ++i) {
            dp[i][0] = i;
        }

        for (int j = 0; j < n + 1; ++j) {
            dp[0][j] = j;
        }

        for (int i = 1; i < m + 1; ++i) {
            for (int j = 1; j < n + 1; ++j) {
                int left = dp[i - 1][j] + 1;
                int down = dp[i][j - 1] + 1;
                int left_down = dp[i - 1][j - 1];
                if (word1[i - 1] != word2[j - 1]) {
                    left_down += 1;
                }
                dp[i][j] = min(left, min(down, left_down));
            }
        }
        return dp[m][n];
    }
};

// LeetCode 101解法：时间 8 ms 88.94%，空间 8.7 MB 67.81%
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        if (m * n == 0) return m + n;

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 0; i < m + 1; ++i) {
            dp[i][0] = i;
        }

        for (int j = 0; j < n + 1; ++j) {
            dp[0][j] = j;
        }

        for (int i = 1; i < m + 1; ++i) {
            for (int j = 1; j < n + 1; ++j) {
                int left = dp[i - 1][j] + 1;
                int down = dp[i][j - 1] + 1;
                int left_down = dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1);
                dp[i][j] = min(left, min(down, left_down));
            }
        }
        return dp[m][n];
    }
};