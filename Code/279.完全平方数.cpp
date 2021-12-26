#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：动态规划，时间O(n sqrt(n)) 176 ms，空间O(n) 9.3 MB
class Solution {
public:
	int numSquares(int n) {
		vector<int> nums;
		for (int i = 1; i * i <= n; ++i) {
			nums.emplace_back(i * i);
		}
		vector<int> f(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			int minStep = INT_MAX;
			for (int j = 0; j < nums.size(); ++j) {
				if (i - nums[j] >= 0) {
					minStep = min(minStep, f[i - nums[j]]);
				}
				else break;
			}
			f[i] = minStep + 1;
		}
		return f[n];
	}
};

// 官方解法一：动态规划，时间O(n sqrt(n)) 72 ms，空间O(n) 8.9 MB
class Solution {
public:
	int numSquares(int n) {
		vector<int> f(n + 1);
		for (int i = 1; i <= n; i++) {
			int minn = INT_MAX;
			for (int j = 1; j * j <= i; j++) {
				minn = min(minn, f[i - j * j]);
			}
			f[i] = minn + 1;
		}
		return f[n];
	}
};

// 官方解法二：四平方和定理，任意一个正整数可以表示为至多四个正整数的平方和
// 时间O(sqrt(n)) 4 ms，空间 O(1) 5.8 MB
// 当且仅当n≠4^k*(8m+7)时，n可以被表示为至多三个正整数的平方和。当n=4^k*(8m+7)时，n只能被表示为四个正整数的平方和，此时返回4
// 剩下3种情况：为1时，n为完全平方数
// 检查所有的n-a^2(1<=a<=sqrt(n))是否为完全平方数，是则为2，否则为3
class Solution {
private:
	// 判断是否为完全平方数
	bool isPerfectSquare(int x) {
		int y = sqrt(x);
		return y * y == x;
	}

	bool checkAnswer4(int x) {
		while (x % 4 == 0) {
			x /= 4;
		}
		return x % 8 == 7;
	}

public:
	int numSquares(int n) {
		if (isPerfectSquare(n)) {
			return 1;
		}
		if (checkAnswer4(n)) {
			return 4;
		}
		for (int i = 1; i * i <= n; ++i) {
			int j = n - i * i;
			if (isPerfectSquare(j)) {
				return 2;
			}
		}
		return 3;
	}
};