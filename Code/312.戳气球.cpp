#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 官方解法一：记忆化搜索，时间O(n^3) 888 ms，空间O(n^2) 10 MB
class Solution {
private:
	vector<vector<int>> rec;
	vector<int> val;

	// 在开区间(left, right)中寻找最大的i使得val[left]*val[i]*val[right]最大
	int solve(size_t left, size_t right) {
		if (left >= right - 1) return 0;
		if (rec[left][right] != -1) return rec[left][right];
		for (size_t i = left + 1; i < right; ++i) {
			int sum = val[left] * val[i] * val[right];
			sum += solve(left, i) + solve(i, right);
			rec[left][right] = max(rec[left][right], sum);
		}
		return rec[left][right];
	}
public:
	int maxCoins(vector<int>& nums) {
		size_t n = nums.size();
		val.resize(n + 2);
		val[0] = val[n + 1] = 1;
		for (size_t i = 1; i <= n; ++i) {
			val[i] = nums[i - 1];
		}
		rec.resize(n + 2, vector<int>(n + 2, -1));
		return solve(0, n + 1);
	}
};

// 官方解法二：动态规划，时间O(n^3) 728 ms，空间O(n^2）10.1 MB
class Solution {
public:
	int maxCoins(vector<int>& nums) {
		size_t n = nums.size();
		vector<vector<int>> rec(n + 2, vector<int>(n + 2));
		vector<int> val(n + 2);
		val[0] = val[n + 1] = 1;
		for (size_t i = 1; i <= n; ++i) {
			val[i] = nums[i - 1];
		}
		for (size_t i = n - 1; i != -1; --i) {
			for (size_t j = i + 2; j <= n + 1; ++j) {
				for (size_t k = i + 1; k < j; ++k) {
					int sum = val[i] * val[k] * val[j];
					sum += rec[i][k] + rec[k][j];
					rec[i][j] = max(rec[i][j], sum);
				}
			}
		}
		return rec[0][n + 1];
	}
};