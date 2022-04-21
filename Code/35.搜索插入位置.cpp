#include<iostream>
#include<vector>
using namespace std;

// 我的解法：二分查找
//class Solution {
//public:
//	int searchInsert(vector<int>& nums, int target) {
//		int left = 0, right = nums.size() - 1;
//		int mid;
//		while (left <= right) {
//			mid = (left + right) / 2;
//
//			if (nums[mid] > target) {
//				right = mid - 1;
//			}
//			else if (nums[mid] < target) {
//				left = mid + 1;
//			}
//			else {
//				return mid;
//			}
//		}
//		return nums[mid] < target ? mid + 1 : mid;
//	}
//};

// 官方解法：
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1, ans = n;
        while (left <= right) {
            int mid = (right + left) / 2;
            if (target <= nums[mid]) {
                ans = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    vector<int> nums = { 1,3,5,6 };
    int target = 3;

    Solution s;
    int ret = s.searchInsert(nums, target);

    cout << ret << endl;

    return 0;
}