#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<functional>

using std::vector;
using std::sort;
using std::priority_queue;
using std::less;
using std::greater;
using std::nth_element;
using std::swap;

// 我的解法一：排序求中位数，时间O(n logn) 12 ms 56.34%，空间 O(1) 10.6 MB 65.75%
class Solution {
public:
	int minMoves2(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int n = nums.size(), mid = n >> 1;
		int median = n & 1 ? nums[mid] : ((nums[mid] + nums[mid - 1]) >> 1);
		int ret = 0;
		for (int num : nums) {
			ret += abs(num - median);
		}
		return ret;
	}
};

// 我的解法二：优先队列求中位数，时间O(n) 12 ms 56.34%，空间 O(n) 11.2 MB 5.14%
class Solution {
public:
	int minMoves2(vector<int>& nums) {
		// 大顶堆
		priority_queue<int, vector<int>, less<int>> queMin;
		// 小顶堆
		priority_queue<int, vector<int>, greater<int>> queMax;

		for (int num : nums) {
			// queMin.top() == max{queMin}
			if (queMin.empty() || num <= queMin.top()) {
				queMin.emplace(num);
				if (queMax.size() + 1 < queMin.size()) {
					queMax.emplace(queMin.top());
					queMin.pop();
				}
			}
			else {
				queMax.emplace(num);
				if (queMax.size() > queMin.size()) {
					queMin.emplace(queMax.top());
					queMax.pop();
				}
			}
		}
		int n = nums.size();
		int median = n & 1 ? queMin.top() : (queMin.top() + queMax.top()) >> 1;
		int ret = 0;
		for (int num : nums) {
			ret += abs(num - median);
		}
		return ret;
	}
};

// 我的解法三：快速选择算法，调用nth_element，时间 12 ms 56.34%，空间 10.5 MB 82.53%
class Solution {
public:
	int minMoves2(vector<int>& nums) {
		int n = nums.size(), mid = n >> 1;
		auto it1 = nums.end() - mid - 1;
		nth_element(nums.begin(), it1, nums.end());
		int median = *it1;
		if (!(n & 1)) {
			median = *it1;
			auto it2 = nums.end() - mid;
			nth_element(nums.begin(), it2, nums.end());
			median = (*it2 + median) >> 1;
		}
		int ret = 0;
		for (int num : nums) {
			ret += abs(num - median);
		}
		return ret;
	}
};

// 我的解法四：自写随机选取枢轴+快速选择算法，时间 8 ms 88.70%，空间 10.5 MB 79.45%
class Solution {
private:
	int quickSelect(vector<int>& nums, int left, int right, int index) {
		int q = randomPartition(nums, left, right);
		if (q == index) return nums[q];
		else {
			return q < index ? quickSelect(nums, q + 1, right, index) : quickSelect(nums, left, q - 1, index);
		}
	}

	inline int randomPartition(vector<int>& nums, int left, int right) {
		int i = rand() % (right - left + 1) + left;
		swap(nums[i], nums[right]);
		return partition(nums, left, right);
	}

	inline int partition(vector<int> & nums, int left, int right) {
		int x = nums[right], i = left - 1;
		for (int j = left; j < right; ++j) {
			if (nums[j] < x) {
				swap(nums[++i], nums[j]);
			}
		}
		swap(nums[i + 1], nums[right]);
		return i + 1;
	}

public:
	int minMoves2(vector<int> & nums) {
		int n = nums.size(), mid = n >> 1;
		int median = 0;
		if (n & 1) {
			median = quickSelect(nums, 0, n - 1, mid);
		}
		else {
			median = (quickSelect(nums, 0, n - 1, mid - 1) + quickSelect(nums, 0, n - 1, mid)) >> 1;
		}
		int ret = 0;
		for (int num : nums) {
			ret += abs(num - median);
		}
		return ret;
	}
};

// 我的解法五：三数取中+快速选择算法，时间 8 ms 88.70%，空间 10.6 MB 67.12%
class Solution {
private:
	int quickSelect(vector<int>& nums, int left, int right, int target) {
		while (left < right) {
			int mid = partition(nums, left, right);
			if (mid == target) {
				return nums[mid];
			}
			else if (mid < target) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		return nums[left];
	}

	int partition(vector<int>& nums, int left, int right) {
		int mid = (left + right) >> 1;
		if (nums[left] > nums[right]) {
			swap(nums[left], nums[right]);
		}
		if (nums[mid] > nums[right]) {
			swap(nums[right], nums[mid]);
		}
		if (nums[mid] > nums[left]) {
			swap(nums[mid], nums[left]);
		}
		int key = nums[left];
		while (left < right) {
			while (left < right && key <= nums[right]) {
				--right;
			}
			nums[left] = nums[right];
			while (left < right && nums[left] <= key) {
				++left;
			}
			nums[right] = nums[left];
		}
		nums[left] = key;
		return right;
	}

public:
	int minMoves2(vector<int>& nums) {
		int n = nums.size(), mid = n >> 1;
		int median = 0;
		if (n & 1) {
			median = quickSelect(nums, 0, n - 1, mid);
		}
		else {
			median = (quickSelect(nums, 0, n - 1, mid - 1) + quickSelect(nums, 0, n - 1, mid)) >> 1;
		}
		int ret = 0;
		for (int num : nums) {
			ret += abs(num - median);
		}
		return ret;
	}
};