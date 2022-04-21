#include<iostream>
#include<vector>

using namespace std;

// 我的解法：DFS+标记数组，时间 12 ms 71.64%，空间 9.8 MB 56.34%
class Solution {
private:
    int directions[5] = { -1, 0, 1, 0, -1 };
    void dfs(const vector<vector<char>>& board, int i, int j, vector<vector<bool>>& non_surrounded) {
        if (board[i][j] == 'X' || non_surrounded[i][j]) return;
        non_surrounded[i][j] = true;
        for (int k = 0; k < 4; ++k) {
            int newi = i + directions[k], newj = j + directions[k + 1];
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
                if (board[newi][newj] == 'O') {
                    dfs(board, newi, newj, non_surrounded);
                }
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        int height = board.size(), width = board[0].size();
        vector<vector<bool>> non_surrounded(height, vector<bool>(width, false));
        for (int i = 0; i < height; ++i) {
            dfs(board, i, 0, non_surrounded);
            dfs(board, i, width - 1, non_surrounded);
        }
        for (int i = 0; i < width; ++i) {
            dfs(board, 0, i, non_surrounded);
            dfs(board, height - 1, i, non_surrounded);
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (board[i][j] == 'O') {
                    if (!non_surrounded[i][j]) {
                        board[i][j] = 'X';
                    }
                }
            }
        }
    }
};

// 我的解法：DFS+原数组标记，时间 12 ms 71.64%，空间 9.7 MB 75.38%
class Solution {
private:
    int directions[5] = { -1, 0, 1, 0, -1 };
    void dfs(vector<vector<char>>& board, int i, int j) {
        char& ch = board[i][j];
        if (ch == 'X' || ch == 'A') return;
        ch = 'A';
        for (int k = 0; k < 4; ++k) {
            int newi = i + directions[k], newj = j + directions[k + 1];
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
                if (board[newi][newj] == 'O') {
                    dfs(board, newi, newj);
                }
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        int height = board.size(), width = board[0].size();
        for (int i = 0; i < height; ++i) {
            dfs(board, i, 0);
            dfs(board, i, width - 1);
        }
        for (int i = 0; i < width; ++i) {
            dfs(board, 0, i);
            dfs(board, height - 1, i);
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                char& ch = board[i][j];
                if (ch == 'O') {
                    ch = 'X';
                }
                else if (ch == 'A') {
                    ch = 'O';
                }
            }
        }
    }
};