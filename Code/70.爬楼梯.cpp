#include<iostream>
using namespace std;

// 我的解法一：动态规划 时间 O(n) 0 ms，空间O(n) 6.1 MB
class Solution {
public:
	int climbStairs(int n) {
		if (n == 1) return 1;
		int* dp = new int[n];
		dp[0] = 1, dp[1] = 2;
		for (int i = 2; i < n; ++i) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n - 1];
	}
};

// 官方解法一：动态规划+滚动数组 时间 O(n) 0 ms，空间O(1) 5.8 MB
class Solution {
public:
	int climbStairs(int n) {
		if (n == 1) return 1;
		int a = 1, b = 1, c = 2;
		for (int i = 3; i <= n; ++i) {
			a = b;
			b = c;
			c = a + b;
		}
		return c;
	}
};

class Solution {
public:
	int climbStairs(int n) {
		int p = 0, q = 0, r = 1;
		for (int i = 1; i <= n; ++i) {
			p = q;
			q = r;
			r = p + q;
		}
		return r;
	}
};



int main() {
	int n = 3;

	Solution s;
	int ret = s.climbStairs(n);

	cout << ret << endl;

	system("pause");
	return 0;
}