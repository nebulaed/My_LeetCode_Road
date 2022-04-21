#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

// 我的解法：哈希表，时间 O(n^2) 8 ms 89.47%，空间 O(n) 8.1 MB 78.88%
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int maxPointNum = 1;
        unordered_map<double, int> slopes;
        for (int i = 0; i < points.size(); ++i) {
            int infSlope = 0;
            for (int j = i + 1; j < points.size(); ++j) {
                const auto& point1 = points[i];
                const auto& point2 = points[j];
                double x_dif = point2[0] - point1[0];
                if (x_dif != 0) {
                    double y_dif = point2[1] - point1[1];
                    double slope = y_dif / x_dif;
                    ++slopes[slope];
                }
                else {
                    ++infSlope;
                }
            }
            int curPointNum = infSlope;
            for (const auto& [_, pointNum] : slopes) {
                curPointNum = max(curPointNum, pointNum);
            }
            maxPointNum = max(maxPointNum, curPointNum + 1);
            slopes.clear();
        }
        return maxPointNum;
    }
};

// LeetCode 101解法：哈希表，时间 8 ms 89.47%，空间 8.2 MB 74.54%
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        unordered_map<double, int> hash;
        int maxCount = 0, same = 1, same_y = 1;
        for (int i = 0; i < points.size(); ++i) {
            same = 1, same_y = 1;
            for (int j = i + 1; j < points.size(); ++j) {
                if (points[i][1] == points[j][1]) {
                    ++same_y;
                    if (points[i][0] == points[j][0]) {
                        ++same;
                    }
                }
                else {
                    double dx = points[i][0] - points[j][0], dy = points[i][1] - points[j][1];
                    ++hash[dx / dy];
                }
            }
            maxCount = max(maxCount, same_y);
            for (auto item : hash) {
                maxCount = max(maxCount, same + item.second);
            }
            hash.clear();
        }
        return maxCount;
    }
};