#include<iostream>
#include<queue>
#include<vector>
#include<xmemory>

using std::vector;
using std::queue;
using std::pair;

// LeetCode 101�ⷨ��ʱ�� 24 ms 99.42%���ռ� 18.1 MB 86.90%
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
		// dfsѰ�Ҵ�ĳһ��������������е�һ���㣬���ѳ������ڵ����1ȫ����ֵΪ2
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
		// BFSѰ�ҵڶ������죬���ѹ����о�����0��ֵΪ2
		for (int level = 1; !points.empty(); ++level) {
			// ��ǰ���г��ȣ��൱�ڴӵ�һ������������ĳһ��0������Щ0��������һ�������1��������һ�㻹û������Χ��1����ôlevel�Լ�1��������
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