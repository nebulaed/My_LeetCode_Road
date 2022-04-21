#include<string>
using namespace std;

// 我的解法：时间 0 ms 100%，空间 7 MB 42.72%
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size(), start = 0, end = n - 1;
        bool flag = false;
        string ret;
        for (int i = n - 1; i >= 0; --i) {
            if (!flag && isalnum(s[i])) {
                end = i;
                flag = true;
            }
            else if (flag && s[i] == ' ') {
                flag = false;
                start = i + 1;
                ret += ret.empty() ? s.substr(start, end - start + 1) : " " + s.substr(start, end - start + 1);
            }
        }
        if (s[0] != ' ') {
            ret += ret.empty() ? s.substr(0, end + 1) : " " + s.substr(0, end + 1);
        }
        return ret;
    }
};