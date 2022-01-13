#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

using std::vector;
using std::stack;
using std::array;
using std::max;
using std::pair;

// 我的解法：DFS记忆化搜索，时间 12 ms 93.03%，空间 22.6 MB 65.05%
class Solution {
private:
	int maxArea = 0;
	void dfs(vector<vector<int>>& grid, size_t x, size_t y, int& curArea) {
		if (grid[x][y] == 0) return;
		else {
			maxArea = max(maxArea, ++curArea);
			grid[x][y] = 0;
		}
		if (x > 0) dfs(grid, x - 1, y, curArea);
		if (x < grid.size() - 1) dfs(grid, x + 1, y, curArea);
		if (y > 0) dfs(grid, x, y - 1, curArea);
		if (y < grid[0].size() - 1) dfs(grid, x, y + 1, curArea);
	}
public:
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		size_t height = grid.size(), width = grid[0].size();
		for (size_t i = 0; i < height; ++i) {
			for (size_t j = 0; j < width; ++j) {
				if (grid[i][j] == 1) {
					int curArea = 0;
					dfs(grid, i, j, curArea);
				}
			}
		}
		return maxArea;
	}
};

// LeetCode 101解法1：递归，时间 20 ms 50.20%，空间 22.6 MB 59.86%
class Solution {
private:
	int direction[5] = { -1, 0, 1, 0, -1 };
	int maxArea = 0;
	void dfs(vector<vector<int>>& grid, size_t x, size_t y, int& curArea) {
		if (grid[x][y] == 0) return;
		else {
			maxArea = max(maxArea, ++curArea);
			grid[x][y] = 0;
		}
		for (size_t i = 0; i < 4; ++i) {
			size_t newx = x + direction[i], newy = y + direction[i + 1];
			if (newx >= 0 && newx < grid.size() && newy >= 0 && newy < grid[0].size()) {
				dfs(grid, newx, newy, curArea);
			}
		}
	}
public:
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		size_t height = grid.size(), width = grid[0].size();
		for (size_t i = 0; i < height; ++i) {
			for (size_t j = 0; j < width; ++j) {
				if (grid[i][j] == 1) {
					int curArea = 0;
					dfs(grid, i, j, curArea);
				}
			}
		}
		return maxArea;
	}
};

// LeetCode 101解法2：栈+DFS，时间 20 ms，空间 26 MB
class Solution {
private:
	int direction[5] = { -1, 0, 1, 0, -1 };
public:
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		int height = grid.size(), width = grid[0].size(), localArea = 0, maxArea = 0;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (grid[i][j] == 1) {
					localArea = 1;
					grid[i][j] = 0;
					stack<pair<int,int>> island;
					island.emplace(i, j);
					while (!island.empty()) {
						// C++17引入的结构化绑定声明(Structured binding declaration)
						auto [x, y] = island.top();
						island.pop();
						for (size_t k = 0; k < 4; ++k) {
							int newx = x + direction[k], newy = y + direction[k + 1];
							if (newx >= 0 && newx < height && newy >= 0 && newy < width && grid[newx][newy] == 1) {
								grid[newx][newy] = 0;
								++localArea;
								island.emplace(newx, newy);
							}
						}
					}
					maxArea = max(maxArea, localArea);
				}
			}
		}
		return maxArea;
	}
};