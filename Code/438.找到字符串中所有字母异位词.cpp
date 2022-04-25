#include<vector>
#include<array>
#include<string>
using namespace std;

// 我的解法：哈希表+滑动窗口，时间 O(m + (n - m) × Σ) 12 ms 65.87%，空间 O(Σ) 8.6 MB 25.88%
// m为p的长度，n为s的长度，Σ=26
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int winLen = p.size() - 1, n = s.size();
        if (winLen >= n) return {};
        array<int, 26> record{};
        for (char ch: p){
            ++record[ch - 'a'];
        }
        array<int, 26> hashMap{};
        for (int i = 0; i <= winLen; ++i){
            ++hashMap[s[i] - 'a'];
        }
        vector<int> ret;
        if (hashMap == record) ret.emplace_back(0);
        for (int i = 1; i < n - winLen; ++i){
            --hashMap[s[i - 1] - 'a'];
            ++hashMap[s[i + winLen] - 'a'];
            if (hashMap == record) ret.emplace_back(i);
        }
        return ret;
    }
};


// 官方解法：优化的滑动窗口，时间 O(n + m + Σ) 4 ms 99.16%，空间 O(Σ) 8.4 MB 75.02%
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int winLen = p.size() - 1, n = s.size();
        if (winLen >= n) return {};
        array<int, 26> hashMap{};
        for (int i = 0; i <= winLen; ++i) {
            ++hashMap[s[i] - 'a'];
            --hashMap[p[i] - 'a'];
        }
        int diff{0};
        for (int i = 0; i < 26; ++i) {
            if (hashMap[i] != 0) ++diff;
        }
        vector<int> ret;
        if (diff == 0) ret.emplace_back(0);
        for (int i = 1; i < n - winLen; ++i) {
            int &last = hashMap[s[i - 1] - 'a'], &first = hashMap[s[i + winLen] - 'a'];
            if (--last == 0) --diff;
            else if (last == -1) ++diff;
            if (++first == 0) --diff;
            else if (first == 1) ++diff;
            if (diff == 0) ret.emplace_back(i);
        }
        return ret;
    }
};