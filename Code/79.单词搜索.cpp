#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;


// 我的方法：dfs+回溯，超时
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Solution {
private:
    bool flag = false;
    unordered_set<pair<int, int>, hash_pair> path;
public:
    void dfs(int pos, pair<int, int> crd, const string& word, const vector<vector<char>>& board) {
        if (pos == word.size()) {
            flag = true;
            return;
        }
        vector<pair<int, int>> posSet;
        if (pos == 0) {
            posSet = findBoard(word[0], board);
        }
        else {
            posSet = findNearby(word[pos], crd, board);
        }

        for (auto it = posSet.begin(); it != posSet.end(); ++it) {
            path.insert(*it);
            dfs(pos + 1, *it, word, board);
            path.erase(*it);
        }

    }
    bool exist(vector<vector<char>>& board, string word) {
        dfs(0, pair<int, int>(0, 0), word, board);
        return this->flag;
    }

    vector<pair<int, int>> findBoard(char c, const vector<vector<char>>& board) {
        vector<pair<int, int>> posSet;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == c) {
                    posSet.emplace_back(i, j);
                }
            }
        }
        return posSet;
    }

    vector<pair<int, int>> findNearby(char c, const pair<int, int>& crd, const vector<vector<char>>& board) {
        vector<pair<int, int>> posSet;
        if ((crd.first > 0) && (board[crd.first - 1][crd.second] == c) && (!path.count(pair<int, int>(crd.first - 1, crd.second)))) {
            posSet.emplace_back(crd.first - 1, crd.second);
        }
        if ((crd.first < board.size() - 1) && (board[crd.first + 1][crd.second] == c) && (!path.count(pair<int, int>(crd.first + 1, crd.second)))) {
            posSet.emplace_back(crd.first + 1, crd.second);
        }
        if ((crd.second > 0) && (board[crd.first][crd.second - 1] == c) && (!path.count(pair<int, int>(crd.first, crd.second - 1)))) {
            posSet.emplace_back(crd.first, crd.second - 1);
        }
        if ((crd.second < board[0].size() - 1) && (board[crd.first][crd.second + 1] == c) && (!path.count(pair<int, int>(crd.first, crd.second + 1)))) {
            posSet.emplace_back(crd.first, crd.second + 1);
        }
        return posSet;
    }
};

// 我的方法：优化后的dfs+回溯，1356 ms，177.8 MB
class Solution {
private:
    bool flag = false;
public:
    void dfs(int pos, const pair<int, int>& crd, const string& word, const vector<vector<char>>& board, vector<vector<int>>& path) {
        if (pos == word.size()) {
            this->flag = true;
            return;
        }
        vector<pair<int, int>> posSet;
        if (pos == 0) {
            findBoard(word[0], board, posSet);
        }
        else {
            findNearby(word[pos], crd, board, path, posSet);
        }

        for (auto it = posSet.begin(); it != posSet.end(); ++it) {
            path[it->first][it->second] = 1;
            dfs(pos + 1, *it, word, board, path);
            path[it->first][it->second] = 0;
        }
    }

    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<int>> path(board.size(), vector<int>(board[0].size(), 0));
        dfs(0, pair<int, int>(0, 0), word, board, path);
        return this->flag;
    }

    void findBoard(char c, const vector<vector<char>>& board, vector<pair<int, int>>& posSet) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == c) {
                    posSet.emplace_back(i, j);
                }
            }
        }
    }

    void findNearby(char c, const pair<int, int>& crd, const vector<vector<char>>& board, const vector<vector<int>>& path, vector<pair<int, int>>& posSet) {
        if ((crd.first > 0) && (board[crd.first - 1][crd.second] == c) && (!path[crd.first - 1][crd.second])) {
            posSet.emplace_back(crd.first - 1, crd.second);
        }
        if ((crd.first < board.size() - 1) && (board[crd.first + 1][crd.second] == c) && (!path[crd.first + 1][crd.second])) {
            posSet.emplace_back(crd.first + 1, crd.second);
        }
        if ((crd.second > 0) && (board[crd.first][crd.second - 1] == c) && (!path[crd.first][crd.second - 1])) {
            posSet.emplace_back(crd.first, crd.second - 1);
        }
        if ((crd.second < board[0].size() - 1) && (board[crd.first][crd.second + 1] == c) && (!path[crd.first][crd.second + 1])) {
            posSet.emplace_back(crd.first, crd.second + 1);
        }
    }
};

// 官方解法优化后：dfs+回溯，304 ms，7.9 MB
class Solution {
public:
    bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k) {
        if (board[i][j] != s[k]) {
            return false;
        }
        else if (k == s.size() - 1) {
            return true;
        }
        visited[i][j] = true;
        int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        bool result = false;
        for (const auto& dir : directions) {
            int newi = i + dir[0], newj = j + dir[1];
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
                if (!visited[newi][newj]) {
                    bool flag = check(board, visited, newi, newj, s, k + 1);
                    if (flag) {
                        result = true;
                        break;
                    }
                }
            }
        }
        visited[i][j] = false;
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int h = board.size(), w = board[0].size();
        vector<vector<int>> visited(h, vector<int>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                bool flag = check(board, visited, i, j, word, 0);
                if (flag) {
                    return true;
                }
            }
        }
        return false;
    }
};

// 官方解答再优化：时间 224 ms 75.10%，空间 7.7 MB 51%
class Solution {
private:
    int directions[5] = { -1, 0, 1, 0, -1 };
    bool check(const vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, string& s, int k) {
        if (board[i][j] != s[k]) {
            return false;
        }
        else if (k == s.length() - 1) {
            return true;
        }
        visited[i][j] = true;
        bool result = false;
        for (size_t l = 0; l < 4; ++l) {
            int newi = i + directions[l], newj = j + directions[l + 1];
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size() && !visited[newi][newj]) {
                if (!visited[newi][newj]) {
                    bool flag = check(board, visited, newi, newj, s, k + 1);
                    if (flag) {
                        result = true;
                        break;
                    }
                }
            }
        }
        visited[i][j] = false;
        return result;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int h = board.size(), w = board[0].size();
        vector<vector<bool>> visited(h, vector<bool>(w));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                bool flag = check(board, visited, i, j, word, 0);
                if (flag) {
                    return true;
                }
            }
        }
        return false;
    }
};

// 我的第二次解法：时间 244 ms 68.60%，空间 7.9 MB 43.71%
class Solution {
private:
    int directions[5] = { -1, 0, 1, 0, -1 };
    bool dfs(const vector<vector<char>>& board, vector<vector<bool>>& used, const string& word, int pos, int x, int y) {
        if (word[pos] != board[x][y]) return false;
        if (pos == word.size() - 1) return true;
        for (int i = 0; i < 4; ++i) {
            int newx = x + directions[i], newy = y + directions[i + 1];
            if (newx >= 0 && newx < board.size() && newy >= 0 && newy < board[0].size() && !used[newx][newy]) {
                used[newx][newy] = true;
                if (dfs(board, used, word, pos + 1, newx, newy)) return true;
                used[newx][newy] = false;
            }
        }
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> used(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    used[i][j] = true;
                    if (dfs(board, used, word, 0, i, j)) {
                        return true;
                    }
                    used[i][j] = false;
                }
            }
        }
        return false;
    }
};

int main() {
    vector<vector<char>> board = { {'A', 'B', 'C', 'E'},{'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'} };
    string word = "ABCCED";

    Solution s;
    bool ret = s.exist(board, word);

    cout << ret << endl;

    return 0;

}