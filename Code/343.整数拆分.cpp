#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 官方题解一：动态规划，时间O(n^2) 0 ms 100%，空间O(n) 6.2 MB 15.55%
// 思路：dp[i]表示将正整数i拆分成至少两个正整数的和之后，这些正整数的最大乘积。
// 其中0不是正整数，1是最小正整数，0和1都不能拆分，因此dp[0]=dp[1]=0
// 当i>=2时，假设对正整数i拆分出的第一个正整数是j(1<=j<i)，有以下两种方案:
// 1.将i拆分成j和i-j的和，且i-j不再拆分成多个正整数，此时乘积是j×(i-j)
// 2.将i拆分出j和i-j的和，且i-j继续拆分，此时乘积是j×dp[i-j]
// 故有dp[i] = max(1<=j<i){max(j×(i-j),j×dp[i-j])}
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp.back();
    }
};

// 方法二：优化的动态规划，时间 O(n) 0 ms 100%，空间 O(n) 6.1 MB 52.80%
// 思路：由于dp[i]表示将正整数i拆分成至少两个正整数的和之后，这些正整数的最大乘积，故有dp[i]>=j*dp[i-j]
class Solution {
public:
    int integerBreak(int n) {
        if (n < 4) return n - 1;
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            dp[i] = max(max(2 * (i - 2), 2 * dp[i - 2]), max(3 * (i - 3), 3 * dp[i - 3]));
        }
        return dp[n];
    }
};