#include<iostream>
using namespace std;

// 我的解法：时间O(log C)，C最大为31，因为int最大为2^31，空间O(1)
class Solution {
public:
	int hammingDistance(int x, int y) {
		int ret = 0;
		while (x != 0 || y != 0) {
			if ((x & 1) != (y & 1)) {
				++ret;
			}
			x >>= 1;
			y >>= 1;
		}
		return ret;
	}
};

// 共同思路：两个整数之间的汉明距离是对应位置上数字不同的位数。根据定义，应使用异或运算，当且仅当输入位不同时输出为1

// 官方解法一：内置位计数功能，时间O(1) 0 ms，空间O(1) 5.9 MB
// 工程上应该直接使用内置函数
class Solution {
public:
	int hammingDistance(int x, int y) {
		return __builtin_popcount(x ^ y);
	}
};

// 官方解法二：移位实现位计数，时间O(log C) 0 ms，空间O(1) 5.9 MB
class Solution {
public:
	int hammingDistance(int x, int y) {
		int s = x ^ y, ret = 0;
		while (s) {
			ret += s & 1;
			s >>= 1;
		}
		return ret;
	}
};

// 官方解法三：Brian Kernighan算法，时间O(log C) 0 ms，空间O(1) 5.9 MB
// 在方法二中，对于s=(10001100)_2的情况，需要循环右移8次才能得到答案，实际上可以跳过两个1之间的0，直接对1进行计数
// 利用x & (x-1)删去最右边的1，知道x == 0为止，就可以计算出异或值的二进制表示中的1数量
// 效率比解法二高
class Solution {
public:
	int hammingDistance(int x, int y) {
		int s = x ^ y, ret = 0;
		while (s) {
			s &= s - 1;
			++ret;
		}
		return ret;
	}
};

// LeetCode 101解法，时间 0 ms 100%，空间 5.8 MB 84.22%
class Solution {
public:
	int hammingDistance(int x, int y) {
		int num = x ^ y, count = 0;
		while (num) {
			++count;
			num &= num - 1;
		}
		return count;
	}
};