#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

// LeetCode 101解法：时间 4 ms 47.82%，空间 7.1 MB 74%
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        size_t length = nums.size();
        if (length <= 2) return 0;
        vector<int> dp(length, 0);
        for (size_t i = 2; i < length; ++i) {
            int temp = nums[i - 1];
            if (nums[i] - temp == temp - nums[i - 2]) {
                dp[i] = dp[i - 1] + 1;
            }
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }
};