#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

// 我的解法一：使用柱状图的优化暴力方法，24 ms，11.6 MB
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size();
		if (m == 0) return 0;
		int n = matrix[0].size();

		vector<vector<int>> left(m, vector<int>(n, 0));

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
				}
			}
		}

		int ret = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '0') {
					continue;
				}
				int width = left[i][j];
				int area = 1;
				for (int k = i - 1; k >= 0; --k) {
					width = min(width, left[k][j]);
					int height = i - k + 1;
					if (width >= height) {
						area = max(area, height * height);
					}
					else break;
				}
				ret = max(ret, area);
			}
		}
		return ret;
	}
};

// 我的解法二：单调栈
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size();
		if (m == 0) return 0;
		int n = matrix[0].size();

		vector<vector<int>> left(m, vector<int>(n, 0));

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
				}
			}
		}

		int ret = 0;
		for (int j = 0; j < n; ++j) {
			vector<int> up(m, 0), down(m, 0);
			stack<int> stk;
			for (int i = 0; i < m; ++i) {
				while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
					stk.pop();
				}
				up[i] = stk.empty() ? -1 : stk.top();
				stk.emplace(i);
			}
			stk = stack<int>();
			for (int i = m - 1; i >= 0; --i) {
				while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
					stk.pop();
				}
				down[i] = stk.empty() ? m : stk.top();
				stk.emplace(i);
			}
			for (int i = 0; i < m; ++i) {
				int sideLength = min(down[i] - up[i] - 1, left[i][j]);
				int area = sideLength * sideLength;
				ret = max(ret, area);
			}
		}
		return ret;
	}
};

// 官方题解一：暴力法，时间 O(mn min(m,n)^2) 52 ms，空间 O(1) 10.8 MB
// 1.遍历矩阵中的每个元素，每次遇到1，则将该元素作为正方形的左上角
// 2.确定正方形的左上角后，根据左上角所在的行和列计算可能的最大正方形的边长(正方形的范围不能超过矩阵的行数和列数)，在该边长范围内寻找只包含1的最大正方形
// 3.每次在下方新增一行在右方新增一列，判断新增的行和列是否满足所有元素都是1
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int rows = matrix.size(), columns = matrix[0].size();
		if (rows == 0 || columns == 0) return 0;
		int maxSide = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] == '0') {
					continue;
				}
				// 遇到一个'1'作为正方形的左上角
				maxSide = max(maxSide, 1);
				// 计算可能的最大正方形边长
				int currentMaxSide = min(rows - i, columns - j);
				for (int k = 1; k < currentMaxSide; ++k) {
					// 判断新增的一行一列是否均为1
					bool flag = true;
					if (matrix[i + k][j + k] == '0') {
						break;
					}
					for (int m = 0; m < k; ++m) {
						if (matrix[i + k][j + m] == '0' || matrix[i + m][j + k] == '0') {
							flag = false;
							break;
						}
					}
					if (flag) {
						maxSide = max(maxSide, k + 1);
					}
					else {
						break;
					}
				}
			}
		}
		int maxSquare = maxSide * maxSide;
		return maxSquare;
	}
};

// 官方解法二：动态规划，时间O(mn) 24 ms，空间O(mn) 11.6 MB
// 以dp(i,j)表示以(i,j)为右下角，且只包含1的正方形的边长最大值。若能计算出所有dp(i,j)的值，那么其中最大值的平方即为结果。
// 对每个(i,j)，检查在矩阵中该为止的值：
// 1.若该位置是0，则dp(i,j)=0
// 2.若该位置是1，则dp(i,j)的值由其上方、左方和左上方的三个相邻位置的dp值决定。具体而言，当前为止的元素值等于三个相邻为止的元素中的最小值+1
// 即 dp(i,j) = min(dp(i-1,j),dp(i-1,j-1),dp(i,j-1)) + 1
// 具体状态转移方程原因见1277题官方题解。
// 最后还要考虑边界条件。如果i和j中至少一个为0，则以(i,j)为右下角的最大正方形的边长只能是1。
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size(), n = matrix[0].size();
		vector<vector<int>> dp(m, vector<int>(n, 0));
		int maxSide = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '0') {
					continue;
				}
				if (i == 0 || j == 0) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = min({ dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1] }) + 1;
				}
				maxSide = max(maxSide, dp[i][j]);
			}
		}
		return maxSide * maxSide;
	}
};