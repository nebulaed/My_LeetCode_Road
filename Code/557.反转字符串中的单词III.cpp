#include<string>
#include<algorithm>
using namespace std;

// 我的解法：时间 O(n) 8 ms 91.77%，空间 O(1) 9.3 MB 87.92%
class Solution {
public:
    string reverseWords(string s) {
        size_t left = 0, right = 0, len = s.size();
        while (right < len) {
            while (right != len && s[right] != ' '){
                ++right;
            }
            reverse(s.begin() + left, s.begin() + right);
            left = ++right;
        }
        return s;
    }
};