#include<iostream>
#include<string>
#include<array>

using namespace std;

// 我的解法：两次哈希表计数，时间 4 ms 91.49%，空间 7.2 MB 30.60%
class Solution {
public:
    bool isAnagram(string s, string t) {
        array<int, 26> charFreqMapS{};
        for (char ch : s) {
            ++charFreqMapS[ch - 'a'];
        }
        array<int, 26> charFreqMapT{};
        for (char ch : t) {
            ++charFreqMapT[ch - 'a'];
        }
        return charFreqMapS == charFreqMapT;
    }
};

// LeetCode 101解法：一次哈希表计数，时间 4 ms 91.49%，空间 7 MB 93.11%
class Solution {
public:
    bool isAnagram(string s, string t) {
        size_t n1 = s.size(), n2 = t.size();
        if (n1 != n2) return false;
        array<int, 26> charFreqMap{};
        for (size_t i = 0; i < n1; ++i) {
            ++charFreqMap[s[i] - 'a'];
            --charFreqMap[t[i] - 'a'];
        }
        for (int freq : charFreqMap) {
            if (freq) return false;
        }
        return true;
    }
};