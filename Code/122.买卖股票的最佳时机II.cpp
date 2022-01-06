#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// �ҵĽⷨ��˫ָ��+̰���㷨��ʱ��O(n) 4 ms 90.29%���ռ�O(1) 12.5 MB 96.49%
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int maxBenefit = 0;
		size_t length = prices.size();
		size_t left = 0, right = 0;
		while (right < length) {
			// ��leftָ�����һ��Ԫ�ػ�����һ��Ԫ��С�ڵ��ڵ�ǰԪ�أ�left��right������
			if (left == length - 1 || prices[left] >= prices[left + 1]) {
				++left;
				++right;
			}
			// leftָ��ȷ�����������ƶ�right
			else {
				// ��rightָ���Ԫ�ز�����leftָ��Ԫ�أ�right������
				if (prices[right] <= prices[left]) {
					++right;
				}
				// ��right��ָ�����һ��Ԫ������һ��Ԫ�رȵ�ǰԪ�ش�right������
				else if (right < length - 1 && prices[right] < prices[right + 1]) {
					++right;
				}
				// ���϶������㣬˵��rightָ��ȷ�����������󣬲���left��right��ָ��right����һ��Ԫ��
				else {
					maxBenefit += prices[right] - prices[left];
					left = ++right;
				}
			}
		}
		return maxBenefit;
	}
};

// �ҵĽⷨ����̬�滮��ʱ��O(n) 4 ms 90.29%���ռ�O(n) 13 MB 15.92%
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

// �ҵĽⷨ����̬�滮+�������飬ʱ��O(n) 4 ms 90.29%���ռ�O(1) 12.7 MB 72.06%
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		size_t n = prices.size();
		// ע�⣺�����ʼ��������ʾ��int����ĵ�һλ��ʼ��Ϊ-prices[0]�������ʼ��Ϊ0
		// C++11���³�ʼ��������int array[2]{};�൱��int array[2] = {0};��ʾ�����ڶ���ʼ��Ϊ0
		int dp[2] = { -prices[0] };
		for (size_t i = 1; i < n; ++i) {
			dp[0] = max(dp[0], dp[1] - prices[i]);
			dp[1] = max(dp[0] + prices[i], dp[1]);
		}
		return dp[1];
	}
};