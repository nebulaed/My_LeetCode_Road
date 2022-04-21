#include<vector>
#include<string>

using namespace std;

// 我的解法参考LeetCode 101：动态规划，时间 0 ms 100%，空间 6 MB 64.26%
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        char prev = s[0];
        if (prev == '0') return 0;
        if (n == 1) return 1;
        vector<int> dp(n + 1, 1);
        for (int i = 2; i <= n; ++i) {
            char ch = s[i - 1];
            if (ch == '0' && (prev == '0' || prev > '2')) return 0;
            if ((prev > '0' && prev < '2') || (prev == '2' && ch < '7')) {
                dp[i] = dp[i - 2] + (ch == '0' ? 0 : dp[i - 1]);
            }
            else {
                dp[i] = dp[i - 1];
            }
            prev = ch;
        }
        return dp[n];
    }
};