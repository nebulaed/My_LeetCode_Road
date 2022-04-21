#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// 官方解法一：动态规划，时间O(n) 4 ms，空间O(n) 11.3 MB
// 思路：用f[i]表示第i天结束后的累计最大收益。根据题意，我们会有三种不同状态：
// 1.我们目前持有一支股票，对应的累计最大收益记为f[i][0];
// 2.我们目前不持有任何股票且处于冷冻期，对应的累计最大收益记为f[i][1];
// 3.我们目前不持有任何股票，且不处于冷冻期，对应的累计最大收益记为f[i][2]。
// A. 对于f[i][0]，目前我们持有的这支股票是在第i-1天就已经持有的，对应的状态为f[i-1][0]；或者是第i天买入的，那么第i-1天不能持有股票或卖出股票，对应的状态为f[i-1][2]加上买入股票的负收益prices[i]。因此状态转移方程为：
// f[i][0] = max(f[i-1][0], f[i-1][2]-prices[i])
// B. 对于f[i][1]，在第i天结束后处于冷冻期说明当天卖出了股票，那么i-1天必持有股票，当前状态为f[i-1][0]加上卖出股票的正收益prices[i]。状态转移方程为：
// f[i][1] = f[i-1][0] + prices[i]
// 对于f[i][2]，在第i天结束之后不持有任何股票并且不处于冷冻期，说明当天没有进行任何操作，即第i-1天时不持有任何股票；若i-1天为冷冻期，则状态为f[i-1][1]，不处于冷冻期，则对应状态为f[i-1][2]。因此状态转移方程为：
// f[i][2] = max(f[i-1][1], f[i-1][2])
// 有了所有的状态转移方程，那么一共有n天，最终答案为
// max(f[n-1][0],f[n-1][1],f[n-1][2])
// 由于最后一天结束后仍持有股票无法卖出，故结果为max(f[n-1][1],f[n-1][2])
// 边界条件为f[0][0]=-prices[0]，f[0][1] = 0, f[0][2] = 0
//
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        size_t n = prices.size();
        vector<array<int, 3>> f(n, array<int, 3>());
        f[0][0] = -prices[0];
        for (size_t i = 1; i < n; ++i) {
            f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i]);
            f[i][1] = f[i - 1][0] + prices[i];
            f[i][2] = max(f[i - 1][1], f[i - 1][2]);
        }
        return max(f[n - 1][1], f[n - 1][2]);
    }
};

// 滚动数组，时间O(n) 0 ms，空间O(1) 10.9 MB
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        array<int, 3> f = { 0 };
        f[0] = -prices[0];
        for (int price : prices) {
            int newf2 = max(f[1], f[2]);
            f[1] = f[0] + price;
            f[0] = max(f[0], f[2] - price);
            f[2] = newf2;
        }
        return max(f[1], f[2]);
    }
};

// LeetCode 101：带状态机的动态规划，时间 4 ms，空间 11.1 MB
// 思路：用状态机来解决这类复杂的状态转移问题，通过建立多个状态以及它们的转移方式，可以很容易地推导出各个状态的转移方程。
// 图见LeetCode101：S1代表买入后等待卖出，S2代表卖出后冻结期+可能的等待期，buy和sell分别代表买入卖出
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        vector<int> buy(n), sell(n), s1(n), s2(n);
        s1[0] = buy[0] = -prices[0];
        sell[0] = s2[0] = 0;
        for (int i = 1; i < n; ++i) {
            buy[i] = s2[i - 1] - prices[i];
            s1[i] = max(buy[i - 1], s1[i - 1]);
            sell[i] = max(buy[i - 1], s1[i - 1]) + prices[i];
            s2[i] = max(s2[i - 1], sell[i - 1]);
        }
        return max(sell[n - 1], s2[n - 1]);
    }
};
// 稍加优化，时间 0 ms 100%，空间 11 MB 61.7%
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        vector<int> buy(n), sell(n), s1(n), s2(n);
        s1[0] = buy[0] = -prices[0];
        sell[0] = s2[0] = 0;
        for (int i = 1; i < n; ++i) {
            int price = prices[i], prevS2 = s2[i - 1];
            buy[i] = prevS2 - price;
            s1[i] = max(buy[i - 1], s1[i - 1]);
            sell[i] = s1[i] + price;
            s2[i] = max(prevS2, sell[i - 1]);
        }
        return max(sell[n - 1], s2[n - 1]);
    }
};