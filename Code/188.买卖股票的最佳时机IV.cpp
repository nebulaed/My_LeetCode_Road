#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;

// �ҵĽⷨ����̬�滮��ʱ��O(nk) 4 ms 94.53%���ռ� O(k) 10.4 MB 90.80%
// ���k������������һ�룬һ�����ֿ���׬Ǯ�Ϳ�������������һ��������Ҫ����������һ�롣
// ���kС����������һ�룬���Խ���������̬�滮����buy��sell������ÿ��Ĺ�Ʊ�۸�buy[i][j]��ʾ�ڵ�i����е�j�������������棬sell[j]��ʾ�ڵ�i����е�j������ʱ��������棬Ȼ���ù��������Ż���buy[j]��sell[j]
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

// ��̬�滮�ǹ�������汾��ʱ��O(nk) 8 ms 65.56%���ռ�O(nk) 12.5 MB 22.01%
// i��j����1����
// ����ÿ��Ĺ�Ʊ�۸�buy[i][j]��ʾ�ڵ�i����е�j�������������棬sell[j]��ʾ�ڵ�i����е�j������ʱ���������
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
				// ��i�켰֮ǰ�ĵ�j������������������֣�һ����i-1�켰֮ǰ���е�j�����룬�����ڵ�i�������ˣ�i-1�������j-1�ν��׵������ȥ�ڵ�i��(��1����)�ļ۸�prices[i-1]������ȡ���
				buy[i][j] = max(buy[i - 1][j], sell[i - 1][j - 1] - prices[i - 1]);
				// ��i�켰֮ǰ�ĵ�j���۳�������������֣�һ����i-1�켰֮ǰ�����˵�j���۳������ǵ�i�켰֮ǰ���е�j��������������ϵ�i��ļ۸�prices[i-1]������ȡ���
				sell[i][j] = max(sell[i - 1][j], buy[i][j] + prices[i - 1]);
			}
		}
		return sell[days][k];
	}
};