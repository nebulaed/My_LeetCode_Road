#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

// LeetCode 101解法：时间 0 ms 100%，空间 6.3 MB 70.63%
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1);
        iota(dp.begin(), dp.end(), 0);
        dp[1] = 0;
        for (int i = 2; i <= n; ++i) {
            // 由于对j > sqrt(i)的情况，i分解质因数后得到的两个乘数j和i/j会和之前的i/j和j重复，因此j列举到sqrt(i)即可
            // 如12 = 2 * 6：j = 2，i/j = 6与12 = 6 * 2: j = 6, i/j = 2的结果都是dp[12] = dp[2] + dp[6]
            for (int j = 2; j * j <= i; ++j) {
                // 若i能被j整除，那么长度i可由长度j操作得到，操作次数等价于把长度为1的A延展到长度为i/j
                // 例如，AAAA到AAAA AAAA AAAA的操作数和A到AAA的操作数一致
                if (i % j == 0) {
                    dp[i] = dp[j] + dp[i / j];
                    break;
                }
            }
        }
        return dp[n];
    }
};