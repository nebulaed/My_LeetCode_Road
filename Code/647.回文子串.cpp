#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// 我的解法一：中心扩展算法，时间 O(n^2) 4 ms 82.96%，空间 O(1) 6.1 MB 78.53%
class Solution {
private:
    int expandAroundCenter(const string& s, size_t left, size_t right) {
        int count = 0;
        while (left != -1 && right < s.size() && s[left] == s[right]) {
            ++count;
            --left;
            ++right;
        }
        return count;
    }
public:
    int countSubstrings(string s) {
        int count = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            count += expandAroundCenter(s, i, i);
            count += expandAroundCenter(s, i, i + 1);
        }
        return count;
    }
};

// 官方题解：Manacher算法，时间O(n) 0 ms 100%，空间 6.6 MB 60.12%
class Solution {
public:
    int countSubstrings(string s) {
        // 加入'$'和'!'是为了循环时避免越界
        string t = "$#";
        for (char ch : s) {
            t += ch;
            t += '#';
        }
        t += '!';
        int n = t.size(), iMax = 0, rMax = 0, ans = 0;
        vector<int> armLen(n);
        for (int i = 1; i < n; ++i) {
            int& curArmLen = armLen[i];
            // 若i被包含在当前最大回文子串内，则以i为中心的最大臂长为[rMax - i + 1(最大回文子串右边界到i)与i在这个最大回文子串里的对称点的最大臂长]两个取最小值
            // 否则臂长为1
            curArmLen = (i <= rMax) ? min(rMax - i + 1, armLen[2 * iMax - i]) : 1;
            // 中心扩展
            while (t[i + curArmLen] == t[i - curArmLen]) {
                ++curArmLen;
            }
            // 动态维护iMax和rMax
            if (i + curArmLen - 1 > rMax) {
                iMax = i;
                rMax = i + curArmLen - 1;
            }
            // ans += (armLen[i] - 1) / 2向上取整
            // 举例：字符串为$#a#b#c#!，当当前字符为a时，最大臂长为curArmLen = 2，那么实际最大回文字符串长度为maxLen = curArmLen - 1 = 1，回文字符串数量为(maxLen + 1) / 2
            // 因此：回文字符串数量为curArmLen / 2
            ans += curArmLen / 2;
        }
        return ans;
    }
};