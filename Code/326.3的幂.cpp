#include<iostream>
#include<cmath>

using std::fmod;
using std::log10;

//  我的解法：时间O(log_3 n) 20 ms 34.95%，空间 5.9 MB 33.51%
class Solution {
public:
	bool isPowerOfThree(int n) {
		while (n >= 3) {
			if (n % 3 != 0) break;
			n /= 3;
		}
		return n == 1;
	}
};

// LeetCode 101解法一：利用对数，时间 8 ms 91.91%，空间 6 MB 7.24%
// 设log_3^n = m，若n是3的整数次方，那么m一定是整数。
class Solution {
public:
	bool isPowerOfThree(int n) {
		return fmod(log10(n) / log10(3), 1) == 0;
	}
};

// LeetCode 101解法二：取模，时间 12 ms 76.27%，空间 5.8 MB 63.43%
// int范围内3的最大次方是3^19=1162261467，如果n是3的整数次方，1162261467 % n 一定为零。
class Solution {
public:
	bool isPowerOfThree(int n) {
		return n > 0 && 1162261467 % n == 0;
	}
};