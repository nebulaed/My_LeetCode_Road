#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨһ��DFS+���ݣ���ʱ
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

// �ٷ��ⷨһ������������ʱ�� O(mn) 688 ms���ռ� O(1) 14.4 MB
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

// ���ٷ��ⷨ��˼·д�ĳ��򣺶�ÿ�������ֲ��ң�ʱ��O(m log n) 168 ms���ռ�O(1) 14.6 MB
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

// �ٷ��ⷨ����Z���β��ң�ʱ��O(m+n) 64 ms���ռ�O(1) 14.6 MB
// �Ӿ������Ͻ�(0, n-1)��ʼ����������Ҫ�����ķ�Χ���Ծ������½�(n-1, 0)Ϊ���½ǣ���(x,y)Ϊ���Ͻǵķ�Χ
// ��matrix[x,y] == target���������
// ��matrix[x,y] > target��˵����y�е�Ԫ�ض�����target����ȫ�����ԣ���--y
// ��matrix[x,y] < target��˵����x�е�Ԫ�ض�С��target����ȫ�����ԣ���++x
// ��ֱ��x��y�����������߽磬˵�������в�����target
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