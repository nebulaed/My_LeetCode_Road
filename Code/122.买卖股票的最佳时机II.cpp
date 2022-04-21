#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// 我的解法：双指针+贪心算法，时间O(n) 4 ms 90.29%，空间O(1) 12.5 MB 96.49%
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxBenefit = 0;
        size_t length = prices.size();
        size_t left = 0, right = 0;
        while (right < length) {
            // 若left指向最后一个元素或者下一个元素小于等于当前元素，left、right向右移
            if (left == length - 1 || prices[left] >= prices[left + 1]) {
                ++left;
                ++right;
            }
                // left指向确定，接下来移动right
            else {
                // 若right指向的元素不大于left指向元素，right向右移
                if (prices[right] <= prices[left]) {
                    ++right;
                }
                    // 若right不指向最后一个元素且下一个元素比当前元素大，right向右移
                else if (right < length - 1 && prices[right] < prices[right + 1]) {
                    ++right;
                }
                    // 以上都不满足，说明right指向确定，计算利润，并将left和right都指向right的下一个元素
                else {
                    maxBenefit += prices[right] - prices[left];
                    left = ++right;
                }
            }
        }
        return maxBenefit;
    }
};

// 我的解法：动态规划，时间O(n) 4 ms 90.29%，空间O(n) 13 MB 15.92%
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t n = prices.size();
        vector<array<int, 2>> dp(n, array<int, 2>());
        dp[0][0] = -prices[0];
        for (size_t i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][0] + prices[i], dp[i - 1][1]);
        }
        return dp[n - 1][1];
    }
};

// 我的解法：动态规划+滚动数组，时间O(n) 4 ms 90.29%，空间O(1) 12.7 MB 72.06%
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        size_t n = prices.size();
        // 注意：这个初始化方法表示将int数组的第一位初始化为-prices[0]，其余初始化为0
        // C++11的新初始化方法：int array[2]{};相当于int array[2] = {0};表示数组内都初始化为0
        int dp[2] = { -prices[0] };
        for (size_t i = 1; i < n; ++i) {
            dp[0] = max(dp[0], dp[1] - prices[i]);
            dp[1] = max(dp[0] + prices[i], dp[1]);
        }
        return dp[1];
    }
};