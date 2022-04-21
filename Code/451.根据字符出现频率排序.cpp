#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>

using namespace std;

// 我的解法一：桶排序，时间 12 ms，空间 10.7 MB
class Solution {
private:
    size_t ch2sizet(char ch) {
        size_t ind;
        if (ch >= 'a' && ch <= 'z') {
            ind = ch - 'a';
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ind = ch - 'A' + 26;
        }
        else {
            ind = ch - '0' + 52;
        }
        return ind;
    }

    char int2ch(int ind) {
        char ch;
        if (ind >= 0 && ind < 26) {
            ch = 'a' + ind;
        }
        else if (ind >= 26 && ind < 52) {
            ch = 'A' + ind - 26;
        }
        else {
            ch = '0' + ind - 52;
        }
        return ch;
    }

public:
    string frequencySort(string s) {
        int charFreq[62]{};
        int maxCount = 0;
        for (char ch : s) {
            maxCount = max(maxCount, ++charFreq[ch2sizet(ch)]);
        }

        vector<vector<int>> buckets(maxCount + 1);
        for (int i = 0; i < sizeof(charFreq) / sizeof(int); ++i) {
            buckets[charFreq[i]].emplace_back(i);
        }

        string ret;
        for (int i = maxCount; i >= 0; --i) {
            for (int num : buckets[i]) {
                ret += string(i, int2ch(num));
            }
        }
        return ret;
    }
};

// 我的解法二：哈希表+桶排序，时间 8 ms，空间 10.6 MB
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> charFreq;
        int maxCount = 0;
        for (char ch : s) {
            maxCount = max(maxCount, ++charFreq[ch]);
        }

        vector<vector<char>> buckets(maxCount + 1);
        for (auto it = charFreq.begin(); it != charFreq.end(); ++it) {
            buckets[it->second].emplace_back(it->first);
        }

        string ret;
        for (auto rit = buckets.rbegin(); rit != buckets.rend(); ++rit) {
            for (char ch : *rit) {
                ret += string(charFreq[ch], ch);
            }
        }
        return ret;
    }
};