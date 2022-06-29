#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：时间 O(mn) 8 ms 95.92%，空间 O(m+n) 12.9 MB 49.06%
class Solution {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        size_t m = matrix.size(), n = matrix[0].size();
        vector<bool> lineSpread(m, false), columnSpread(n, false);
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (!matrix[i][j]) {
                    lineSpread[i] = columnSpread[j] = true;
                }
            }
        }
        for (size_t i = 0; i < m; ++i) {
            if (lineSpread[i]) {
                fill(matrix[i].begin(), matrix[i].end(), 0);
            }
        }
        for (size_t j = 0; j < n; ++j) {
            if (columnSpread[j]) {
                for (auto &line: matrix) {
                    line[j] = 0;
                }
            }
        }
    }
};

// 官方解法二：使用两个标记变量，时间 O(mn) 12 ms 75.66%，空间 O(1) 12.8 MB 84.81%
class Solution {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        size_t m = matrix.size(), n = matrix[0].size();
        bool col0Exist0 = false, row0Exist0 = false;
        for (size_t i = 0; i < m; ++i) {
            if (!matrix[i][0]) {
                col0Exist0 = true;
                break;
            }
        }
        for (size_t j = 0; j < n; ++j) {
            if (!matrix[0][j]) {
                row0Exist0 = true;
                break;
            }
        }
        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                if (!matrix[i][j]) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        for (size_t i = 1; i < m; ++i) {
            if (!matrix[i][0]) {
                fill(matrix[i].begin(), matrix[i].end(), 0);
            }
        }
        for (size_t j = 1; j < n; ++j) {
            if (!matrix[0][j]) {
                for (auto &row: matrix) {
                    row[j] = 0;
                }
            }
        }
        if (col0Exist0) {
            for (auto &row: matrix) {
                row[0] = 0;
            }
        }
        if (row0Exist0) {
            fill(matrix[0].begin(), matrix[0].end(), 0);
        }
    }
};


// 官方解法三：使用一个标记变量，时间 O(mn) 16 ms 34.30%，空间 O(1) 12.8 MB 81.32%
class Solution {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        size_t m = matrix.size(), n = matrix[0].size();
        bool col0Exist0 = false;
        for (size_t i = 0; i < m; ++i) {
            if (!matrix[i][0]) {
                col0Exist0 = true;
            }
            for (size_t j = 1; j < n; ++j) {
                if (!matrix[i][j]) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }
        for (size_t i = m - 1; i != -1; --i) {
            for (size_t j = 1; j < n; ++j) {
                if (!matrix[i][0] || !matrix[0][j]) {
                    matrix[i][j] = 0;
                }
            }
            if (col0Exist0) {
                matrix[i][0] = 0;
            }
        }
    }
};