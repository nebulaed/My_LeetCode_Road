#include<iostream>
#include<vector>
using namespace std;

class Solution {
private:
	vector<int> queens;
	int num = 0;
public:
	void dfs(int n) {
		if (queens.size() == n) {
			++num;
			return;
		}

		for (int i = 0; i < n; ++i) {
			bool flag = true;
			for (int j = 0; j < queens.size(); ++j) {
				if (queens.size() + i == j + queens[j] || queens.size() - i == j - queens[j]) {
					flag = false;
					break;
				}
			}
			if (!count(queens.begin(), queens.end(), i) && flag) {
				queens.emplace_back(i);
				dfs(n);
				queens.pop_back();
			}
		}
	}
public:
	int totalNQueens(int n) {
		dfs(n);
		return num;
	}
};