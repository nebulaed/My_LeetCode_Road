#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

// 官方答案一：组合数学，时间复杂度O(m) 0 ms，空间复杂度O(1) 5.8 MB
class Solution {
public:
	int uniquePaths(int m, int n) {
		long long num = 1, larger = max(m, n), smaller = min(m, n);
		for (long long i = larger, j = 1; j < smaller; ++i, ++j) {
			num = num * i / j;
		}
		return num;
	}
};

// 官方答案二：动态规划，时间复杂度O(mn) 0 ms，空间复杂度O(mn) 6.4 MB
class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n, 1));
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};

// 官方答案二：动态规划评论区优化版，时间复杂度O(mn) 0 ms，空间复杂度O(n) 5.9 MB
class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<int> dp(n, 1);
		for (int i = 1; i < m; i++){
			for (int j = 1; j < n; j++){
				dp[j] += dp[j - 1];
			}
		}
		return dp[n - 1];
	}
};

int main() {
	int m = 23, n = 12;
	
	Solution s;
	int ret = s.uniquePaths(m, n);

	cout << ret << endl;

	system("pause");
	return 0;
}