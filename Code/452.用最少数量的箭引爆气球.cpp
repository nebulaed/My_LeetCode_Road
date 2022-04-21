#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：贪心算法，时间 360 ms，空间 87.7 MB
// 与435题类似，唯一区别是右指针指向区间的左界大于左指针指向区间的右界才说明无重叠，等于也算重叠
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            return lhs[1] < rhs[1];
        });
        int count = 1;
        size_t length = points.size(), left = 0;
        for (size_t right = 1; right < length; ++right) {
            if (points[right][0] > points[left][1]) {
                ++count;
                left = right;
            }
        }
        return count;
    }
};