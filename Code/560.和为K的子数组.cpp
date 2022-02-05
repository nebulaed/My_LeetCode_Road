#include<iostream>
#include<vector>
#include<unordered_map>

using std::vector;
using std::unordered_map;

// 我的解法：前缀和+哈希表，时间 84 ms 25.68%，空间 40.7 MB 13%
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		// count表示不从0开始的和为k的连续区间数量
		int prefixSum = 0, count = 0;
		// 前缀和出现次数哈希表，key为前缀和，val为出现次数
		unordered_map<int, int> prefixSumFreq;
		for (int num : nums) {
			// 当前位置前缀和
			prefixSum += num;
			// 该前缀和出现次数+1
			++prefixSumFreq[prefixSum];
			// 由于prefixSum - (prefixSum - k) == k，所以前缀和等于prefixSum - k的出现次数就是不从0开始的和为k的连续区间数量
			// 当k为0时，要注意prefixSum - k == prefixSum，要-1去掉自己
			count += prefixSumFreq[prefixSum - k] + (k == 0 ? -1 : 0);
		}
		return prefixSumFreq[k] + count;
	}
};

// 我的解法小优化：前缀和+哈希表，时间 84 ms 25.68%，空间 40.7 MB 16.51%
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		// count表示不从0开始的和为k的连续区间数量
		int prefixSum = 0, count = 0;
		// 前缀和出现次数哈希表，key为前缀和，val为出现次数
		unordered_map<int, int> prefixSumFreq;
		for (int num : nums) {
			// 当前位置前缀和
			prefixSum += num;
			// 由于prefixSum - (prefixSum - k) == k，所以前缀和等于prefixSum - k的出现次数就是不从0开始的和为k的连续区间数量
			count += prefixSumFreq[prefixSum - k];
			// 该前缀和出现次数+1
			++prefixSumFreq[prefixSum];
		}
		return prefixSumFreq[k] + count;
	}
};

// LeetCode 101解法：前缀和+哈希表，时间 80 ms 31.49%，空间 40.6 MB 22.97%
// 思路：利用前缀和，不同的是这里我们使用一个哈希表hashmap，其键是前缀和，而值是该前缀和出现的次数。在我们遍历到位置i 时，假设当前的前缀和是psum，那么hashmap[psum - k]即为以当前位置结尾、满足条件的区间个数。
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		int prefixSum = 0, count = 0;
		unordered_map<int, int> prefixSumFreq;
		prefixSumFreq[0] = 1;
		for (int num : nums) {
			prefixSum += num;
			count += prefixSumFreq[prefixSum - k];
			++prefixSumFreq[prefixSum];
		}
		return count;
	}
};