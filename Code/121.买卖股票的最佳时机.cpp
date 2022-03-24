#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一：vector+动态规划，时间O(n) 108 ms，空间O(n) 94.9 MB
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		vector<int> benefit(n);
		benefit[n - 1] = 0;
		for (int i = n - 2; i >= 0; --i) {
			benefit[i] = max(benefit[i + 1] + prices[i + 1] - prices[i], 0);
		}
		return *max_element(benefit.begin(), benefit.end());
	}
};

// 我的解法二：动态数组+动态规划，时间O(n) 92 ms，空间O(n) 94.9 MB
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		int* benefit = new int[n]();
		for (int i = n - 2; i >= 0; --i) {
			benefit[i] = max(benefit[i + 1] + prices[i + 1] - prices[i], 0);
		}
		int maxBenefit = 0;
		for (int i = 0; i < n; ++i) {
			int cur = benefit[i];
			maxBenefit = cur > maxBenefit ? cur : maxBenefit;
		}
		return maxBenefit;
	}
};

// 官方解法一：一次遍历(我改动后的版本)，时间O(n) 96 ms,空间O(1) 91.1 MB
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int minPrice = INT_MAX;
		int maxProfit = 0;
		for (const auto& price : prices) {
			if (price < minPrice) {
				minPrice = price;
			}
			else if (price - minPrice > maxProfit) {
				maxProfit = price - minPrice;
			}
		}
		return maxProfit;
	}
};

// 官方解法一：一次遍历(原版)，时间O(n) 116 ms,空间O(1) 91 MB
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int minprice = INT_MAX, maxprofit = 0;
		for (int price : prices) {
			maxprofit = max(maxprofit, price - minprice);
			minprice = min(price, minprice);
		}
		return maxprofit;
	}
};

// 我的第二次解法：一次遍历，时间 76 ms 99.62%，空间 91.1 MB 79.46%
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int minPrice = 1e5, profit = 0;
		for (int price : prices) {
			if (price < minPrice) {
				minPrice = price;
			}
			else if (price - minPrice > profit) {
				profit = price - minPrice;
			}
		}
		return profit;
	}
};