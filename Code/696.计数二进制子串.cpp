#include<iostream>
#include<string>

using namespace std;

// 我的解法：中心扩展法，时间 12 ms 99.31%，空间 10.2 MB 89.36%
class Solution {
public:
    int countBinarySubstrings(string s) {
        int count = 0;
        size_t length = s.size();
        // 由于要求的是0数量和1数量相等，且0和1都必须连续的字符串
        // 以01或10为中心进行中心扩展，判断以该处01或10为中心的符合要求的字符串数量。
        for (size_t lCenter = 0; lCenter < length - 1; ++lCenter) {
            size_t rCenter = lCenter + 1;
            if (s[lCenter] == '0') {
                if (s[rCenter] == '1') {
                    ++count;
                    size_t left = lCenter, right = rCenter;
                    while (--left != -1 && ++right < length && s[left] == '0' && s[right] == '1') {
                        ++count;
                    }
                }
            }
            else {
                if (s[rCenter] == '0') {
                    ++count;
                    size_t left = lCenter, right = rCenter;
                    while (--left != -1 && ++right < length && s[left] == '1' && s[right] == '0') {
                        ++count;
                    }
                }
            }
        }
        return count;
    }
};

// LeetCode 101解法：时间 16 ms 91.08%，空间 10.3 MB 46.34%
// 从左往右遍历数组，记录和当前位置数字相同且连续的长度，以及其之前连续的不同数字的长度。举例来说，对于00110 的最后一位，我们记录的相同数字长度是1，因为只有一个连续0；我们记录的不同数字长度是2，因为在0 之前有两个连续的1。若不同数字的连续长度大于等于当前数字的连续长度，则说明存在一个且只存在一个以当前数字结尾的满足条件的子字符串。
class Solution {
public:
    int countBinarySubstrings(string s) {
        int pre = 0, cur = 1, count = 0;
        for (size_t i = 1; i < s.size(); ++i) {
            // 若当前字符和前一字符均为0或1，那么当前类型字符数量+1
            if (s[i] == s[i - 1]) {
                ++cur;
            }
            // 否则将当前类型字符数量赋给相反类型字符数量，当前类型字符数量归1
            else {
                pre = cur;
                cur = 1;
            }
            // 若不同类型字符数量大于等于当前类型字符数量，则满足条件的字符串数量+1
            if (pre >= cur) {
                ++count;
            }
        }
        return count;
    }
};