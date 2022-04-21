#include<iostream>
#include<queue>
#include<vector>
#include<memory>

using namespace std;

// LeetCode 101解法：时间 24 ms 99.42%，空间 18.1 MB 86.90%
class Solution {
private:
    int directions[5] = { -1, 0, 1, 0, -1 };

    void dfs(queue<pair<int, int>>& points, vector<vector<int>>& grid, int m, int n, int i, int j) {
        if (grid[i][j] == 0) {
            points.emplace(i, j);
            return;
        }
        grid[i][j] = 2;
        for (int k = 0; k < 4; ++k) {
            int newi = i + directions[k], newj = j + directions[k + 1];
            if (newi >= 0 && newi < m && newj >= 0 && newj < n) {
                if (grid[newi][newj] != 2) {
                    dfs(points, grid, m, n, newi, newj);
                }
            }
        }
    }
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> points;
        // dfs寻找从某一个岛屿出发的所有第一个点，并把出发所在岛屿的1全部赋值为2
        bool flipped = false;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dfs(points, grid, m, n, i, j);
                    flipped = true;
                    break;
                }
            }
            if (flipped) break;
        }
        // BFS寻找第二个岛屿，并把过程中经过的0赋值为2
        for (int level = 1; !points.empty(); ++level) {
            // 当前队列长度，相当于从第一座岛屿出发后的某一层0，从这些0出发找另一座岛屿的1，走完这一层还没发现周围有1，那么level自加1继续查找
            int n_points = points.size();
            while (n_points--) {
                auto [x, y] = points.front();
                points.pop();
                for (int i = 0; i < 4; ++i) {
                    int newx = x + directions[i], newy = y + directions[i + 1];
                    if (newx >= 0 && newx < m && newy >= 0 && newy < n) {
                        if (grid[newx][newy] == 2) continue;
                        if (grid[newx][newy] == 1) {
                            return level;
                        }
                        points.emplace(newx, newy);
                        grid[newx][newy] = 2;
                    }
                }
            }
        }
        return 0;
    }
};