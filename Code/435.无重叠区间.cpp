#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 按照区间的右界从小到大进行排序
        sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            return lhs[1] < rhs[1];
        });
        // 初始化区间总数为totalNum，要保留的区间数量为1
        int totalNum = intervals.size(), count = 1;
        // 初始化左指针为0
        size_t left = 0;
        for (size_t right = 1; right < totalNum; ++right) {
            // 若右指针指向区间的左界大于等于左指针指向区间的右界，说明这两个区间无重叠，right指针指向的区间要保留下来，保留区间数量count加一
            // 同时由于右指针的区间保留，左指针更新为右指针指向区间
            if (intervals[right][0] >= intervals[left][1]) {
                ++count;
                left = right;
            }
        }
        // 总数减去保留区间数量即为移除区间最小数量
        return totalNum - count;
    }
};