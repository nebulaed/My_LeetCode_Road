#include<iostream>
#include<vector>
#include<unordered_set>

using std::vector;
using std::unordered_set;

// 我的解法一：哈希集合，时间 O(n) 12 ms 33.51%，空间 O(n) 10.4 MB 31.63%
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		unordered_set<int> numSet;
		for (int num : nums) {
			if (numSet.count(num)) {
				numSet.erase(num);
			}
			else {
				numSet.emplace(num);
			}
		}
		auto it = numSet.begin();
		return { *it, *++it };
	}
};

// 我的解法二：位运算，时间 O(n) 4 ms 98.50%，空间 O(1) 9.7 MB 72.72%
// 原理：有两个只出现一次的数分别为x1和x2
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int mask = 0;
		for (int num : nums) {
			mask ^= num;
		}
		// 此时mask = x1 ^ x2
		// 注意当mask == INT_MIN时，-mask会溢出。
		// mask & -mask 取出了x1 ^ x2的二进制表示中最低位，假设为第l位1
		// 该位x1和x2中其中一个数第l位为0，另外一个数第l位为1
		if (mask != INT_MIN) mask &= -mask;
		vector<int> ret(2, 0);
		int& ret1 = ret[0], &ret2 = ret[1];
		// 此时可以将nums中的所有元素分成两类，其中一类包含所有二进制表示的第l位为0的数，另一类包含所有二进制表示的第l位为1的数。
		// 1. 对于所有在nums中出现两次的元素，该元素的两次出现会被包含在同一类中，所以会在异或中抵消掉。
		// 2. 对于任意一个在数组nums中只出现了一次的元素，即x1，x2，它们会被包含在不同类中。
		for (int num : nums) {
			if (num & mask) {
				ret1 ^= num;
			}
			else {
				ret2 ^= num;
			}
		}
		return ret;
	}
};