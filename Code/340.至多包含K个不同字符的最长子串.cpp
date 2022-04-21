#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;

// 我的解法：双指针(滑动窗口)，时间 4 ms 98.72%，空间 6.7 MB 98.72%
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        // 若k为0，任何长度大于0的字符串包含的字符种类都大于0，因此返回0
        if (k == 0) return k;
        // 字符哈希表，表示该字符是否出现在滑动窗口内
        bool flag[128]{};
        // 字符出现次数哈希表，表示该字符在滑动窗口内出现的次数
        int charFreq[128]{};
        // cnt表示滑动窗口内字符的种类数，left表示滑动窗口左端点，maxSize表示最大窗口长度
        int cnt = 0, left = 0, maxSize = 0;
        for (int right = 0; right < s.size(); ++right) {
            // 滑动窗口右端点的字符的出现次数+1
            ++charFreq[s[right]];
            // 若右端点字符在滑动窗口中之前没出现过
            if (!flag[s[right]]) {
                // 滑动窗口内字符种类数+1
                ++cnt;
                // 将该种类字符出现置为真
                flag[s[right]] = true;
            }
            // 若右端点在s最后一个位置或s下一个字符未在滑动窗口中出现
            if (right == s.size() - 1 || !flag[s[right + 1]]) {
                while (cnt == k) {
                    // 若当前滑动窗口大小大于maxSize，更新maxSize
                    maxSize = max(maxSize, right - left + 1);
                    // 若左端点右移后原左端点字符不再出现在滑动窗口内，滑动窗口内字符种类数-1，并将该种类字符出现置为假
                    if (--charFreq[s[left]] == 0) {
                        --cnt;
                        flag[s[left]] = false;
                    }
                    ++left;
                }
            }
        }
        // 若maxSize为0，说明s内的字符种类小于k，返回s全长
        return maxSize == 0 ? s.size() : maxSize;
    }
};

// 我的解法再优化：时间 0 ms 100%，空间 6.9 MB 85.29%
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        // 若k为0，任何长度大于0的字符串包含的字符种类都大于0，因此返回0
        if (k == 0) return k;
        // 字符出现次数哈希表，表示该字符在滑动窗口内出现的次数
        int charFreq[128]{};
        // cnt表示滑动窗口内字符的种类数，left表示滑动窗口左端点，maxSize表示最大窗口长度
        int cnt = 0, left = 0, maxSize = 0;
        for (int right = 0; right < s.size(); ++right) {
            // 滑动窗口右端点的字符的出现次数+1
            if (charFreq[s[right]]++ == 0) {
                // 若右端点字符在滑动窗口中之前没出现过，滑动窗口内字符种类数+1
                ++cnt;
            }
            // 若右端点在s最后一个位置或s下一个字符未在滑动窗口中出现
            if (right == s.size() - 1 || charFreq[s[right + 1]] == 0) {
                while (cnt == k) {
                    // 若当前滑动窗口大小大于maxSize，更新maxSize
                    maxSize = max(maxSize, right - left + 1);
                    // 若左端点右移后原左端点字符不再出现在滑动窗口内，滑动窗口内字符种类数-1，并将该种类字符出现置为假
                    if (--charFreq[s[left]] == 0) {
                        --cnt;
                    }
                    ++left;
                }
            }
        }
        // 若maxSize为0，说明s内的字符种类小于k，返回s全长
        return maxSize == 0 ? s.size() : maxSize;
    }
};


// 官方解法一：滑动窗口+哈希表，时间O(nk) 12 ms 67.40%，空间O(k) 8 MB 36.81%，k为输入字符串s内字符种类数
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int n = s.size();
        // 若s长度为0或k为0，返回0
        if (n * k == 0) return 0;

        int left = 0, right = 0;
        // 保存字符在滑动窗口内最后一次出现的位置
        unordered_map<char, int> hashMap;
        int maxLen = 1;
        while (right < n) {
            // 将s[right]出现在滑动窗口内的最后一个位置更新为right，然后right自加1
            hashMap[s[right++]] = right;
            // 若滑动窗口内字符种类已经大于k
            if (hashMap.size() == k + 1) {
                // 找出hashMap内在滑动窗口内最后一次出现最靠前的字符的位置
                int del_idx = min_element(hashMap.begin(), hashMap.end(), [](const auto& lhs, const auto& rhs) {
                    return lhs.second < rhs.second;
                })->second;
                // 删掉hashMap内对应字符
                hashMap.erase(s[del_idx]);
                left = del_idx + 1;
            }
            maxLen = max(maxLen, right - left);
        }
        return maxLen;
    }
};