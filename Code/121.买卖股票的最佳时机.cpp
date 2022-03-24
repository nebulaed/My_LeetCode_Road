#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ��vector+��̬�滮��ʱ��O(n) 108 ms���ռ�O(n) 94.9 MB
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

// �ҵĽⷨ������̬����+��̬�滮��ʱ��O(n) 92 ms���ռ�O(n) 94.9 MB
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

// �ٷ��ⷨһ��һ�α���(�ҸĶ���İ汾)��ʱ��O(n) 96 ms,�ռ�O(1) 91.1 MB
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

// �ٷ��ⷨһ��һ�α���(ԭ��)��ʱ��O(n) 116 ms,�ռ�O(1) 91 MB
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

// �ҵĵڶ��νⷨ��һ�α�����ʱ�� 76 ms 99.62%���ռ� 91.1 MB 79.46%
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