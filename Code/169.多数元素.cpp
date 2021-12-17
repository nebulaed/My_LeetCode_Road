#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

// �ҵĽⷨ1����ϣ��ʱ��O(n) 20 ms���ռ�O(n) 19.2 MB
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int maxFreq = 0, maxFreqInd = -1;
		unordered_map<int, int> numFreq;
		for (const auto& num : nums) {
			if (!numFreq.count(num)) {
				numFreq[num] = 1;
			}
			else {
				++numFreq[num];
			}
			if (numFreq[num] > maxFreq) {
				maxFreq = numFreq[num];
				maxFreqInd = num;
				if (maxFreq > nums.size() / 2) break;
			}
		}
		return maxFreqInd;
	}
};

// �ҵĽⷨ2������ʱ��O(nlogn) 8 ms���ռ�O(log n) 19.1 MB�����������Դ��������㷨����ҪO(n logn)�����Լ�д�Ķ�����ֻ��ҪO(1)�ռ䡣
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int freq = 1, n = nums.size();
		for (int i = 1; i < n; ++i) {
			if (nums[i] == nums[i - 1]) ++freq;
			else freq = 1;
			if (freq > n / 2) return nums[i];
		}
		return nums[0];
	}
};

// �ٷ��ⷨ��������ʱ��O(n logn) 24 ms���ռ�O(log n) 19 MB
// ����󣬶�������������n/2Ԫ�ص����飬��λ����Ȼ������
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return nums[nums.size() / 2];
	}
};

// �ٷ��ⷨ������������ʱ��O(��)��ƽ��ʱ�临�Ӷ�O(n) 16 ms���ռ�O(1) 19.1 MB
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		while (true) {
			int candidate = nums[rand() % nums.size()];
			int count = 0;
			for (int num : nums) {
				if (num == candidate) ++count;
			}
			if (count > nums.size() / 2) return candidate;
		}
		return -1;
	}
};

// �ٷ��ⷨ�ģ����Σ�ʱ��O(n log n) 24 ms���ռ�O(log n) 19.2 MB
class Solution {
public:
	int count_in_range(vector<int>& nums, int target, int lo, int hi) {
		int count = 0;
		for (int i = lo; i <= hi; ++i) {
			if (nums[i] == target) ++count;
		}
		return count;
	}
	int majority_element_rec(vector<int>& nums, int lo, int hi) {
		if (lo == hi) return nums[lo];
		int mid = (lo + hi) / 2;
		int left_majority = majority_element_rec(nums, lo, mid);
		int right_majority = majority_element_rec(nums, mid + 1, hi);
		if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2) {
			return left_majority;
		}
		if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2) {
			return right_majority;
		}
		return -1;
	}
	int majorityElement(vector<int>& nums) {
		return majority_element_rec(nums, 0, nums.size() - 1);
	}
};

// �ٷ��ⷨ�壺Boyer-Moore ͶƱ�㷨��ʱ��O(n) 12 ms���ռ�O(1) 19.2 MB
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		int candidate = -1, count = 0;
		for (const int& num : nums) {
			if (num == candidate) ++count;
			else if (--count < 0) {
				candidate = num;
				count = 1;
			}
		}
		return candidate;
	}
};