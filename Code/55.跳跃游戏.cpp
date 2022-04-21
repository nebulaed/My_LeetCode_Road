#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// 我的解法：贪心算法 时间 O(n) 44 ms，空间 O(1) 47.1 MB
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxPos = 0, n = nums.size();
        for (int i = 0; i < n - 1; ++i) {
            if (i <= maxPos) {
                maxPos = max(maxPos, i + nums[i]);
            }
            else break;
        }
        return maxPos >= n - 1;
    }
};

// 官方解法：贪心算法 40 ms, 47.2 MB
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxPos = 0, n = nums.size();
        for (int i = 0; i < n - 1; ++i) {
            if (i <= maxPos) {
                maxPos = max(maxPos, i + nums[i]);
            }
        }
        return maxPos >= n - 1;
    }
};

int main() {

    vector<int> nums = { 5,8,1,8,9,8,7,1,7,5,8,6,5,4,7,3,9,9,0,6,6,3,4,8,0,5,8,9,5,3,7,2,0,0,0,0,0,0,0,0,0,0,0,2,8,2,7,9,3,7,6,9,2,0,8,2,7,8,4,4,1,1,6,4,1,0,7,2,0,3,9,8,7,7,0,6,9,9,7,3,6,3,4,8,6,4,3,3,2,7,8,5,8,6,0 };

    Solution s;
    bool ret = s.canJump(nums);

    cout << ret << endl;

    return 0;
}