#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

// 我的解法：滑动窗口，时间 O(n) 4 ms 94.02%，空间 O(1) 10.3 MB 39.00%
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0, left = 0, right = 0, n = nums.size(), minLen = 1e6;
        while (right < n) {
            while (right < n && sum < target) {
                sum += nums[right++];
            }
            if (right >= n && sum < target) break;
            //minLen = min(minLen, right - left); // 没必要，因为后面会缩减窗口，加上这句时间会增至8 ms，60.90%
            while (sum >= target) {
                sum -= nums[left++];
            }
            minLen = min(minLen, right - left + 1);
        }
        return minLen == 1e6 ? 0 : minLen;
    }
};

// 官方解法二：前缀和+二分查找，时间 O(n log n) 16 ms 21.10%，空间 O(n) 10.6 MB 5.07%
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return n;
        // 求前缀和
        vector<int> sums(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        // 求最短满足和的子数组长度
        int ret = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            // 为使sums[end] - sums[i - 1] == target，需在sums中二分查找target + sums[i - 1]
            int endSum = target + sums[i - 1];
            auto end = lower_bound(sums.begin(), sums.end(), endSum);
            if (end != sums.end()) {
                ret = min(ret, static_cast<int>(end - sums.begin()) - i + 1);
            }
        }
        return ret == INT_MAX ? 0 : ret;
    }
};


int main() {

    int target = 7;
    vector<int> nums{ 2,3,1,2,4,3 };

    Solution sol;
    int ret = sol.minSubArrayLen(target, nums);

    cout << ret << endl;

    return 0;
}