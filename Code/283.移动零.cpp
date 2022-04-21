#include<iostream>
#include<vector>
using namespace std;

// 我的解法一：遍历将检查到的0删去，再尾插相同数量的0，时间 92 ms，空间 18.8 MB
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int count = 0;
        for (auto it = nums.begin(); it != nums.end();) {
            if (*it != 0) {
                ++it;
                continue;
            }
            it = nums.erase(it);
            ++count;
        }
        for (int i = 0; i < count; ++i) {
            nums.emplace_back(0);
        }
    }
};

// 我的解法二：双指针法，将非0数逐个交换到前面，时间O(n) 20 ms，空间O(1) 18.6 MB
// ptr0指向是0的数，ptr1指向非零数
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t ptr0 = 0, ptr1 = 0, length = nums.size();
        while (ptr1 < length && ptr0 < length) {
            while (ptr0 < length && nums[ptr0] != 0) {
                ++ptr0;
            }
            while (ptr1 < length && nums[ptr1] == 0) {
                ++ptr1;
            }
            if (ptr1 < length && ptr0 < length && ptr1 > ptr0) {
                swap(nums[ptr0], nums[ptr1]);
                ++ptr0;
            }
            ++ptr1;
        }
    }
};

// 官方解法一：双指针，时间O(n) 20 ms，空间O(1) 18.7 MB
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t length = nums.size(), left = 0, right = 0;
        while (right < length) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
                ++left;
            }
            ++right;
        }
    }
};