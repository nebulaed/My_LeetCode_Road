#include<iostream>
#include<vector>
using namespace std;

// 我的解法：双指针，时间O(n) 4 ms，空间O(1) 9.3 MB
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int lrSum = numbers[left] + numbers[right];
            if (lrSum > target) {
                --right;
            }
            else if (lrSum < target) {
                ++left;
            }
            else return { left + 1, right + 1 };
        }
        return { left + 1, right + 1 };
    }
};