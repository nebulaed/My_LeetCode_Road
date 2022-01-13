#include<iostream>
#include<vector>

using std::vector;

// 我的解法：时间 16 ms 73%，空间 13.3 MB 78%
class Solution {
private:
	void dfs(const vector<vector<int>>& isConnected, size_t i, bool visited[]) {
		visited[i] = true;
		for (size_t j = 0; j < isConnected.size(); ++j) {
			if (isConnected[i][j] == 1 && !visited[j]) {
				dfs(isConnected, j, visited);
			}
		}
	}

public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		size_t n = isConnected.size();
		int count = 0;
		bool* visited = new bool[n]();
		for (size_t i = 0; i < n; ++i) {
			if (!visited[i]) {
				dfs(isConnected, i, visited);
				++count;
			}
		}
		return count;
	}
};

// LeetCode 101解法：记忆化DFS，时间 16 ms 92.73%，空间 13.3 MB 82.27%
class Solution {
private:
	void dfs(const vector<vector<int>>& isConnected, size_t i, vector<bool>& visited) {
		visited[i] = true;
		for (size_t j = 0; j < isConnected.size(); ++j) {
			if (isConnected[i][j] == 1 && !visited[j]) {
				dfs(isConnected, j, visited);
			}
		}
	}

public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		size_t n = isConnected.size();
		int count = 0;
		vector<bool> visited(n, false);
		for (size_t i = 0; i < n; ++i) {
			if (!visited[i]) {
				dfs(isConnected, i, visited);
				++count;
			}
		}
		return count;
	}
};