#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;

// 本题是NP完全问题，找不到多项式时间复杂度的解法，因此必须尝试非多项式时间复杂度的解法，例如时间复杂度与元素大小相关的动态规划

// 本题的转述：给定一个只包含正整数的非空数组nums[0]，判断是否可以从数组中选出一些数字，使得这些数字的和等于整个数组元素和的一半。
// 该问题可以转换成0-1背包问题。

// 在使用动态规划求解之前，先进行以下判断：
// 1. 根据数组的长度n判断数组是否可以被划分。若n < 2，则直接返回false
// 2. 计算整个数组的元素和sum以及最大元素maxNum。如果sum是奇数，返回false。若sum是偶数，令target = sum/2，若maxNum > target，返回false

// 创建二维数组dp，包含n行target + 1列，其中dp[i][j]表示从数组的[0, i]下标范围内选取任意数量(包括0)个正整数，是否存在一种选取方案使得被选取的正整数的和等于j。
// 初始时，dp中的全部元素都是false。

// 在定义状态后，需要考虑边界情况。以下两种情况都属于边界情况。
// 1.只要不选取任何正整数，被选取正整数和就为0。因此对于所有0<=i<n，都有dp[i][0] = true
// 2.当i==0时，只有一个正整数nums[0]可被选取，因此dp[0][nums[0]] = true

// 对于i > 0 且 j > 0，需要考虑以下两种情况：
// 1. 若j >= nums[i]，对于当前数字nums[i]，可选也可以不选，这两种只要有一个前导情况为true，就有dp[i][j] = true
// 1.1 若不选取nums[i]，则dp[i][j] = dp[i-1][j]
// 1.2 若选取nums[i]，则dp[i][j] = dp[i-1][j-nums[i]]
// 所以，nums[i] = dp[i-1][j] | dp[i-1][j-nums[i]]
// 2. 若j < nums[i]，则在选取的数字和等于j的情况下无法选取当前数字nums[i]，那么dp[i][j] = dp[i-1][j]

// 官方解法：动态规划，时间O(n×target) 256 ms, 空间O(n×target) 73.4 MB
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        size_t length = nums.size();
        if (length < 2) return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int target = sum / 2, maxNum = *max_element(nums.begin(), nums.end());
        if (maxNum > target) return false;
        vector<vector<int>> dp(length, vector<int>(target + 1, 0));
        for (size_t i = 0; i < length; ++i) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;
        for (size_t i = 1; i < length; ++i) {
            for (size_t j = 1; j < target + 1; ++j) {
                if (j >= nums[i]) {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[length - 1][target];
    }
};

// 官方解法优化：动态规划+滚动数组，时间O(n×target) 56 ms, 空间O(target) 9.2 MB
// 用vector<int> 取代 bool 数组，时间 128 ms，空间 9.6 MB
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        size_t length = nums.size();
        if (length < 2) return false;
        int sum = 0, maxNum = 0;
        for (int num : nums) {
            sum += num;
            maxNum = max(num, maxNum);
        }
        if (sum & 1) return false;
        int target = sum / 2;
        if (maxNum > target) return false;
        bool* dp = new bool[target + 1]();
        dp[0] = dp[nums[0]] = true;
        for (size_t i = 1; i < length; ++i) {
            // 注意：该层循环需要从大到小循环，否则dp[j-nums[i]]已被更新为当前层的值
            // 我的写法：
            //for (size_t j = target; j != -1; --j) {
            //	if (j >= nums[i]) {
            //		dp[j] |= dp[j - nums[i]];
            //	}
            //}
            // 官方写法更佳：
            for (size_t j = target; j >= nums[i]; --j) {
                dp[j] |= dp[j - nums[i]];
            }
            if (dp[target]) return true;
        }
        return dp[target];
    }
};

// LeetCode 101解法：时间 O(n*sum/2) 232 ms 26.25%，空间O(n*sum/2) 11.7 MB 35.39%
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int target = sum >> 1, n = nums.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= target; ++j) {
                int num = nums[i - 1];
                if (j < num) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
                }
            }
        }
        return dp[n][target];
    }
};

// LeetCode 101空间压缩解法：时间 O(n*sum/2) 92 ms 88%，空间O(sum/2) 8.8 MB 94%
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int target = sum >> 1, n = nums.size();
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            int num = nums[i - 1];
            for (int j = target; j >= num; --j) {
                if (j >= num) {
                    dp[j] = dp[j] | dp[j - num];
                }
            }
        }
        return dp[target];
    }
};