#include<iostream>
#include<vector>
using namespace std;

// 我的解法
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 1) return nums[0] == target ? 0 : -1;
        int k;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] > nums[i + 1]) {
                k = i;
                break;
            }
        }
        int left, right;
        if (target >= nums[0]) {
            left = 0;
            right = k;
        }
        else {
            left = k + 1;
            right = nums.size() - 1;
        }

        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] > target) {
                right = middle - 1;
            }
            else if (nums[middle] < target) {
                left = middle + 1;
            }
            else {
                return middle;
            }
        }
        return -1;
    }
};

// 官方解法1：
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if (!n) {
            return -1;
        }
        if (n == 1) {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) return mid;
            if (nums[0] <= nums[mid]) {
                if (nums[0] <= target && target < nums[mid]) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }
            else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    vector<int> nums = { 4,5,6,7,0,1,2 };
    int target = 0;

    Solution s;
    int ret = s.search(nums, target);

    cout << ret << endl;

    return 0;
}