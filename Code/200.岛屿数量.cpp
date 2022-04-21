#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// 我的解法：dfs+回溯，时间O(MN) 24ms，空间O(MN) 11.9 MB
class Solution {
private:
    int num;
public:
    Solution() : num(0) {}
    void dfs(vector<vector<char>>& grid, size_t x, size_t y) {
        if (grid[x][y] == '0') return;
        if (grid[x][y] == '1') grid[x][y] = '0';
        if (x >= 1) dfs(grid, x - 1, y);
        if (x + 1 < grid.size()) dfs(grid, x + 1, y);
        if (y >= 1) dfs(grid, x, y - 1);
        if (y + 1 < grid[0].size()) dfs(grid, x, y + 1);
    }
    int numIslands(vector<vector<char>>& grid) {
        for (size_t i = 0; i < grid.size(); ++i) {
            for (size_t j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == '1') {
                    ++num;
                    dfs(grid, i, j);
                }
            }
        }
        return num;
    }
};

// 官方解法二：BFS，时间O(MN) 32 ms，空间O(min(M,N)) 17.7 MB
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    grid[r][c] == '0';
                    queue<pair<int, int>> neighbors;
                    neighbors.emplace(r, c);
                    while (!neighbors.empty()) {
                        auto rc = neighbors.front();
                        neighbors.pop();
                        int row = rc.first, col = rc.second;
                        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                            neighbors.emplace(row - 1, col);
                            grid[row - 1][col] = '0';
                        }
                        if (row + 1 < nr && grid[row + 1][col] == '1') {
                            neighbors.emplace(row + 1, col);
                            grid[row + 1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                            neighbors.emplace( row, col - 1 );
                            grid[row][col - 1] = '0';
                        }
                        if (col + 1 < nc && grid[row][col + 1] == '1') {
                            neighbors.emplace( row, col + 1 );
                            grid[row][col + 1] = '0';
                        }
                    }
                }
            }
        }
        return num_islands;
    }
};

// 官方解法三：并查集，在需要不改动原输入的情况下使用，时间O(MN×α(MN)) 32 ms，空间O(MN) 15.3 MB
class UnionFind {
public:
    UnionFind(vector<vector<char>>& grid): count(0) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    parent.emplace_back(i * n + j);
                    ++count;
                }
                else {
                    parent.emplace_back(-1);
                }
                rank.emplace_back(0);
            }
        }
    }

    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                swap(rootx, rooty);
            }
            parent[rooty] = rootx;
            if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            --count;
        }
    }

    int getCount() const {
        return count;
    }
private:
    vector<int> parent;
    vector<int> rank;
    int count;
};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (!nr) return 0;
        int nc = grid[0].size();

        UnionFind uf(grid);
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    grid[r][c] = '0';
                    if (r - 1 >= 0 && grid[r - 1][c] == '1') uf.unite(r * nc + c, (r - 1) * nc + c);
                    if (r + 1 < nr && grid[r + 1][c] == '1') uf.unite(r * nc + c, (r + 1) * nc + c);
                    if (c - 1 >= 0 && grid[r][c - 1] == '1') uf.unite(r * nc + c, r * nc + c - 1);
                    if (c + 1 < nc && grid[r][c + 1] == '1') uf.unite(r * nc + c, r * nc + c + 1);
                }
            }
        }
        return uf.getCount();
    }
};