#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>

using namespace std;

// 我的解法：动态规划，时间O(nk) 4 ms 94.53%，空间 O(k) 10.4 MB 90.80%
// 如果k大于总天数的一半，一旦发现可以赚钱就可以买卖，由于一次买卖需要两天所以是一半。
// 如果k小于总天数的一半，可以建立两个动态规划数组buy和sell，对于每天的股票价格，buy[i][j]表示在第i天进行第j次买入的最大收益，sell[j]表示在第i天进行第j次卖出时的最大收益，然后用滚动数组优化成buy[j]和sell[j]
class Solution {
private:
    int maxProfitKLargerHalf(const vector<int>& prices) {
        int maxProfit = 0;
        for (size_t i = 1; i < prices.size(); ++i) {
            int profit = prices[i] - prices[i - 1];
            maxProfit += profit > 0 ? profit : 0;
        }
        return maxProfit;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        size_t days = prices.size();
        if (days < 2) return 0;
        if (k * 2 >= days) {
            return maxProfitKLargerHalf(prices);
        }
        vector<int> buy(k + 1, INT_MIN), sell(k + 1, 0);
        for (int price : prices) {
            for (size_t j = 1; j <= k; ++j) {
                buy[j] = max(buy[j], sell[j - 1] - price);
                sell[j] = max(sell[j], buy[j] + price);
            }
        }
        return sell[k];
    }
};

// 动态规划非滚动数组版本：时间O(nk) 8 ms 65.56%，空间O(nk) 12.5 MB 22.01%
// i和j都从1计起
// 对于每天的股票价格，buy[i][j]表示在第i天进行第j次买入的最大收益，sell[j]表示在第i天进行第j次卖出时的最大收益
class Solution {
private:
    int maxProfitKLargerHalf(const vector<int>& prices) {
        int maxProfit = 0;
        for (size_t i = 1; i < prices.size(); ++i) {
            int profit = prices[i] - prices[i - 1];
            maxProfit += profit > 0 ? profit : 0;
        }
        return maxProfit;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        size_t days = prices.size();
        if (days < 2) return 0;
        if (k * 2 >= days) {
            return maxProfitKLargerHalf(prices);
        }
        vector<vector<int>> buy(days + 1, vector<int>(k + 1, INT_MIN)), sell(days + 1, vector<int>(k + 1, 0));
        for (size_t i = 1; i <= days; ++i) {
            for (size_t j = 1; j <= k; ++j) {
                // 第i天及之前的第j次买入最大收益有两种，一是在i-1天及之前进行第j次买入，二是在第i天买入了，i-1天进行了j-1次交易的收益减去在第i天(从1计起)的价格prices[i-1]，两者取最大
                buy[i][j] = max(buy[i - 1][j], sell[i - 1][j - 1] - prices[i - 1]);
                // 第i天及之前的第j次售出最大收益有两种，一是在i-1天及之前进行了第j次售出，二是第i天及之前进行第j次买入后的收益加上第i天的价格prices[i-1]，两者取最大
                sell[i][j] = max(sell[i - 1][j], buy[i][j] + prices[i - 1]);
            }
        }
        return sell[days][k];
    }
};