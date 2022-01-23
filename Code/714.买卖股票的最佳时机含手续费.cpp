#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;


// �ҵĽⷨ��״̬��+��̬�滮��ʱ��O(n) 84 ms 68.79%���ռ� O(n) 62.8 MB 38.13%
class Solution {
public:
	int maxProfit(vector<int>& prices, int fee) {
		int n = prices.size();
		vector<int> buy(n), sell(n), s1(n), s2(n);
		s1[0] = buy[0] = -prices[0] - fee;
		sell[0] = s2[0] = 0;
		for (int i = 1; i < n; ++i) {
			int price = prices[i];
			buy[i] = max(sell[i - 1], s2[i - 1]) - price - fee;
			s1[i] = max(buy[i - 1], s1[i - 1]);
			sell[i] = max(buy[i - 1], s1[i - 1]) + price;
			s2[i] = max(sell[i - 1], s2[i - 1]);
		}
		return max(sell[n - 1], s2[n - 1]);
	}
};

// �ҵĽⷨ��״̬��+��̬�滮+�������飬ʱ��O(n) 72 ms 94.30%���ռ�O(1) 53.7 MB 84.99%
class Solution {
public:
	int maxProfit(vector<int>& prices, int fee) {
		int n = prices.size();
		int buy = 0, sell = 0, s1 = 0, s2 = 0;
		s1 = buy = -prices[0] - fee;
		for (int i = 1; i < n; ++i) {
			int price = prices[i], tempBuy = buy, tempSell = sell;
			buy = max(sell, s2) - price - fee;
			sell = max(tempBuy, s1) + price;
			s1 = max(tempBuy, s1);
			s2 = max(tempSell, s2);
		}
		return max(sell, s2);
	}
};
