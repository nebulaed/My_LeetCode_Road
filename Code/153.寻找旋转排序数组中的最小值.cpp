#include<vector>
using namespace std;

// 我的解法：二分查找，时间 O(log n) 4 ms 60.14%，空间 O(1) 9.8 MB 79.46%
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (nums[mid] < nums[right]) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        return nums[left];
    }
};