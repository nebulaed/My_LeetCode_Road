#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

// 官方解法1：动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxSum = nums[0];
        for (const auto& num : nums) {
            pre = max(pre + num, num);
            maxSum = max(maxSum, pre);
        }
        return maxSum;
    }
};

// 官方解法2：贪心算法
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ret = INT_MIN, sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            ret = max(ret, sum);
            if (sum < 0) {
                sum = 0;
            }
        }
        return ret;
    }
};

// 官方解法3：分治，优点是可以解决任意子区间[l,r]的问题。在O(log n)的时间内求得任意区间内的答案。
class Solution {
public:
    struct Status {
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status l, Status r) {
        int iSum = l.iSum + r.iSum;
        int lSum = max(l.lSum, l.iSum + r.lSum);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
        return (Status) { lSum, rSum, mSum, iSum };
    }

    Status get(vector<int>& a, int l, int r) {
        if (l == r) {
            return (Status) { a[l], a[l], a[l], a[l] };
        }
        int m = (l + r) >> 1;
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        return pushUp(lSub, rSub);
    }

    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};


int main() {

    vector<int> nums = { 1 };

    Solution s;
    int ret = s.maxSubArray(nums);

    cout << ret << endl;

    return 0;
}