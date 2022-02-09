#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<functional>

using std::vector;
using std::stack;
using std::upper_bound;
using std::greater;

// 我的解法一：暴力遍历，时间 O(n^2) 148 ms 7%，空间 O(1) 22.9 MB 99%
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

// 我的解法二：单调栈+拼接数组，时间 O(n) 24 ms 94.20%，空间 O(n) 24.1 MB 17.71%
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int, vector<int>> inds;
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
                ret[prev] = nums[i];
            }
        }
        return ret;
    }
};

// 我的解法三：单调栈+两次循环，时间 24 ms 94.21%，空间 22.9 MB 98.24%  
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int, vector<int>> inds;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            while (!inds.empty()) {
                int prev = inds.top();
                if (num <= nums[prev]) {
                    break;
                }
                inds.pop();
                ret[prev] = num;
            }
            inds.emplace(i);
        }
        for (int i = 0; i < n - 1; ++i) {
            int num = nums[i];
            while (!inds.empty()) {
                int prev = inds.top();
                if (num <= nums[prev]) {
                    break;
                }
                inds.pop();
                ret[prev] = num;
            }
        }
        return ret;
    }
};


// 官方解法：单调栈+取模，时间 24 ms 94.21%，空间 23.1 MB 94.40%
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int, vector<int>> inds;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int num = nums[i % n];
            while (!inds.empty()) {
                int prev = inds.top();
                if (num <= nums[prev]) {
                    break;
                }
                inds.pop();
                ret[prev] = num;
            }
            inds.emplace(i % n);
        }
        return ret;
    }
};

// 官方解法自行优化：单调栈+二分查找，时间 20 ms 98.42%，空间 23.2 MB 86.70%
class Solution {
private:
    int binarySearch(const vector<int>& inds, const vector<int>& nums, int target) {
        int left = 0, right = inds.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[inds[mid]] < target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return left;
    }
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        vector<int> inds;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int cur = i % n, num = nums[cur];
            if (!inds.empty()) {
                int prev = binarySearch(inds, nums, num);
                // 二分查找到的prev若大于等于inds.size()说明没查找到第一个对应的nums[prev]大于等于nums[i%n]
                if (prev < inds.size()) {
                    // 对prev即后面的每一个inds中元素，它们的下一个更大元素都是num
                    for (int j = prev; j < inds.size(); ++j) {
                        ret[inds[j]] = num;
                    }
                    // prev到后面的全部擦除
                    inds.erase(inds.begin() + prev, inds.end());
                }
            }
            inds.emplace_back(cur);
        }
        return ret;
    }
};

int main() {

    using std::cout;
    using std::endl;

    vector<int> nums1 = { 1,2,1 };
    vector<int> nums2 = { 1,2,3,4,3 };
    vector<int> nums3 = { 5,4,3,2,1 };

    Solution s;
    vector<int> ret1 = s.nextGreaterElements(nums3);

    vector<int> ret2 = s.nextGreaterElements(nums2);

    cout << "[";
    for (int num : ret1) {
        cout << num << ",";
    }
    cout << "]" << endl;

    cout << "[";
    for (int num : ret2) {
        cout << num << ",";
    }
    cout << "]" << endl;

    system("pause");
    return 0;
}