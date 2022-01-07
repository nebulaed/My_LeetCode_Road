#include<iostream>
using namespace std;

// 我的解法：双指针，时间 O(sqrt(c)) 0 ms，空间 O(1) 5.7 MB 
class Solution {
public:
	bool judgeSquareSum(int c) {
		int left = 0, right = sqrt(c);
		while (left <= right) {
			int aSquare = left * left;
			int bSquare = right * right;
			// 注意：这里要小心aSquare + bSquare > INT_MAX，所以要把bSquare移项到右边
			if (aSquare > c - bSquare) {
				--right;
			}
			else if (aSquare < c - bSquare) {
				++left;
			}
			else return true;
		}
		return false;
	}
};

// 官方解法1：直接利用sqrt函数，时间 O(sqrt(c)) 4 ms，空间 O(1) 5.8 MB
class Solution {
public:
	bool judgeSquareSum(int c) {
		for (long a = 0; a * a <= c; ++a) {
			double b = sqrt(c - a * a);
			if (b == static_cast<int>(b)) {
				return true;
			}
		}
		return false;
	}
};

// 官方解法2：数学，时间 O(sqrt(c)) 0 ms，空间 O(1) 5.8 MB
// 费马定理告诉我们：一个非负整数c如果能够表示为两个整数的平方和，当且仅当c的所有形如4k+3的质因子的幂均为偶数。
class Solution {
public:
	bool judgeSquareSum(int c) {
		for (int base = 2; base * base <= c; base++) {
			// 如果不是因子，枚举下一个
			if (c % base != 0) {
				continue;
			}

			// 计算 base 的幂
			int exp = 0;
			while (c % base == 0) {
				c /= base;
				exp++;
			}

			// 根据 Sum of two squares theorem 验证
			if (base % 4 == 3 && exp % 2 != 0) {
				return false;
			}
		}

		// 例如 11 这样的用例，由于上面的 for 循环里 base * base <= c ，base == 11 的时候不会进入循环体
		// 因此在退出循环以后需要再做一次判断
		return c % 4 != 3;
	}
};