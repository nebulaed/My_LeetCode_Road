#include<iostream>
#include<numeric>
#include<vector>
using namespace std;

// 官方解法一：动态规划，时间 8 ms 23%，空间 8.1 MB 82%
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size(), m = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (j < stones[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - stones[i - 1]];
                }
            }
        }
        const auto& neg = dp[n];
        for (int j = m;; --j) {
            if (neg[j]) {
                return sum - 2 * j;
            }
        }
        return 0;
    }
};

// 我的解法：动态规划+滚动数组，时间 0 ms 100%，空间 7.8 MB 96.25%
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int n = stones.size(), m = sum / 2;
        vector<bool> dp(m + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= 0; --j) {
                if (j >= stones[i - 1]) {
                    dp[j] = dp[j] | dp[j - stones[i - 1]];
                }
            }
        }
        for (int j = m;; --j) {
            if (dp[j]) {
                return sum - 2 * j;
            }
        }
        return sum;
    }
};