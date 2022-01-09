#include<iostream>
#include<vector>
#include<algorithm>
using std::vector;
using std::min;

// 我的解法：暴力遍历，时间 O(n) 8 ms 42.89%，空间 O(1) 12 MB 23.84%
class Solution {
public:
	int findMin(vector<int>& nums) {
		int minVal = 1e5;
		for (int num : nums) {
			minVal = min(minVal, num);
		}
		return minVal;
	}
};

// 我的解法：二分查找，时间 平均O(log n)，最坏O(n) 4 ms 87.02%，空间 O(1) 12 MB 18.62%
class Solution {
public:
	int findMin(vector<int>& nums) {
		int left = 0, right = nums.size() - 1, minVal = 1e4;
		while (left <= right) {
			int mid = (left + right) >> 1, midVal = nums[mid];
			if (nums[left] == midVal) {
				minVal = min(minVal, midVal);
				++left;
			}
			// 右区间为增序
			else if (midVal <= nums[right]) {
				minVal = min(minVal, midVal);
				right = mid - 1;
			}
			// 左区间为增序
			else {
				minVal = min(minVal, nums[left]);
				left = mid + 1;
			}
		}
		return minVal;
	}
};

// 官方解法：二分查找，时间 平均O(log n)，最坏O(n) 0 ms 100%，空间O(1) 11.9 MB 86.26%
// 我们考虑旋转排序数组中的最后一个元素x：在最小值右侧的元素，值一定小于等于x；在最小值左侧的元素，值一定大于等于x。
// 根据这条性质，通过二分查找的方法找出最小值
// 二分查找的每一步中，最小值就在low和high之间，中点为pivot。
// 将中点元素nums[pivot]和右边界元素nums[high]进行比较，可能有以下三种情况：
// 1. nums[pivot]<nums[high]。如下图所示，说明nums[pivot]是最小值右侧元素，可以忽略pivot到high间的右侧区间。
// 2. nums[pivot]>nums[high]，说明nums[pivot]是最小值左侧元素，忽略low到pivot之间的左侧区间。
// 3. nums[pivot]=nums[high]，不能确定nums[pivot]在最小值左侧还是右侧。如3 4 0 1 1 1 1和3 3 3 3 0 1 3。只能确定一定有与nums[high]相等的元素，只能忽略high
class Solution {
public:
	int findMin(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		while (low < high) {
			int pivot = (low + high) >> 1;
			int pivotVal = nums[pivot], highVal = nums[high];
			if (pivotVal < highVal) {
				high = pivot;
			}
			else if (pivotVal > highVal) {
				low = pivot + 1;
			}
			else --high;
		}
		return nums[low];
	}
};