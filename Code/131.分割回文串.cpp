#include<iostream>
#include<vector>
#include<string>
#include<array>
using namespace std;

// 我的解法：DFS, 时间 100 ms 84.51%，空间 73.8 MB 77.08%
class Solution {
private:
    vector<vector<string>> ret;

    bool isPalind(const string& s) {
        size_t left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] == s[right]) {
                ++left;
                --right;
            } else return false;
        }
        return true;
    }

    void dfs(const string& s, size_t pos, vector<string>& curr) {
        if (pos == s.size()) {
            ret.emplace_back(curr);
            return;
        }
        string part;
        for (size_t end = pos + 1; end <= s.size(); ++end) {
            part = s.substr(pos, end - pos);
            if (isPalind(part)) {
                curr.emplace_back(part);
                dfs(s, end, curr);
                curr.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<string> curr;
        dfs(s, 0, curr);
        return ret;
    }
};

// 我的解法：DFS，时间 116 ms 53.62%，空间 73.6 MB 90.35%
class Solution {
private:
    vector<vector<string>> ret;

    bool isPalind(const string& s) {
        size_t left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] == s[right]) {
                ++left;
                --right;
            } else return false;
        }
        return true;
    }

    void dfs(const string& s, size_t pos, array<size_t, 16>& curr, size_t c_pos) {
        if (pos == s.size()) {
            size_t len = 0;
            for (size_t i = 0; i < 16; ++i) {
                if (curr[i] == 0) {
                    len = i;
                    break;
                }
            }
            if (len == 0) len = 16;
            vector<string> currRet(len);
            size_t prev = 0;
            for (size_t i = 0; i < len; ++i) {
                currRet[i] = move(s.substr(prev, curr[i] - prev));
                prev = curr[i];
            }
            ret.push_back(move(currRet));
            return;
        }
        for (size_t end = pos + 1; end <= s.size(); ++end) {
            if (isPalind(s.substr(pos, end - pos))) {
                curr[c_pos] = end;
                dfs(s, end, curr, c_pos + 1);
                curr[c_pos] = 0;
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        array<size_t, 16> curr{};
        dfs(s, 0, curr, 0);
        return ret;
    }
};

int main() {
    string input{"aab"};

    Solution sol;

    vector<vector<string>> ret = sol.partition(input);

    for (auto& var1: ret) {
        cout << "[";
        for (auto& var2: var1) {
            cout << var2 << ",";
        }
        cout << "],";
    }

    return 0;
}