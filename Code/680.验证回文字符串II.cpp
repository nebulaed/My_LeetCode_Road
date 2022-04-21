#include<iostream>
#include<string>
using namespace std;

// 我的解法：双指针，时间 44 ms，空间 19.3 MB
class Solution {
public:
    bool validPalindrome(string s) {
        bool skip = false, flag = false;
        size_t left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                if (skip) return false;
                skip = true;
                if (s[right - 1] == s[left] && s[left + 1] == s[right]) {
                    flag = true;
                    break;
                }
                else if (s[right - 1] == s[left]) --right;
                else if (s[left + 1] == s[right]) ++left;
                else return false;
            }
            else {
                ++left;
                --right;
            }
        }
        if (!flag) return true;
        size_t lPtr = left + 1, rPtr = right;
        while (lPtr < rPtr) {
            if (s[lPtr] != s[rPtr]) {
                flag = false;
                break;
            }
            ++lPtr;
            --rPtr;
        }
        if (flag) return true;
        --right;
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};

// 官方解法一：双指针，时间 40 ms，空间 19.1 MB
class Solution {
private:
    bool checkPalindrome(const string& str, size_t low, size_t high) {
        for (; low < high; ++low, --high) {
            if (str[low] != str[high]) {
                return false;
            }
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        size_t low = 0, high = s.size() - 1;
        while (low < high) {
            if (s[low] == s[high]) {
                ++low;
                --high;
            }
            else {
                return checkPalindrome(s, low, high - 1) || checkPalindrome(s, low + 1, high);
            }
        }
        return true;
    }
};