#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;

// 我的解法一：动态规划，时间 8 ms 11.92%，空间 7.1 MB 9.36%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		size_t n = nums.size();
		vector<int> dp(n, 1);
		vector<int> prev(n, -1);
		int maxLength = 0;
		for (size_t i = 1; i <= n; ++i) {
			int& cur = dp[i - 1], curNum = nums[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				int pre = dp[j - 1], preNum = nums[j - 1];
				if (curNum > preNum && (j < 2 || preNum < prev[j - 1])) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = preNum;
					}
				}
				else if (curNum < preNum && (j < 2 || preNum > nums[j - 2])) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = preNum;
					}
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// 我的解法二：动态规划，时间 8 ms 11.92%，空间 7.1 MB 15.03%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		size_t n = nums.size();
		vector<int> dp(n, 1);
		vector<bool> prev(n, false);
		int maxLength = 0;
		for (size_t i = 1; i <= n; ++i) {
			int& cur = dp[i - 1], curNum = nums[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				int pre = dp[j - 1], preNum = nums[j - 1];
				bool preFlag = prev[j - 1];
				if (j < 2) {
					if (cur <= pre) {
						if (curNum > preNum) {
							cur = pre + 1;
							prev[i - 1] = true;
						}
						else if (curNum < preNum) {
							cur = pre + 1;
							prev[i - 1] = false;
						}
					}
					continue;
				}
				if (curNum > preNum && !preFlag) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = !preFlag;
					}
				}
				else if (curNum < preNum && preFlag) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = !preFlag;
					}
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// 我的解法三：贪心，时间 0 ms 100%，空间 7 MB 19.62%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		size_t n = nums.size();
		if (n == 1) return n;
		// 若第二个元素等于第一个元素，摆动序列的开头只有一个元素，否则有两个
		bool equal = nums[0] == nums[1];
		vector<int> endArr{ nums[0] };
		if (!equal) {
			endArr.emplace_back(nums[1]);
		}
		// 判断第二个元素是大于第一个元素还是小于第一个元素
		bool swing = nums[0] < nums[1];
		for (size_t i = 2; i < n; ++i) {
			int num = nums[i];
			// 若当前元素等于摆动序列结尾元素，直接跳过
			if (num == endArr.back()) {
				continue;
			}
			// 若摆动序列目前只有一个元素，当前元素只要与该元素不相等，都可以放进摆动序列
			if (equal) {
				// 若第二元素小于摆动序列第一元素，标记swing为假
				if (num < endArr.back()) {
					swing = false;
				}
				// 若第二元素大于摆动序列第一元素，标记swing为真
				else {
					swing = true;
				}
				endArr.emplace_back(num);
				// 摆动序列不再只有一个元素
				equal = false;
				continue;
			}
			// 若摆动序列结尾元素比上一元素大
			if (swing) {
				// 若当前元素比摆动序列结尾元素小，构成prev < end > num，可以放进摆动序列，并标记swing为假
				if (num < endArr.back()) {
					endArr.emplace_back(num);
					swing = false;
				}
				// 若当前元素比摆动序列结尾元素大，更新摆动序列结尾元素为num
				else {
					endArr.back() = num;
				}
			}
			// 若摆动序列结尾元素比上一元素小
			else {
				// 若当前元素比摆动序列结尾元素大，构成prev > end < num，可以放进摆动序列，并标记swing为真
				if (num > endArr.back()) {
					endArr.emplace_back(num);
					swing = true;
				}
				// 若当前元素比摆动序列结尾元素小，更新摆动序列结尾元素为num
				else {
					endArr.back() = num;
				}
			}
		}
		return endArr.size();
	}
};

// 官方解法一：动态规划，时间O(n) 4 ms 34.79%，空间O(n) 7.1 MB 16.44%
// 上升摆动序列表示最后一个元素上升的摆动序列，...
// 思路：列出状态表达式为：
// 1.up[i]表示以前i个元素中的某一个为结尾的最长上升摆动序列的长度
// 2.down[i]表示以前i个元素中的某一个为结尾的最长的下降摆动序列长度
// 以up[i]为例，说明其状态转移规则：
// 1. 当nums[i] <= nums[i - 1]，上升摆动序列无法扩展，up[i] = up[i - 1]
// 2. 当nums[i] > nums[i - 1]，up[i] = max(up[i - 1], down[i - 1] + 1)
// 类似地有，1.down[i] = down[i - 1]
// 2. down[i] = max(down[i-1], up[i - 1] + 1)
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) {
			return n;
		}
		vector<int> up(n), down(n);
		up[0] = down[0] = 1;
		for (int i = 1; i < n; i++) {
			if (nums[i] > nums[i - 1]) {
				up[i] = max(up[i - 1], down[i - 1] + 1);
				down[i] = down[i - 1];
			}
			else if (nums[i] < nums[i - 1]) {
				up[i] = up[i - 1];
				down[i] = max(up[i - 1] + 1, down[i - 1]);
			}
			else {
				up[i] = up[i - 1];
				down[i] = down[i - 1];
			}
		}
		return max(up[n - 1], down[n - 1]);
	}
};

// 官方解法二：动态规划+滚动数组，时间O(n) 0 ms 100%，空间O(1) 6.8 MB 69.86%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) {
			return n;
		}
		int up = 1, down = 1;
		for (int i = 1; i < n; i++) {
			if (nums[i] > nums[i - 1]) {
				// 注意到每有一个峰到谷，down才会+1，每有一个谷到峰up才会+1，过程中down与up的差恒不大于1，因此up<=down + 1且down <= up + 1，因此不必要对up和down+1取最大值，也不必对up+1和down取最大值
				//up = max(up, down + 1);
				up = down + 1;
				
			}
			else if (nums[i] < nums[i - 1]) {
				//down = max(up + 1, down);
				down = up + 1;
			}
		}
		return max(up, down);
	}
};

// 官方解法三：贪心，时间O(n) 0 ms 100%，空间O(1) 6.9 MB 60.73%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) return n;
		int prevdiff = nums[1] - nums[0];
		int ret = prevdiff != 0 ? 2 : 1;
		for (int i = 2; i < n; i++) {
			int diff = nums[i] - nums[i - 1];
			if ((diff > 0 && prevdiff <= 0) || (diff < 0 && prevdiff >= 0)) {
				++ret;
				prevdiff = diff;
			}
		}
		return ret;
	}
};