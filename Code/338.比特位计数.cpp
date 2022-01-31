#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一：动态规划，时间 4 ms，空间 7.6 MB
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			int minOne = INT_MAX;
			for (int j = 1; j <= i; j *= 2) {
				minOne = min(minOne, dp[i - j]);
			}
			dp[i] = minOne + 1;
		}
		return dp;
	}
};

// 我的解法二：动态规划+数学，时间 8 ms，空间 7.7 MB
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i - pow(2, static_cast<int>(log2(i)))] + 1;
		}
		return dp;
	}
};

// 官方解法一：Brian Kernighan算法，时间O(n log n) 4 ms，空间O(1) 7.8 MB
// 对于任意整数x，令x = x & (x - 1)，该算法将x的二进制表示的最后一个1变成0。对x重复该操作，直到x变成0，操作次数即为x的一比特数。
class Solution {
private:
	int countOnes(int x) {
		int ones = 0;
		while (x > 0) {
			x &= (x - 1);
			++ones;
		}
		return ones;
	}
public:
	vector<int> countBits(int n) {
		vector<int> bits(n + 1, 0);
		for (int i = 0; i <= n; ++i) {
			bits[i] = countOnes(i);
		}
		return bits;
	}
};

// 官方解法二：动态规划——最高有效位，时间O(n) 4 ms，空间O(1) 7.7 MB
// 思路：当计算i的一比特数时，若存在0<=j<i，j的一比特数已知，且i和j相比，i的二进制表示只多了一个1，则可快速得到i的一比特数
// 令bits[i]表示i的一比特数，有bits[i] = bits[j] + 1
// 对正整数x，若知道最大的正整数y，使得y<=x且y是2的整数次幂，则y的二进制表示中只有最高位是1，其余都为0，y称为x的最高有效位。
// 令z = x - y，显然0<=z<x，则bits[x] = bits[z] + 1
// 一个正整数是不是2的整数次幂，可以通过y&(y-1) == 0判断
// 用highBit表示当前数最高有效位，遍历从1到n的每个正整数i，进行如下操作
// 1.若i&(i-1)==0，则令highBit = i，更新当前最高有效位
// 2.若bits[i]比bits[i-highBit]多1，由于是从小到大遍历，故bits[i-highBit]已知，令bits[i] = bits[i-highBit] + 1
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		int highBit = 0;
		for (int i = 1; i <= n; ++i) {
			if (i & (i - 1) == 0) {
				highBit = i;
			}
			dp[i] = dp[i - highBit] + 1;
		}
		return dp;
	}
};

// 官方解法三：动态规划——最低有效位，时间O(n) 4 ms，空间O(1) 7.7 MB
// 对正整数x，将其二进制右移一位，得到int(x/2)，若bits(int(x/2))，则可知道bits[x]:
// 1.若x是偶数，bits[x] = bits[int(x/2)]
// 2.若x是奇数，bits[x] = bits[int(x/2)] + 1
// 这两种情况可以合并成bits[x] = bits[int(x/2)] + x % 2
// 用二进制算法即bits[x] = bits[x>>1] + (x & 1)
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i >> 1] + (i & 1);
		}
		return dp;
	}
};

// 官方解法四：动态规划——最低设置位，时间O(n) 4 ms，空间O(1) 7.6 MB
// 定义正整数x的最低设置位位x的二进制表示中最低的1所在位，如10的二进制表示是1010，最低设置位为2
// 令y = x & (x - 1)，则y为将x的最低设置位从1变0后的数，显然0<=y<x，bits[x] = bits[y] + 1。
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i & (i - 1)] + 1;
		}
		return dp;
	}
};

// 直接使用内置函数，时间 0 ms 100%，空间 7.8 MB 36.09%
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> ret(n + 1);
		for (int i = 0; i <= n; ++i) {
			ret[i] = __builtin_popcount(i);
		}
		return ret;
	}
};

// LeetCode 101解法：时间 8 ms 24.79%，空间 7.7 MB 50.06%
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = i & 1 ? dp[i - 1] + 1 : dp[i >> 1];
		}
		return dp;
	}
};


// LeetCode 101解法：时间 4 ms 86.73%，空间 7.8 MB 40.80%
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i & (i - 1)] + 1;
		}
		return dp;
	}
};