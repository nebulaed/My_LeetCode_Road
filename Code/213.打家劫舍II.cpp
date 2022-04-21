#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 我的解法参考一点官方思路：动态规划，时间 0 ms 100%，空间 7.7 MB 36%
// 思路，将i=0到n-1用198题的方法用dp数组遍历一次，再将i=1到n的情况用198题方法的dp数组遍历一次，取两次最大值
class Solution {
public:
    int rob(vector<int>& nums) {
        const size_t n = nums.size();
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        vector<int> dp(n - 1);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (size_t i = 2; i < n - 1; ++i) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        int ret = dp.back();
        dp[0] = nums[1];
        dp[1] = max(nums[1], nums[2]);
        for (size_t i = 2; i < n - 1; ++i) {
            dp[i] = max(dp[i - 2] + nums[i + 1], dp[i - 1]);
        }
        return max(ret, dp.back());
    }
};
// 滚动数组优化版：时间 0 ms 100%，空间 7.8 MB 17%
class Solution {
public:
    int rob(vector<int>& nums) {
        const size_t n = nums.size();
        int nums0 = nums.front();
        if (n == 1) return nums0;
        int nums1 = nums[1];
        if (n == 2) return max(nums0, nums1);
        vector<int> dp(n - 1);
        int first = nums0, second = max(nums0, nums1);
        for (size_t i = 2; i < n - 1; ++i) {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        int ret = second;
        first = nums1;
        second = max(nums1, nums[2]);
        for (size_t i = 2; i < n - 1; ++i) {
            int temp = second;
            second = max(first + nums[i + 1], second);
            first = temp;
        }
        return max(ret, second);
    }
};