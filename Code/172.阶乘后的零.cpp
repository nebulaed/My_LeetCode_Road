#include<iostream>

// 我的解法：计算阶乘中五的个数，时间 0 ms 100%，空间 5.8 MB 66.10%
// 思路：五的个数会带来零的个数
class Solution {
public:
	int trailingZeroes(int n) {
		int ret = 0;
		for (int factor = 5; factor <= n; factor *= 5) {
			ret += n / factor;
		}
		return ret;
	}
};

// LeetCode 101解法：统计阶乘结果中质因子5的个数，时间 0 ms 100%，空间 5.8 MB 64.23%
class Solution {
public:
	int trailingZeroes(int n) {
		return n == 0 ? 0 : (n / 5 + trailingZeroes(n / 5));
	}
};
