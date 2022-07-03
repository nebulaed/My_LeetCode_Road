#include<vector>
using namespace std;

// 我的解法：直接计算，时间 0 ms 100%，空间 6.4 MB 51.77%
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);
        for (int i = 1; i <= numRows; ++i) {
            auto& curr = ret[i - 1];
            curr.emplace_back(1);
            for (int j = 1; j < i - 1; ++j) {
                curr.emplace_back(ret[i - 2][j - 1] + ret[i - 2][j]);
            }
            if (i != 1) curr.emplace_back(1);
        }
        return ret;
    }
};

// 官方解法：resize避免不断扩容，时间 O(numRows^2) 0 ms 100%，空间 O(1) 6.2 MB 94.11%
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);
        for (int i = 0; i < numRows; ++i) {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
            }
        }
        return ret;
    }
};