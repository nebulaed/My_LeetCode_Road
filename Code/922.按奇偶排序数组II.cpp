#include<iostream>
#include<vector>
using namespace std;


// 我的解法：C语言解法，双指针，时间 84 ms 10.06%，空间 12.6 MB 94.67%
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int* sortArrayByParityII(int* nums, int numsSize, int* returnSize) {
    int odd = 1, even = 0;
    while (odd < numsSize) {
        if (!((*(nums + odd)) & 1)) {
            // 注意这里可以舍去对even是否超出边界的检查，因为有odd必定有对应的even
            while (!((*(nums + even)) & 1)) {
                even += 2;
            }
            swap(nums + odd, nums + even);
        }
        odd += 2;
    }
    *returnSize = numsSize;
    return nums;
}

// 我的解法：双指针，时间 20 ms 53.76%，空间 21 MB 35.02%
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size(), even = 0;
        for (int odd = 1; odd < n; odd += 2) {
            if (!(nums[odd] & 1)) {
                while (!(nums[even] & 1)) {
                    even += 2;
                }
                swap(nums[odd], nums[even]);
            }
        }
        return nums;
    }
};