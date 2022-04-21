#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// 我的解法：多指针，两次遍历，时间O(d(m+n)) 64 ms，空间O(d) 14.6 MB
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        size_t length = dictionary.size();
        vector<size_t> ptrDir(length, 0);
        for (char ch : s) {
            for (size_t i = 0; i < length; ++i) {
                size_t temp = ptrDir[i];
                const string& tempStr = dictionary[i];
                if (temp < tempStr.size() && tempStr[temp] == ch) {
                    ++ptrDir[i];
                }
            }
        }
        string ret;
        for (size_t i = 0; i < length; ++i) {
            const string& currWord = dictionary[i];
            size_t currPtr = ptrDir[i];
            size_t retLength = ret.size();
            if (currPtr == currWord.size()) {
                if (currPtr > retLength || (currPtr == retLength && currWord < ret)) {
                    ret = currWord;
                }
            }
        }
        return ret;
    }
};

// 官方解法一：双指针，一次遍历，时间O(d×(m+n)) 52 ms，空间O(1) 14.7 MB
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string ret;
        for (const auto& word : dictionary) {
            size_t ptrS = 0, ptrW = 0, wordSize = word.size();
            while (ptrS < s.size() && ptrW < wordSize) {
                if (word[ptrW] == s[ptrS]) {
                    ++ptrW;
                }
                ++ptrS;
            }
            if (ptrW == wordSize) {
                if (wordSize > ret.size() || (wordSize == ret.size() && word < ret)) {
                    ret = word;
                }
            }
        }
        return ret;
    }
};

// 官方解法二：排序，时间O(d*m*log d + d*(m+n)) 48 ms，空间O(d*m) 14.6 MB
// 先对dictionary做预处理，依据字符串长度的降序和字典序的升序进行排序，然后从前向后找到第一个符合条件的字符串直接返回即可。
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [](const string& lhs, const string& rhs) {
            return lhs.size() > rhs.size() || (lhs.size() == rhs.size() && lhs < rhs);
        });
        for (const string& word : dictionary) {
            size_t ptrW = 0, ptrS = 0, wordSize = word.size();
            while (ptrW < wordSize && ptrS < s.size()) {
                if (word[ptrW] == s[ptrS]) {
                    ++ptrW;
                }
                ++ptrS;
            }
            if (ptrW == wordSize) {
                return word;
            }
        }
        return "";
    }
};

// 官方解法三：动态规划，时间O(m*|Σ|+d*n) 44 ms，空间O(m*|Σ|) 15.4 MB
// 我们可以通过预处理，得到对于s的每一个位置，从该位置开始往后每一个字符第一次出现的位置
// 可以使用动态规划的方法实现预处理，令f[i][j]表示字符串s中从位置i开始往后字符j
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        size_t m = s.size();
        vector<array<int, 26>> dp(m + 1, array<int, 26>{});
        // 为最后一行全部填充上m，以便分辨是不是s中是不是没有某一字符
        fill(dp[m].begin(), dp[m].end(), m);

        // 从s的最后一个字符开始倒着统计
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) {
                // 若s[i]是第j位代表的字符，则记录下第j位字符出现的当前位置i
                if (s[i] == 'a' + j) {
                    dp[i][j] = i;
                }
                    // 否则第j位出现的位置和s的后一位置相同
                else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }
        string ret;
        for (const string& word : dictionary) {
            bool match = true;
            int j = 0;
            for (int i = 0; i < word.size(); ++i) {
                // 查找word[i]出现在s中的位置
                int pos = dp[j][word[i] - 'a'];
                // 若等于m说明s中没有word[i]
                if (pos == m) {
                    match = false;
                    break;
                }
                // 否则从s[j]开始查找word的下一位字符
                j = pos + 1;
            }
            if (match) {
                if (word.size() > ret.size() || (word.size() == ret.size() && word < ret)) {
                    ret = word;
                }
            }
        }
        return ret;
    }
};