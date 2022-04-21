#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// LeetCode 101解法：时间 52 ms 96.99%，空间 26.8 MB 90.63%
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.empty()) return {};
        int height = mat.size(), width = mat[0].size();
        vector<vector<int>> dp(height, vector<int>(width, 1e5));
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (mat[i][j] == 0) {
                    dp[i][j] = 0;
                }
                else {
                    if (i > 0) {
                        dp[i][j] = dp[i - 1][j] + 1;
                    }
                    if (j > 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                    }
                }
            }
        }
        for (int i = height - 1; i >= 0; --i) {
            for (int j = width - 1; j >= 0; --j) {
                if (mat[i][j] == 1) {
                    if (i < height - 1) {
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                    }
                    if (j < width - 1) {
                        dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                    }
                }
            }
        }
        return dp;
    }
};