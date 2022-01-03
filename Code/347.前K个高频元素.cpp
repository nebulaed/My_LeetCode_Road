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

// 官方解法二：基于快速排序，时间最坏O(n^2)，平均O(n) 8 ms，空间O(n) 13.3 MB
// 堆数组arr[l...r]做快速排序的过程中，将数组划分为两个部分arr[i...q-1]和arr[q+1...j]，并使得arr[i...q-1]中的每一个值都不超过arr[q]，且arr[q+1...j]中的每一个值都大于arr[q]。
// 根据k与左侧子数组arr[i...q-1]的长度q-i的大小关系：
// 1. 若k<=q-i，则数组arr[l...r]前k大的值，就等于子数组arr[i...q-1]前k大的值。
// 2. 否则，arr[l...r]前k大的值，就等于左侧子数组全部元素，加上右侧子数组arr[q+1...j]中前k-(q-i)大的值。
class Solution {
private:
	void qsort(vector<pair<int, int>>& vec, size_t start, size_t end, vector<int>& ret, int k) {
		int picked = rand() % (end - start + 1) + start;
		swap(vec[picked], vec[start]);
		
		int pivot = vec[start].second;
		size_t index = start;
		for (size_t i = start + 1; i <= end; ++i) {
			if (vec[i].second >= pivot) {
				swap(vec[index + 1], vec[i]);
				++index;
			}
		}
		swap(vec[start], vec[index]);

		if (k <= index - start) {
			qsort(vec, start, index - 1, ret, k);
		}
		else {
			for (size_t i = start; i <= index; ++i) {
				ret.emplace_back(vec[i].first);
			}
			if (k > index - start + 1) {
				qsort(vec, index + 1, end, ret, k - (index - start + 1));
			}
		}
	}

public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreqs;
		for (int num : nums) {
			++numFreqs[num];
		}
		vector<pair<int, int>> values;
		for (const auto& pair : numFreqs) {
			values.emplace_back(pair);
		}
		vector<int> ret;
		qsort(values, 0, values.size() - 1, ret, k);
		return ret;
	}
};
