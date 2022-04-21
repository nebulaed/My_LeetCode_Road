#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

// 我的解法：前缀和，时间 20 ms 78.90%，空间 16.7 MB 31.61%
class NumArray {
private:
    vector<int> prefixSum;
public:
    NumArray(vector<int>& nums) : prefixSum(nums) {
        int n = prefixSum.size();
        for (int i = 1; i < n; ++i) {
            prefixSum[i] += prefixSum[i - 1];
        }
    }

    int sumRange(int left, int right) {
        return prefixSum[right] - (left == 0 ? 0 : prefixSum[left - 1]);
    }
};

// LeetCode 101解法：前缀和，时间 24 ms 51.90%，空间 16.7 MB 17.46%
class NumArray {
private:
    vector<int> prefixSum;
public:
    NumArray(vector<int>& nums) : prefixSum(nums.size() + 1, 0) {
        partial_sum(nums.begin(), nums.end(), prefixSum.begin() + 1);
    }

    int sumRange(int left, int right) {
        return prefixSum[right + 1] - prefixSum[left];
    }
};