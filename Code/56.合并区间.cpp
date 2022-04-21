#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

// 我的方法 16 ms，15.5 MB
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() < 2) {
            return intervals;
        }
        list<vector<int>> temp;
        for (auto& interval : intervals) {
            auto it = temp.begin();
            while (it != temp.end()) {
                if (max(interval[0], (*it)[0]) <= min(interval[1], (*it)[1])) {
                    interval[0] = min(interval[0], (*it)[0]);
                    interval[1] = max(interval[1], (*it)[1]);
                    it = temp.erase(it);
                }
                else ++it;
            }
            temp.emplace_back(interval);
        }
        vector<vector<int>> ret{ temp.begin(), temp.end() };
        return ret;
    }
};

// 官方解法：排序 时间 O(n log n), 空间 O(log n)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() < 2) {
            return intervals;
        }
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ret;
        for (const auto& interval : intervals) {
            if (ret.empty() || ret.back()[1] < interval[0]) {
                ret.emplace_back(interval);
            }
            else {
                ret.back()[1] = max(ret.back()[1], interval[1]);
            }
        }
        return ret;
    }
};



int main() {

    vector<vector<int>> intervals(3, { 0,0 });

    intervals[0] = { 1,5 };
    intervals[1] = { 7,11 };
    intervals[2] = { 4,8 };

    Solution s;
    vector<vector<int>> ret = s.merge(intervals);


    cout << "[";
    for (int i = 0; i < ret.size(); ++i) {
        cout << "[";
        for (int j = 0; j < ret[i].size(); ++j) {
            cout << ret[i][j];
            if (j != ret[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i != ret.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}