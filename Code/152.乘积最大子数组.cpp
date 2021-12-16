#include<iostream>
#include<array>
#include<vector>
using namespace std;

// 我参考官方思路的写法：动态规划，时间O(n) 8 ms，空间O(1) 13.4 MB
// 在最大子序和的基础上，要考虑当前位置的最优解不一定由前一位置的最优解转移得到，因此需要同时维护最小乘积和最大乘积，以保证[负得更多]的乘积保留下来，这样负负得正更大
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int curMax = 1, curMin = 1, maxProduct = nums[0];
		array<int, 3> temp; 
		for (const auto& num : nums) {
			temp[0] = curMax * num;
			temp[1] = curMin * num;
			temp[2] = num;
			curMax = *max_element(temp.begin(), temp.end());
			curMin = *min_element(temp.begin(), temp.end());
			maxProduct = maxProduct > curMax ? maxProduct : curMax;
		}
		return maxProduct;
	}
};

// 官方解法一：动态规划，时间O(n) 12 ms，空间O(1) 13.4 MB
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int maxF = nums[0], minF = nums[0], ans = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			int mx = maxF, mn = minF;
			maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
			minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
			ans = max(maxF, ans);
		}
		return ans;
	}
};