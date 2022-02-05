#include<iostream>
#include<cmath>

using std::log2;

// 我的解法一：位运算，时间 0 ms 100%，空间 5.9 MB 12.67%
// 交替位二进制数如101，右移后为010，两个数异或后为111，若与2^(log2(101)+1) - 1即1000 - 1 = 111相等，说明当前数为交替位二进制数
// 若当前数不是交替位二进制数如100，右移后为010，两个数异或后为110，与2^(log2(100)+1) - 1即 111 不相等
class Solution {
public:
	bool hasAlternatingBits(int n) {
		int ret = n ^ (n >> 1);
		int digit = static_cast<int>(log2(n)) + 1;
		int j = digit >= 31 ? INT_MAX : (1 << digit) - 1;
		return ret == j;
	}
};

// 我的解法二：位运算，时间 0 ms 100%，空间 5.8 MB 39.41%
// 101与010的异或为111，111 + 1后为1000，1000 & (1000 - 1) = (111 + 1) & 111就是将1000最后一位1置为零，结果为0
// 这说明当(n ^ (n >> 1) + 1) & (n ^ (n >> 1))为0，则n为交替位二进制数
// 注意避免n ^ (n >> 1) == INT_MAX的边界情况
class Solution {
public:
	bool hasAlternatingBits(int n) {
		int ret = n ^ (n >> 1);
		return ret == INT_MAX || !((ret + 1) & ret);
	}
};