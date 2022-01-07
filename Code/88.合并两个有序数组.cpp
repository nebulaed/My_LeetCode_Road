#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：双指针从尾到头反向遍历，时间O(m+n) 4 ms，空间O(1) 8.9 MB
class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int end = nums1.size() - 1;
		while (n != 0) {
			if (m != 0 && nums1[m - 1] > nums2[n - 1]) {
				nums1[end--] = nums1[--m];
			}
			else {
				nums1[end--] = nums2[--n];
			}
		}
	}
};

// 官方解法一：直接合并后排序，时间O((m+n) log(m+n)) 0 ms，空间O(log(m+n)) 8.9 MB
class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		for (int i = 0; i < n; ++i) {
			nums1[m + i] = nums2[i];
		}
		sort(nums1.begin(), nums1.end());
	}
};

// 官方解法二：正向双指针，时间O(m+n) 4 ms，空间O(m+n) 8.8 MB
class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int ptr1 = 0, ptr2 = 0;
		int* sorted = new int[m + n]();
		int cur = 0;
		while (ptr1 < m || ptr2 < n) {
			if (ptr1 == m) {
				cur = nums2[ptr2++];
			}
			else if (ptr2 == n) {
				cur = nums1[ptr1++];
			}
			else if (nums1[ptr1] < nums2[ptr2]) {
				cur = nums1[ptr1++];
			}
			else {
				cur = nums2[ptr2++];
			}
			sorted[ptr1 + ptr2 - 1] = cur;
		}
		for (int i = 0; i < m + n; ++i) {
			nums1[i] = sorted[i];
		}
		delete[] sorted;
	}
};