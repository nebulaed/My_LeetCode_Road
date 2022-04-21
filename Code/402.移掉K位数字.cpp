#include<string>
#include<vector>
using namespace std;

// 我的解法：超时，每次找到第一个比后面的数字大的数字，把它移除，然后注意删掉前置零即可
class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        while (k--) {
            if (num.size() <= 1) return "0";
            bool mono = true;
            for (int i = 0; i < n - 1; ++i) {
                if (num[i] > num[i + 1]) {
                    num.erase(i, 1);
                    mono = false;
                    break;
                }
            }
            if (mono) num.pop_back();
            if (num.size() > 1) {
                for (auto it = num.begin(); it != num.end();) {
                    if (*it == '0') {
                        it = num.erase(it);
                    }
                    else break;
                }
            }
        }
        return num.empty() ? "0" : num;
    }
};

// 官方解法：贪心+单调栈，时间 O(n) 8 ms 57.24%，空间 O(n) 8.9 MB 24.52%
class Solution {
public:
    string removeKdigits(string num, int k) {
        vector<char> stk;
        for (char ch : num) {
            while (!stk.empty() && stk.back() > ch && k) {
                stk.pop_back();
                --k;
            }
            stk.emplace_back(ch);
        }
        while (k-- > 0) {
            stk.pop_back();
        }
        string ret;
        bool isLeadingZero = true;
        for (char ch : stk) {
            if (isLeadingZero && ch == '0') {
                continue;
            }
            isLeadingZero = false;
            ret += ch;
        }
        return ret.empty() ? "0" : ret;
    }
};