#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

// LeetCode 101解法：用partial_sum求前缀和，即当前位置和前面所有数字的和。结果数组必为单调递增。
// 时间 68 ms 90.99%，空间 39.1 MB 95.42%
// 每次需要采样时，先在[1,权重和]间随机产生一个数字，然后用二分查找其在前缀和中的位置，模拟加权采样过程。
class Solution {
private:
    vector<int> sums;
public:
    Solution(vector<int>& w) : sums(move(w)) {
        partial_sum(sums.begin(), sums.end(), sums.begin());
    }

    int pickIndex() {
        int pos = (rand() % sums.back()) + 1;
        return lower_bound(sums.begin(), sums.end(), pos) - sums.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */