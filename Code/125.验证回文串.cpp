#include<string>
using namespace std;

// 我的解法：时间 O(|s|) 4 ms 88.35%，空间 O(1) 7.2 MB 68.83%
class Solution {
public:
    bool isPalindrome(string s) {
        size_t left = 0, right = s.size() - 1;
        while (left < right) {
            if (!isalnum(s[left])) {
                ++left;
                continue;
            }
            if (!isalnum(s[right])) {
                --right;
                continue;
            }
            if (s[left] == s[right] || ((islower(s[left]) && s[left] - 32 == s[right]) || (isupper(s[left]) && s[left] + 32 == s[right]))) {
                ++left;
                --right;
            } else return false;
        }
        return true;
    }
};

// 官方解法：时间 O(|s|) 4 ms 88.35%，空间 O(1) 7.2 MB 59.88%
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        int left = 0, right = n - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left])) {
                ++left;
            }
            while (left < right && !isalnum(s[right])) {
                --right;
            }
            if (left < right) {
                if (tolower(s[left]) != tolower(s[right])) {
                    return false;
                }
                ++left;
                --right;
            }
        }
        return true;
    }
};