#include<iostream>
#include<vector>
using namespace std;

// 我的解法一：DFS+回溯，超时
class Solution {
private:
	bool dfs(const vector<vector<int>>& matrix, vector<vector<int>>& visited, int x, int y, int target) {
		if (matrix[x][y] == target) return true;
		else if (matrix[x][y] > target) return false;
		int directions[2][2] = { {0, 1}, {1, 0} };
		bool ret = false;
		for (const auto& dir : directions) {
			int newx = x + dir[0], newy = y + dir[1];
			if (newx < matrix.size() && newy < matrix[0].size()) {
				if (!visited[newx][newy]) {
					if (dfs(matrix, visited, newx, newy, target)) {
						ret = true;
						break;
					}
				}
			}
		}
		return ret;
	}
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		size_t height = matrix.size(), width = matrix[0].size();
		vector<vector<int>> visited(height, vector<int>(width));
		bool ret = dfs(matrix, visited, 0, 0, target);
		return ret;
	}
};

// 官方解法一：暴力遍历，时间 O(mn) 688 ms，空间 O(1) 14.4 MB
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		for (const auto& row : matrix) {
			if (row[0] > target) break;
			for (int element : row) {
				if (element == target) {
					return true;
				}
			}
		}
		return false;
	}
};

// 按官方解法二思路写的程序：对每行做二分查找，时间O(m log n) 168 ms，空间O(1) 14.6 MB
class Solution {
private:
	bool binarySearch(const vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (target < nums[mid]) {
				high = mid - 1;
			}
			else if (target > nums[mid]) {
				low = mid + 1;
			}
			else return true;
		}
		return false;
	}
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		for (const auto& row : matrix) {
			if (row[0] > target) break;
			if (binarySearch(row, target)) {
				return true;
			}
		}
		return false;
	}
};

// 官方解法三：Z字形查找，时间O(m+n) 64 ms，空间O(1) 14.6 MB
// 从矩阵右上角(0, n-1)开始搜索，我们要搜索的范围是以矩阵左下角(n-1, 0)为左下角，以(x,y)为右上角的范围
// 若matrix[x,y] == target，搜索完成
// 若matrix[x,y] > target，说明第y列的元素都大于target，可全部忽略，故--y
// 若matrix[x,y] < target，说明第x行的元素都小于target，可全部忽略，故++x
// 若直到x和y超出输入矩阵边界，说明矩阵中不存在target
class Solution {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int height = matrix.size(), width = matrix[0].size();
		int x = 0, y = width - 1;
		while (x < height && y >= 0) {
			int num = matrix[x][y];
			if (num == target) {
				return true;
			}
			if (num > target) {
				--y;
			}
			else {
				++x;
			}
		}
		return false;
	}
};