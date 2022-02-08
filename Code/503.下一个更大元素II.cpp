#include<iostream>
#include<vector>
#include<stack>

using std::vector;
using std::stack;

// 我的解法一：暴力遍历，时间 148 ms 7%，空间 22.9 MB 99%
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n);
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            bool find = false;
            int j = i;
            while (++j < n) {
                if (nums[j] > num) {
                    find = true;
                    break;
                }
            }
            if (find) ret[i] = nums[j];
            else {
                find = false;
                j = -1;
                while (++j < i) {
                    if (nums[j] > num) {
                        find = true;
                        break;
                    }
                }
                if (find) ret[i] = nums[j];
                else ret[i] = -1;
            }
        }
        return ret;
    }
};

// 我的解法二：单调栈，时间 24 ms 94.20%，空间 24.1 MB 17.71%
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int> inds;
        for (int i = 0; i < n; ++i) {
            while (!inds.empty()) {
                int prev = inds.top();
                if (nums[i] <= nums[prev]) {
                    break;
                }
                inds.pop();
                ret[prev] = nums[i];
            }
            inds.emplace(i);
        }
        nums.reserve(2 * n - 1);
        nums.insert(nums.end(), nums.begin(), nums.end() - 1);
        for (int i = n; i < 2 * n - 1; ++i) {
            while (!inds.empty()) {
                int prev = inds.top();
                if (nums[i] <= nums[prev]) {
                    break;
                }
                inds.pop();
                if (prev < n) ret[prev] = nums[i];
            }
        }
        return ret;
    }
};