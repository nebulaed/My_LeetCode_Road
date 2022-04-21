#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// 网友解法：时间 4 ms 79.94%，空间 8.6 MB 21.04%
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        vector<array<int, 4>> dp(n, array<int, 4>{});
        int preSum = 0;
        for (int i = 0; i < firstLen; ++i) {
            preSum += nums[i];
        }
        int maxSum = preSum;
        dp[firstLen - 1][0] = maxSum;
        for (int i = firstLen; i < n; ++i) {
            preSum -= nums[i - firstLen];
            preSum += nums[i];
            maxSum = max(maxSum, preSum);
            dp[i][0] = maxSum;
        }
        preSum = 0;
        for (int i = 0; i < secondLen; ++i) {
            preSum += nums[i];
        }
        maxSum = preSum;
        dp[secondLen - 1][1] = maxSum;

        for (int i = secondLen; i < n; ++i) {
            preSum -= nums[i - secondLen];
            preSum += nums[i];
            maxSum = max(maxSum, preSum);
            dp[i][1] = maxSum;
        }
        preSum = 0;
        for (int i = n - 1; i >= n - firstLen; --i)
        {
            preSum += nums[i];
        }
        maxSum = preSum;
        dp[n - firstLen][2] = maxSum;
        for (int i = n - firstLen - 1; i >= 0; --i)
        {
            preSum -= nums[i + firstLen];
            preSum += nums[i];
            maxSum = max(maxSum, preSum);
            dp[i][2] = maxSum;
        }

        preSum = 0;
        for (int i = n - 1; i >= n - secondLen; --i)
        {
            preSum += nums[i];
        }
        maxSum = preSum;
        dp[n - secondLen][3] = maxSum;
        for (int i = n - secondLen - 1; i >= 0; --i)
        {
            preSum -= nums[i + secondLen];
            preSum += nums[i];
            maxSum = max(maxSum, preSum);
            dp[i][3] = maxSum;
        }

        //计算答案
        int res = 0;
        //L在secondLen左边
        for (int i = firstLen; i <= n - secondLen; ++i)
            res = max(res, dp[i - 1][0] + dp[i][3]);
        //secondLen在L左边
        for (int i = secondLen; i <= n - firstLen; ++i)
            res = max(res, dp[i - 1][1] + dp[i][2]);

        return res;
    }
};

// lee215解法：时间 4 ms 79.94%，空间 8.3 MB 80.26%
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        // 求前缀和
        for (int i = 1; i < n; ++i)
            nums[i] += nums[i - 1];
        //初始化最终最大值的初始值，初始化firstLen子数组和最大值，初始值化secondLen子数组和最大值
        //初始化后，是前缀和数组中满足当前子数组长度下最靠左边的几个元素值
        int res = nums[firstLen + secondLen - 1], firstMax = nums[firstLen - 1], secondMax = nums[secondLen - 1];
        for (int i = firstLen + secondLen; i < n; ++i) {
            //从前往后遍历数组，找长度为firstLen的子数组最大和，此时是模拟firstLen数组在secondLen数组左边，nums[i - secondLen]是当前位置，secondLen长度子数组之前的第一个元素
            firstMax = max(firstMax, nums[i - secondLen] - nums[i - firstLen - secondLen]);
            //从前往后遍历数组，找长度为M的子数组最大和，此时是模拟M数组在L数组左边，A[i - L]是当前位置，L长度子数组之前的第一个元素
            secondMax = max(secondMax, nums[i - firstLen] - nums[i - firstLen - secondLen]);
            //比较firstLen在左边的最大值+最近的一个secondLen子数组和，secondLen在左边并取最大值+最近的一个L子数组和
            res = max(res, max(firstMax + nums[i] - nums[i - secondLen], secondMax + nums[i] - nums[i - firstLen]));
        }
        return res;
    }
};