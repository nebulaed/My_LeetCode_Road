#include<vector>
#include<stack>
#include<string>
using namespace std;

// 我的解法：逆波兰表达式，时间 12 ms 54%，空间 9 MB 38%
// 关键点：一元表达式“-”的处理
class Solution {
public:
    int calculate(string s) {
        // 将中缀表达式转换为后缀表达式
        string t;
        stack<int, vector<int>> stk;
        size_t length = s.size();
        bool flag = true;
        for (size_t i = 0; i < length; ++i) {
            if (isdigit(s[i])) {
                t += s[i];
                if (i + 1 == length || !isdigit(s[i + 1])) t += ',';
                flag = true;
            }
            else {
                if (s[i] == ' ') continue;
                if (s[i] == '(') {
                    stk.emplace(s[i]);
                    flag = false;
                }
                else if (s[i] == ')') {
                    while (stk.top() != '(') {
                        t += static_cast<char>(stk.top());
                        stk.pop();
                    }
                    stk.pop();
                }
                else {
                    // 关键点：当符号为'-'且前面无任何其他数字或符号，或者前面是'('时，加个0
                    if (s[i] == '-' && (t.empty() || !flag)) {
                        t += "0,";
                    }
                    while (!stk.empty() && (stk.top() == '+' || stk.top() == '-')) {
                        t += static_cast<char>(stk.top());
                        stk.pop();
                    }
                    stk.emplace(s[i]);
                }
            }
        }
        while (!stk.empty()) {
            t += static_cast<char>(stk.top());
            stk.pop();
        }
        // 对后缀表达式通过出栈入栈操作进行处理，得到计算结果
        for (size_t i = 0; i < t.size();) {
            if (isdigit(t[i])) {
                int num = 0;
                while (isdigit(t[i])) {
                    num = 10 * num + (t[i++] - '0');
                }
                stk.emplace(num);
            }
            else {
                if (t[i] == ',') {
                    ++i;
                    continue;
                }
                int rhs = stk.top();
                stk.pop();
                int lhs = stk.top();
                stk.pop();
                if (t[i++] == '+') {
                    stk.emplace(lhs + rhs);
                }
                else {
                    stk.emplace(lhs - rhs);
                }
            }
        }
        return stk.top();
    }
};

// 官方解法一：括号展开 + 栈，时间 O(n) 4 ms 97.89%，空间 O(n) 7.8 MB 88.34%
// 原理：用sign = {-1, +1}代表当前的符号，根据括号表达式的性质，它的取值：
// 1. 与字符串中当前位置的运算符有关
// 2. 若当前位置在一系列符号内，则也与这些括号前面的运算符相关：每当遇到一个以-号开头的括号，则意味着此后的符号都要被翻转
class Solution {
public:
    int calculate(string s) {
        stack<int, vector<int>> stk;
        stk.emplace(1);
        int sign = 1, ret = 0, n = s.size(), i = 0;
        while (i < n) {
            if (s[i] == ' ') ++i;
            else if (s[i] == '+') {
                sign = stk.top();
                ++i;
            }
            else if (s[i] == '-') {
                sign = -stk.top();
                ++i;
            }
            else if (s[i] == '(') {
                stk.emplace(sign);
                ++i;
            }
            else if (s[i] == ')') {
                stk.pop();
                ++i;
            }
            else {
                int num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
};

// 我的第二次解法：括号展开+栈，没必要用vector<bool>，时间 8 ms 80.30%，空间 7.8 MB 87.75%
class Solution {
public:
    int calculate(string s) {
        vector<bool> stk;
        stk.emplace_back(1);
        int sign = 1, ret = 0, n = s.size(), i = 0;
        while (i < n) {
            if (s[i] == ' ') ++i;
            else if (s[i] == '+') {
                sign = stk.back() ? 1 : -1;
                ++i;
            }
            else if (s[i] == '-') {
                sign = -(stk.back() ? 1 : -1);
                ++i;
            }
            else if (s[i] == '(') {
                stk.emplace_back(sign == -1 ? 0 : 1);
                ++i;
            }
            else if (s[i] == ')') {
                stk.pop_back();
                ++i;
            }
            else {
                int num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
};