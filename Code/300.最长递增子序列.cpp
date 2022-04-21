#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一参考官方答案一思路：时间O(n^2) 228 ms，空间O(n) 10.4 MB
// 思路：定义dp[i]为以第i个数字结尾的最长单调递增子序列的长度，注意nums[i]必须被选取
// 从小到大的计算dp数组的值。状态转移方程为：dp[i] = dp[j] + 1，其中0<=j<i且nums[j]<nums[i]且dp[j]>=dp[i]
// 即考虑往dp[0...i-1]中最长的单调递增子序列后再加一个nums[i]。
// 最后，整个数组的最长单调递增子序列即所有dp[i]中的最大值。
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> dp(length, 1);
		for (size_t i = 1; i <= length; ++i) {
			for (size_t j = i - 1; j > 0; --j) {
				if (nums[i - 1] > nums[j - 1] && dp[i - 1] <= dp[j - 1]) {
					dp[i - 1] = dp[j - 1] + 1;
				}
			}
		}
		return *max_element(dp.begin(), dp.end());
	}
};

// 我的解法一优化：时间 212 ms 64.05%，空间 10.2 MB 57%
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> dp(length, 1);
		int maxLength = 0;
		for (size_t i = 1; i <= length; ++i) {
			int& cur = dp[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				if (nums[i - 1] > nums[j - 1]) {
					cur = max(dp[j - 1] + 1, cur);
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// 我的解法二：贪心+二分查找，时间O(n log n) 8 ms，空间O(n) 10.2 MB
// 考虑一个简单的贪心，要使单调递增子序列尽可能地长，必须让序列上升得尽可能慢，因此希望每次在上升子序列最后加上得那个数尽可能小。
// 基于该贪心思路，维护一数组d[i]，表示长度为i的最长单调递增子序列的末尾元素的最小值，用len记录目前最长单调递增子序列的长度
// 起始时len为1，d[1] = nums[0]
// d[i]是关于i单调递增的。
// 我们依次遍历数组nums中的每个元素，并更新数组d和len的值。如果nums[i]>d[len]，则更新len = len + 1，否则在d[1...len]中找满足d[i-1] < nums[j] < d[i]的下标i，并更新d[i] = nums[j]。
// 根据d数组的单调性，我们可以使用二分查找寻找下标i。
// 最后整个算法流程为：
// 1.设当前已求出的最长单调递增子序列的长度为len，从前往后遍历数组nums，在遍历到nums[i]时：
// 1.1 若nums[i]>d[len]，则直接加入到d数组末尾，并更新len = len + 1;
// 1.2 否则，在d数组中二分查找，找到第一个比nums[i]小的数d[k]，并更新d[k+1] = nums[i]
class Solution {
private:
	size_t binarySearch(const vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (target <= nums[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return left;
	}

public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> endArr(1, nums[0]);
		for (size_t i = 1; i < nums.size(); ++i) {
			int curr = nums[i];
			if (curr > endArr.back()) {
				endArr.emplace_back(curr);
			}
			else {
				endArr[binarySearch(endArr, curr)] = curr;
			}
		}
		return endArr.size();
	}
};

// LeetCode 101解法：动态规划+利用官方二分查找，时间 O(n log n) 8 ms 89.70%，空间 O(n) 10.2 MB 77.92%
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> dp{ nums[0] };
		for (size_t i = 1; i < length; ++i) {
			int num = nums[i];
			if (dp.back() < num) {
				dp.emplace_back(num);
			}
			else {
				auto it = lower_bound(dp.begin(), dp.end(), num);
				*it = num;
			}
		}
		return dp.size();
	}
};

int main() {

	vector<int> nums = { 5,7,-24,12,13,2,3,12,5,6,35 };

	Solution s;
	int ret = s.lengthOfLIS(nums);

	cout << ret << "\n";

	return 0;
}