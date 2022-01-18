#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<algorithm>
using namespace std;

// �ҵĽⷨ: dfs+���� 8 ms��8 MB
class Solution {
private:
	vector<vector<string>> ret;
	vector<int> queens;
public:
	void dfs(int n) {
		if (queens.size() == n) {
			vector<string> cur;
			for (int i = 0; i < n; ++i) {
				string temp(n, '.');
				temp[queens[i]] = 'Q';
				cur.emplace_back(temp);
			}
			ret.emplace_back(cur);
			return;
		}

		for (int i = 0; i < n; ++i) {
			bool flag = true;
			for (int j = 0; j < queens.size(); ++j) {
				// ����i�е��»ʺ��queens�еľɻʺ��ڶԽ�����
				// queens.size()��������»ʺ��������i�����»ʺ�������j����ɻʺ�������queen[j]����ɻʺ�����
				// ��������»ʺ���������֮����ɻʺ���������֮����Ȼ��»ʺ���������֮����ɻʺ���������֮�����
				if (queens.size() + i == j + queens[j] || queens.size() - i == j - queens[j]) {
					flag = false;
					break;
				}
			}
			// ���»ʺ������оɻʺ���ͬһ���Ҳ��ڶԽ�����
			if (!count(queens.begin(), queens.end(), i) && flag) {
				queens.emplace_back(i);
				dfs(n);
				queens.pop_back();
			}
		}
	}
	vector<vector<string>> solveNQueens(int n) {
		dfs(n);
		return ret;
	}
};


// �ҵĽⷨ�Ż���ʱ�� 4 ms 92.93%���ռ� 7.2 MB 67.78%
// ��ǰ����ģ��cur������ÿ�ζ����¹��죬���ظ����õ�.size()��queens[j]��int��������
class Solution {
private:
	vector<vector<string>> ret;
	vector<int> queens;
public:
	void dfs(vector<string>& cur, int n) {
		int length = queens.size();
		if (length == n) {
			for (int i = 0; i < n; ++i) {
				cur[i][queens[i]] = 'Q';
			}
			ret.emplace_back(cur);
			for (int i = 0; i < n; ++i) {
				cur[i][queens[i]] = '.';
			}
			return;
		}

		for (int i = 0; i < n; ++i) {
			bool flag = true;
			for (int j = 0; j < length; ++j) {
				int columnj = queens[j];
				if (length + i == j + columnj || length - i == j - columnj) {
					flag = false;
					break;
				}
			}
			if (flag && !count(queens.begin(), queens.end(), i)) {
				queens.emplace_back(i);
				dfs(cur, n);
				queens.pop_back();
			}
		}
	}
	vector<vector<string>> solveNQueens(int n) {
		vector<string> cur(n, string(n, '.'));
		dfs(cur, n);
		return ret;
	}
};

// �ҵĽⷨ�ο��ٽ⣬12 ms��9.7 MB
class Solution {
private:
	vector<vector<string>> ret;
	vector<int> queens;
	unordered_set<int> columns;
	unordered_set<int> sums;
	unordered_set<int> difs;
public:
	void dfs(int n) {
		if (queens.size() == n) {
			vector<string> cur;
			for (int i = 0; i < n; ++i) {
				string temp(n, '.');
				temp[queens[i]] = 'Q';
				cur.emplace_back(temp);
			}
			ret.emplace_back(cur);
			return;
		}

		for (int i = 0; i < n; ++i) {
			if (!columns.count(i) && !sums.count(queens.size() + i) && !difs.count(queens.size() - i)) {
				sums.insert(queens.size() + i);
				difs.insert(queens.size() - i);
				columns.insert(i);
				queens.emplace_back(i);
				dfs(n);
				queens.pop_back();
				columns.erase(i);
				difs.erase(queens.size() - i);
				sums.erase(queens.size() + i);
			}
		}
	}
	vector<vector<string>> solveNQueens(int n) {
		dfs(n);
		return ret;
	}
};

// �ٷ��ⷨ1�����ڼ��ϵĻ��� 16 ms, 9.2 MB
class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		auto solutions = vector<vector<string>>();
		auto queens = vector<int>(n, -1);
		auto columns = unordered_set<int>();
		auto diagonals1 = unordered_set<int>();
		auto diagonals2 = unordered_set<int>();
		backtrack(solutions, queens, n, 0, columns, diagonals1, diagonals2);
		return solutions;
	}

	void backtrack(vector<vector<string>>& solutions, vector<int>& queens, int n, int row, unordered_set<int>& columns, unordered_set<int>& diagonals1, unordered_set<int>& diagonals2) {
		if (row == n) {
			vector<string> board = generateBoard(queens, n);
			solutions.push_back(board);
		}
		for (int i = 0; i < n; ++i) {
			if (columns.find(i) != columns.end()) {
				continue;
			}
			int diagonal1 = row - i;
			if (diagonals1.find(diagonal1) != diagonals1.end()) {
				continue;
			}
			int diagonal2 = row + i;
			if (diagonals2.find(diagonal2) != diagonals2.end()) {
				continue;
			}
			queens[row] = i;
			columns.insert(i);
			diagonals1.insert(diagonal1);
			diagonals2.insert(diagonal2);
			backtrack(solutions, queens, n, row + 1, columns, diagonals1, diagonals2);
			queens[row] = -1;
			columns.erase(i);
			diagonals1.erase(diagonal1);
			diagonals2.erase(diagonal2);
		}
	}

	vector<string> generateBoard(vector<int>& queens, int n) {
		auto board = vector<string>();
		for (int i = 0; i < n; ++i) {
			string row = string(n, '.');
			row[queens[i]] = 'Q';
			board.emplace_back(row);
		}
		return board;
	}
};

// LeetCode 101�ⷨ��ʱ�� 0 ms 100%���ռ� 6.9 MB 98.37%
class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> ans;
		vector<string> board(n, string(n, '.'));
		vector<bool> column(n, false), ldiag(2 * n - 1, false), rdiag(2 * n - 1, false);
		backtracking(ans, board, column, ldiag, rdiag, 0, n);
		return ans;
	}
private:
	void backtracking(vector<vector<string>>& ans, vector<string>& board, vector<bool>& column, vector<bool>& ldiag, vector<bool>& rdiag, int row, int n) {
		if (row == n) {
			ans.emplace_back(board);
			return;
		}
		for (int i = 0; i < n; ++i) {
			if (column[i] || ldiag[n - row + i - 1] || rdiag[row + i]) {
				continue;
			}
			// �޸ĵ�ǰ�ڵ�״̬
			board[row][i] = 'Q';
			// ����һ�����½Ǻ����½Ƕ����Ϊ���ɷ��ûʺ�״̬
			column[i] = ldiag[n - row + i - 1] = rdiag[row + i] = true;
			// �ݹ��ӽڵ�
			backtracking(ans, board, column, ldiag, rdiag, row + 1, n);
			// �ظĵ�ǰ�ڵ�״̬
			board[row][i] = '.';
			column[i] = ldiag[n - row + i - 1] = rdiag[row + i] = false;
		}
	}
};


int main() {
	int n = 4;

	Solution s;
	vector<vector<string>> ret = s.solveNQueens(n);

	for (int i = 0; i < ret.size(); ++i) {
		cout << "[";
		for (int j = 0; j < ret[i].size(); ++j) {
			cout << ret[i][j];
			if (j != ret[i].size() - 1) cout << ",";
			else cout << "]";
			cout << endl;
		}
	}

	system("pause");
	return 0;
}