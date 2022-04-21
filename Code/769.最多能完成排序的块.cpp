#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// LeetCode 101解法：暴力遍历，时间 O(n) 4 ms 17.38%，空间 O(1) 6.9 MB 76.07%
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int blockNum = 0, curMax = 0, n = arr.size();
        for (int i = 0; i < n; ++i) {
            // 记录到当前位置的最大值
            curMax = max(curMax, arr[i]);
            // 若当前最大值大于数组位置，则说明右边一定有小于数组位置的数字，需要将它也加入待排序的
            // 当到当前位置的最大值与当前数组位置相等时，假设为p，即可以成功完成一次分割，并且与上一分割位置q之间的块一定是q+1到p的所有数字
            if (curMax == i) {
                ++blockNum;
            }
        }
        return blockNum;
    }
};