#include<iostream>
#include<vector>
using namespace std;

class Solution {
private:
	// 表示该行是否已出现该数字,true即已出现
	bool lines[9][9];
	// 表示该列是否已出现该数字,true即已出现
	bool columns[9][9];
	// 表示该九宫格是否已出现该数字,true即已出现
	bool blocks[3][3][9];
	bool valid = false;
	vector<pair<int, int>> spaces;

public:
	void dfs(vector<vector<char>>& board, int pos) {
		if (pos == spaces.size()) {
			valid = true;
			return;
		}

		pair<int,int> ret = spaces[pos];
		int i = ret.first, j = ret.second;
		for (int digit = 0; digit < 9 && !valid; ++digit) {
			if (!lines[i][digit] && !columns[j][digit] && !blocks[i / 3][j / 3][digit]) {
				lines[i][digit] = columns[j][digit] = blocks[i / 3][j / 3][digit] = true;
				board[i][j] = '1' + digit;
				dfs(board, pos + 1);
				lines[i][digit] = columns[j][digit] = blocks[i / 3][j / 3][digit] = false;
			}
		}
	}
	void solveSudoku(vector<vector<char>>& board) {
		memset(lines, false, sizeof(lines));
		memset(columns, false, sizeof(columns));
		memset(blocks, false, sizeof(blocks));

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] == '.') {
					spaces.emplace_back(i, j);
				}
				else {
					int digit = board[i][j] - '1';
					lines[i][digit] = columns[j][digit] = blocks[i / 3][j / 3][digit] = true;
				}
			}
		}
		dfs(board, 0);
	}
};

// 官方解法二：位运算优化
class Solution {
private:
	int lines[9];
	int columns[9];
	int blocks[3][3];
	bool valid = false;
	vector<pair<int, int>> spaces;

public:
	void flip(const int& i, const int& j, const int& digit) {
		lines[i] ^= (1 << digit);
		columns[j] ^= (1 << digit);
		blocks[i / 3][j / 3] ^= (1 << digit);
	}

	void dfs(vector<vector<char>>& board, int pos) {
		if (pos == spaces.size()) {
			valid = true;
			return;
		}

		auto [i, j] = spaces[pos];
		int mask = ~(lines[i] | columns[j] | blocks[i / 3][j / 3]) & 0x1ff;
		for (; mask && !valid; mask &= (mask - 1)) {
			int digitMask = mask & (-mask);
			int digit = __builtin_ctz(digitMask);
			flip(i, j, digit);
			board[i][j] = digit + '1';
			dfs(board, pos + 1);
			flip(i, j, digit);
		}
	}

	void solveSudoku(vector<vector<char>>& board) {
		memset(lines, 0, sizeof(lines));
		memset(columns, 0, sizeof(columns));
		memset(blocks, 0, sizeof(blocks));

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] == '.') {
					spaces.emplace_back(i, j);
				}
				else {
					int digit = board[i][j] - '1';
					flip(i, j, digit);
				}
			}
		}

		dfs(board, 0);
	}
};

// 官方解法三：枚举优化
class Solution {
private:
	int lines[9];
	int columns[9];
	int blocks[3][3];
	bool valid = false;
	vector<pair<int, int>> spaces;

public:
	void flip(const int& i, const int& j, const int& digit) {
		lines[i] ^= (1 << digit);
		columns[j] ^= (1 << digit);
		blocks[i / 3][j / 3] ^= (1 << digit);
	}

	void dfs(vector<vector<char>>& board, int pos) {
		if (pos == spaces.size()) {
			valid = true;
			return;
		}

		auto [i, j] = spaces[pos];
		int mask = ~(lines[i] | columns[j] | blocks[i / 3][j / 3]) & 0x1ff;
		for (; mask && !valid; mask &= (mask - 1)) {
			int digitMask = mask & (-mask);
			int digit = __builtin_ctz(digitMask);
			flip(i, j, digit);
			board[i][j] = digit + '1';
			dfs(board, pos + 1);
			flip(i, j, digit);
		}
	}

	void solveSudoku(vector<vector<char>>& board) {
		memset(lines, 0, sizeof(lines));
		memset(columns, 0, sizeof(columns));
		memset(blocks, 0, sizeof(blocks));

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] != '.') {
					int digit = board[i][j] - '1';
					flip(i, j, digit);
				}
			}
		}

		while (true) {
			int modified = false;
			for (int i = 0; i < 9; ++i) {
				for (int j = 0; j < 9; ++j) {
					if (board[i][j] == '.') {
						int mask = ~(lines[i] | columns[j] | blocks[i / 3][j / 3]) & 0x1ff;
						if (!(mask & (mask - 1))) {
							int digit = __builtin_ctz(mask);
							flip(i, j, digit);
							board[i][j] = digit + '1';
							modified = true;
						}
					}
				}
			}
			if (!modified) {
				break;
			}
		}
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] == '.') {
					spaces.emplace_back(i, j);
				}
			}
		}
		dfs(board, 0);
	}
};