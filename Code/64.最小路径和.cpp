#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
//#define INFINITY 65535
//
//void printMatrix(const vector<vector<int>>& matrix) {
//	for (int i = 0; i < matrix.size(); ++i) {
//		cout << "[";
//		for (int j = 0; j < matrix[i].size(); ++j) {
//			if (matrix[i][j] < INFINITY) cout << matrix[i][j];
//			else cout << "∞";
//			if (j != matrix[i].size() - 1) cout << ",";
//		}
//		cout << "]";
//		if (i != matrix.size() - 1) cout << "," << endl;
//	}
//	cout << endl;
//}
// Floyd算法原用法
//class Solution {
//public:
//	int minPathSum(vector<vector<int>>& grid) {
//		int m = grid.size();
//		int n = grid[0].size();
//        int vexNum = m * n;
//		vector<vector<int>> MGraph(vexNum, vector<int>(vexNum, INFINITY));
//		for (int i = 0; i < vexNum; ++i) {
//			for (int j = i; j < vexNum; ++j) {
//				if (j == i) MGraph[i][j] = 0;
//				if ((j - i) == n || ((j - i) == 1 && j % n != 0)) MGraph[i][j] = MGraph[j][i] = grid[j / 3][j % 3];
//			}
//		}
//		vector<vector<int>> Patharc(vexNum, vector<int>(vexNum));
//		vector<vector<int>> ShortPathTable(vexNum, vector<int>(vexNum));
//
//		for (int v = 0; v < vexNum; ++v) {
//			for (int w = 0; w < vexNum; ++w) {
//				ShortPathTable[v][w] = MGraph[v][w];
//				Patharc[v][w] = w;
//			}
//		}
//		for (int k = 0; k < vexNum; ++k) {
//			for (int v = 0; v < vexNum; ++v) {
//				for (int w = 0; w < vexNum; ++w) {
//					if (ShortPathTable[v][w] > ShortPathTable[v][k] + ShortPathTable[k][w]) {
//						ShortPathTable[v][w] = ShortPathTable[v][k] + ShortPathTable[k][w];
//						Patharc[v][w] = Patharc[v][k];
//					}
//				}
//			}
//		}
//		return grid[0][0] + ShortPathTable[0][m * n - 1];
//	}
//};


// 我的解法：Floyd算法，超时
//class Solution {
//public:
//	int minPathSum(vector<vector<int>>& grid) {
//		int m = grid.size();
//		int n = grid[0].size();
//		int vexNum = m * n;
//		vector<vector<int>> MGraph(vexNum, vector<int>(vexNum, INFINITY));
//		for (int i = 0; i < vexNum; ++i) {
//			for (int j = i; j < vexNum; ++j) {
//				if (j == i) MGraph[i][j] = 0;
//				if ((j - i) == n || ((j - i) == 1 && j % n != 0)) MGraph[i][j] = grid[j / n][j % n];
//			}
//		}
//
//		for (int k = 0; k < vexNum; ++k) {
//			for (int v = 0; v < vexNum; ++v) {
//				for (int w = 0; w < vexNum; ++w) {
//					if (MGraph[v][w] > MGraph[v][k] + MGraph[k][w]) {
//						MGraph[v][w] = MGraph[v][k] + MGraph[k][w];
//					}
//				}
//			}
//		}
//		return grid[0][0] + MGraph[0][m * n - 1];
//	}
//};

// 我的解法二：DFS+回溯，超时
class Solution {
private:
    int minPath = INT_MAX;
public:
    void dfs(int path, const pair<int, int>& pos, const vector<vector<int>>& grid) {
        if (pos.first == grid.size() - 1 && pos.second == grid[0].size() - 1) {
            minPath = min(minPath, path);
        }
        if (pos.first != grid.size() - 1) {
            dfs(path + grid[pos.first + 1][pos.second], pair<int, int>(pos.first + 1, pos.second), grid);
        }
        if (pos.second != grid[0].size() - 1) {
            dfs(path + grid[pos.first][pos.second + 1], pair<int, int>(pos.first, pos.second + 1), grid);
        }
    }

    int minPathSum(vector<vector<int>>& grid) {
        dfs(grid[0][0], pair<int, int>(0, 0), grid);
        return minPath;
    }
};

// 我的解法三：动态规划，12 ms，9.9 MB
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, grid[0][0]));
        for (int i = 1; i < n; ++i) {
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};

// 我的解法三动态规划继续优化，4 ms，9.5 MB
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int* dp = new int[n];
        dp[0] = grid[0][0];
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1] + grid[0][i];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j != 0) {
                    dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
                }
                else {
                    dp[j] += grid[i][j];
                }
            }
        }
        return dp[n - 1];
    }
};

int main() {
    //vector<vector<int>> grid = {{1, 3, 1},{1, 5, 1},{4, 2, 1}};
    vector<vector<int>> grid = { {1, 2}, {1, 1} };

    Solution s;
    int ret = s.minPathSum(grid);

    cout << ret << endl;

    return 0;
}