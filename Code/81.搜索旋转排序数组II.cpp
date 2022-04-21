#include<iostream>
#include<vector>
using namespace std;

// 我的解法：二分查找，时间O(log n) 4 ms 87.24%，空间O(1) 13.5 MB 88.74%
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (nums[mid] == target) return true;
                // 中点和左端点数字相同，无法确定是左区间全部相同还是右区间全部相同。0 1 2 0 0 0 0也可能是3 3 3 3 0 1 2
                // 因此无法判断哪个区间是增序的
                // 因此，可以简单地把左端点右移一位，然后继续二分查找
            else if (nums[left] == nums[mid]) {
                ++left;
            }
                // 右区间为增序
            else if (nums[mid] <= nums[right]) {
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
                // 左区间为增序
            else {
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
        }
        return false;
    }
};

// 我的解法：时间 4 ms，空间 13.7 MB
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        for (int num : nums) {
            if (num == target) {
                return true;
            }
        }
        return false;
    }
};