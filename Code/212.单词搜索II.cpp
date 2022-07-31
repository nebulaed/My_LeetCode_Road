#include<vector>
#include<string>
#include<array>
#include<list>
#include<unordered_set>
using namespace std;

// 我的解法1：list，超时
class Solution {
private:
    int dirs[5]{-1, 0, 1, 0, -1};
    vector<string> ret;

    bool dfs(const vector<vector<char>>& board, const string& word, vector<bool>& rec, int pos, int x, int y) {
        if (pos == word.size()) {
            ret.emplace_back(word);
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            int newx = x + dirs[i], newy = y + dirs[i + 1], m = board.size(), n = board[0].size();
            if (newx >= 0 && newx < m && newy >= 0 && newy < n && !rec[newx * n + newy] && word[pos] == board[newx][newy]) {
                rec[newx * n + newy] = true;
                if (dfs(board, word, rec, pos + 1, newx, newy)) {
                    rec[newx * n + newy] = false;
                    return true;
                }
                rec[newx * n + newy] = false;
            }
        }
        return false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        array<list<int>, 26> hashMap;
        int pos = 0;
        for_each(words.begin(), words.end(), [&](string& word){
            hashMap[word[0] - 'a'].emplace_back(pos++);
        });
        int m = board.size(), n = board[0].size();
        vector<bool> rec(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                auto& lst = hashMap[board[i][j] - 'a'];
                if (!lst.empty()) {
                    rec[i * n + j] = true;
                    lst.remove_if([&board, &words, &rec, i, j, this](int ind){
                        return dfs(board, words[ind], rec, 1, i, j);
                    });
                    // 上述remove_if等效于：
                    /*for (auto it = lst.begin(); it != lst.end(); ++it) {
                        if (dfs(board, words[*it], rec, 1, i, j)) {
                            it = lst.erase(it);
                        } else {
                            it = ++it;
                        }
                    }*/
                    rec[i * n + j] = false;
                }
            }
        }
        return ret;
    }
};

// 我的解法2：unordered_multimap，超时
class Solution {
private:
    int dirs[5]{-1, 0, 1, 0, -1};
    vector<string> ret;

    bool dfs(const vector<vector<char>>& board, const string& word, vector<bool>& rec, int pos, int x, int y) {
        if (pos == word.size()) {
            ret.push_back(move(word));
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            int newx = x + dirs[i], newy = y + dirs[i + 1], m = board.size(), n = board[0].size();
            if (newx >= 0 && newx < m && newy >= 0 && newy < n && !rec[newx * n + newy] && word[pos] == board[newx][newy]) {
                rec[newx * n + newy] = true;
                if (dfs(board, word, rec, pos + 1, newx, newy)) {
                    rec[newx * n + newy] = false;
                    return true;
                }
                rec[newx * n + newy] = false;
            }
        }
        return false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        unordered_multimap<char, int> hashMap;
        int pos = 0;
        for_each(words.begin(), words.end(), [&hashMap, &pos](string& word){
            char ch = word[0];
            hashMap.emplace(ch, pos++);
        });
        int m = board.size(), n = board[0].size();
        vector<bool> rec(m * n, false);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                auto rg = hashMap.equal_range(board[i][j]);
                if (rg.first != hashMap.end()) {
                    rec[i * n + j] = true;
                    for (auto it = rg.first; it != rg.second;) {
                        if (dfs(board, words[it->second], rec, 1, i, j)) {
                            it = hashMap.erase(it);
                        } else ++it;
                    }
                    rec[i * n + j] = false;
                }
            }
        }
        return ret;
    }
};

// 我的解法三：同时搜索多个单词，时间 212 ms 84.36%，空间 9.9 MB 98.65%
class Solution {
private:
    int dirs[5]{-1, 0, 1, 0, -1};
    vector<string> ret;

    void dfs(const vector<vector<char>>& board, vector<bool>& rec, unordered_set<string>& wordSet, string& curr, int x, int y) {
        curr += board[x][y];
        auto it = wordSet.find(curr);
        if (it != wordSet.end()) {
            ret.emplace_back(curr);
            wordSet.erase(it);
            if (wordSet.empty()) {
                curr.pop_back();
                return;
            }
        }
        if (curr.size() == 10) {
            curr.pop_back();
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int newx = x + dirs[i], newy = y + dirs[i + 1], m = board.size(), n = board[0].size(), pos = newx * n + newy;
            if (newx >= 0 && newx < m && newy >= 0 && newy < n && !rec[pos]) {
                rec[pos] = true;
                dfs(board, rec, wordSet, curr, newx, newy);
                rec[pos] = false;
                if (wordSet.empty()) break;
            }
        }
        curr.pop_back();
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        array<unordered_set<string>, 26> hashMap;
        for_each(words.begin(), words.end(), [&](const string& word){
            hashMap[word[0] - 'a'].emplace(word);
        });
        int m = board.size(), n = board[0].size();
        vector<bool> rec(m * n);
        string curr;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                auto& wordSet = hashMap[board[i][j] - 'a'];
                if (!wordSet.empty()) {
                    rec[i * n + j] = true;
                    dfs(board, rec, wordSet, curr, i, j);
                    rec[i * n + j] = false;
                    string().swap(curr);
                }
            }
        }
        return ret;
    }
};