#include<iostream>

// 我的解法：时间 0 ms 100%，空间 5.9 MB 40.07%
class Solution {
public:
	bool isPowerOfFour(int n) {
		// 若n小于等于0，必不是4的幂
		if (n <= 0) return false;
		// 若n的二进制不只有一个1，必不是4的幂
		if (n & (n - 1)) return false;
		// 符号位(1),10101010 10101010 10101010 1010101
		const int M4 = 1431655765;
		// 在n的二进制只有一个1的前提下，只要这个1在M4中的1的位置，就是4的幂
		if (n & M4) return true;
		else return false;
	}
};

// LeetCode 101解法：思路同上，更简洁，时间 4 ms 38.04%，空间 5.9 MB 42.55%
class Solution {
public:
	bool isPowerOfFour(int n) {
		return n > 0 && !(n & (n - 1)) && (n & 1431655765);
	}
};