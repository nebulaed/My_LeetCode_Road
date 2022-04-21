#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一：贪心算法，时间O(n) 20 ms，空间 O(1) 17.3 MB
class Solution {
public:
    int candy(vector<int>& ratings) {
        size_t length = ratings.size();
        vector<int> candys(length, 1);
        for (size_t i = 1; i < length; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candys[i] = candys[i - 1] + 1;
            }
        }
        int candySum = candys[length - 1];
        for (size_t i = length - 2; i != -1; --i) {
            if (ratings[i] > ratings[i + 1] && candys[i] <= candys[i + 1]) {
                candys[i] = candys[i + 1] + 1;
            }
            candySum += candys[i];
        }
        return candySum;
    }
};

// LeetCode 101解法：贪心算法，时间O(n) 16 ms，空间 O(1) 17.3 MB
class Solution {
public:
    int candy(vector<int>& ratings) {
        size_t length = ratings.size();
        if (length < 2) return length;
        vector<int> candys(length, 1);
        for (size_t i = 1; i < length; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candys[i] = candys[i - 1] + 1;
            }
        }
        int candySum = candys[length - 1];
        for (size_t i = length - 1; i > 0; --i) {
            if (ratings[i - 1] > ratings[i]) {
                candys[i - 1] = max(candys[i - 1], candys[i] + 1);
            }
            candySum += candys[i];
        }
        return candySum;
    }
};