#include<iostream>
#include<vector>

using std::vector;

// 我的解法：记忆化DFS，时间 36 ms 73.23%，空间 17 MB 80.05%
class Solution {
private:
	int direction[5] = { -1, 0 ,1, 0, -1 };
	void dfs(const vector<vector<int>>& heights, size_t x, size_t y, vector<vector<bool>>& flow) {
		flow[x][y] = true;
		for (size_t i = 0; i < 4; ++i) {
			size_t newx = x + direction[i], newy = y + direction[i + 1];
			if (newx >= 0 && newx < heights.size() && newy >= 0 && newy < heights[0].size() && heights[newx][newy] >= heights[x][y] && !flow[newx][newy]) {
				dfs(heights, newx, newy, flow);
			}
		}
	}
public:
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
		if (heights.empty() || heights[0].empty()) return {};
		size_t m = heights.size(), n = heights[0].size();
		vector<vector<bool>> flowToP(m, vector<bool>(n, false));
		vector<vector<bool>> flowToA(m, vector<bool>(n, false));
		for (size_t i = 0; i < n; ++i) {
			dfs(heights, 0, i, flowToP);
			dfs(heights, m - 1, i, flowToA);
		}
		for (size_t i = 0; i < m; ++i) {
			dfs(heights, i, 0, flowToP);
			dfs(heights, i, n - 1, flowToA);
		}
		vector<vector<int>> ret;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (flowToP[i][j] && flowToA[i][j]) {
					ret.emplace_back(vector<int>{i, j});
				}
			}
		}
		return ret;
	}
};