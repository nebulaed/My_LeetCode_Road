#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<queue>
using namespace std;

// 我的解法：哈希表+二叉排序树，时间O(n log n) 16 ms，空间O(n) 13.5 MB
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreq;
		for (int num : nums) {
			++numFreq[num];
		}
		multimap<int, int> freqNum;
		for (auto it = numFreq.begin(); it != numFreq.end(); ++it) {
			freqNum.emplace(it->second, it->first);
		}
		vector<int> ret;
		int count = 0;
		for (auto rit = freqNum.rbegin(); count < k; ++rit) {
			ret.emplace_back(rit->second);
			++count;
		}
		return ret;
	}
};

// 官方解法一：堆，时间O(n log k) 16 ms，空间O(n)+O(k) = O(n) 13.2 MB
// 先用哈希表记录每个数字出现的次数，形成一个“出现次数数组”
// 利用堆的思想：建立一个小顶堆，然后遍历出现次数数组：
// 1. 如果堆的元素个数小于k，直接插入堆中
// 2. 如果堆的元素个数等于k，则检查堆顶与当前数出现次数的大小。如果堆顶更大，舍弃当前值；否则弹出堆顶，将当前值插入堆中
class Solution {
private:
	static bool cmp(pair<int, int>& left, pair<int, int>& right){
		return left.second > right.second;
	}
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreq;
		for (int num : nums) {
			++numFreq[num];
		}

		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
		for (const auto& item : numFreq) {
			if (q.size() == k) {
				if (q.top().second < item.second) {
					q.pop();
					q.emplace(item);
				}
			}
			else q.emplace(item);
		}
		vector<int> ret;
		while (!q.empty()) {
			ret.emplace_back(q.top().first);
			q.pop();
		}
		return ret;
	}
};

// 官方解法二：基于快速排序
