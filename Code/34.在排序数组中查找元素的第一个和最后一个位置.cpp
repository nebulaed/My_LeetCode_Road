#include<iostream>
#include<vector>
using namespace std;

// 我的蠢解法，时间复杂度O(n)
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		if (nums.empty()) return { -1,-1 };
		int start = -1;
		int end = -1;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] == target) {
				start = i;
				break;
			}
		}
		for (int i = nums.size() - 1; i >= 0; --i) {
			if (nums[i] == target) {
				end = i;
				break;
			}
		}
		return { start,end };
	}
};

// 官方解法，二分查找O(log n)
class Solution {
public:
	int binarySearch(const vector<int>& nums, const int& target, const bool& lower) {
		int left = 0, right = nums.size() - 1, ans = nums.size();
		while (left <= right) {
			int mid = (left + right) / 2;
			if (nums[mid] > target || (lower && nums[mid] >= target)) {
				right = mid - 1;
				ans = mid;
			}
			else {
				left = mid + 1;
			}
		}
		return ans;
	}
	vector<int> searchRange(vector<int>& nums, int target) {
		int leftidx = binarySearch(nums, target, true);
		int rightidx = binarySearch(nums, target, false) - 1;
		if (leftidx <= rightidx && rightidx < nums.size() && nums[leftidx] == target && nums[rightidx] == target) {
			return { leftidx,rightidx };
		}
		return { -1,-1 };
	}
};

// LeetCode 101解法：二分查找，自己实现lower_bount和upper_bound，采用左闭右闭的写法，时间 4 ms，空间 13.3 MB
class Solution {
private:
	int lower_bound(const vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (nums[mid] >= target) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return left;
	}

	int upper_bound(const vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (nums[mid] > target) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return left;
	}
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		if (nums.empty()) return { -1, -1 };
		int lower = lower_bound(nums, target);
		int upper = upper_bound(nums, target) - 1;
		if (lower == nums.size() || nums[lower] != target) {
			return { -1, -1 };
		}
		return { lower, upper };
	}
};

int main() {
	vector<int> nums = { 5,7,7,8,8,10 };
	int target = 6;
	
	Solution s;
	vector<int> ret = s.searchRange(nums, target);

	cout << "[";
	for (int i = 0; i < ret.size(); ++i) {
		cout << ret[i] << ",";
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}

